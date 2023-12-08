#include <unistd.h>
#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_functions.h"
#include "sound_set_map.h"
#endif
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 16

uint8_t playerIndexes[100];

ColorT gColorArray[MAX_TEAMS];
int gPlayersScore[100];
uint32_t gPlayersFriendlyHits[100];
uint8_t gTeamsCount = 0;
uint8_t gErrorState = 0;
uint8_t gAllPlayersTheSameColor = 0;
uint8_t gPlayersInTeam = 0;
uint8_t gPlayersCount = 0;
uint8_t gLeadingTeamIndex = 0;

typedef struct {
    uint8_t teamIndex;
} PlayerData;

PlayerData gPlayerData[100];

volatile uint8_t gvBonusIndex = 1;
volatile uint8_t gvBonusShotCode = 0;
volatile uint8_t gvBonusNonactive = 1;
volatile uint8_t gvMineNonactive = 1;
volatile uint8_t gvSingleModule = 0; // info if there is only one smart module in arena
ColorT gvColorsTable[MAX_TEAMS] = {0};

int gTimerBonusDeactive = 0;
int gTimerBonusActivate = 0;

int gTimerMineDeactive = 0;
int gTimerMineActivate = 0;
int gTimerMineShoot = 0;

const ColorT gColorBonus = {0xFF, 0xFF, 0x00}; // yellow color
const ColorT gColorGray = {0x20, 0x20, 0x20};
const ColorT gColorBlack = {0x00, 0x00, 0x00};
ColorT gColorArena = {0x00, 0x00, 0x00};
const char pgLightBroadcastAddress[] = "000000000000000000";

std::string gBonusModule;
std::string gMineModule;

void selectNewBonus(void);
void selectBonusActivateTime(void);
void selectMineActivateTime(void);
void mineEffectInit(void);
void bonusEffectInit(void);

void handlerBonusDeactivate() {
    // printf("Bonus deactivated\n");
    if (gvBonusNonactive == 0) {
        ENGINE_playSoundFromSoundSet(BonusDeactivated);
    } else {
    }
    ENGINE_lightSetColors(gBonusModule, gColorArena, gColorBlack, gColorBlack, 1);
    ENGINE_clearTimer(gTimerBonusDeactive);
    selectBonusActivateTime();
    gvBonusNonactive = 1;
    ENGINE_lightLock(gBonusModule, 0x00);
    ENGINE_lightSetColors(gBonusModule, gvColorsTable[gLeadingTeamIndex], gColorBlack, gColorBlack, 1);
}

void handlerBonusActivate() {
    // printf("Bonus activated\n");
    // choose new module to be bonus
    std::string lBonusNewAddress;
    if (gvSingleModule == 1) {
        if (gvMineNonactive == 1) {
            // printf("Bonus the same\n");
            lBonusNewAddress = gBonusModule;
        } else {
            // printf("Bonus delayed\n");
            ENGINE_clearTimer(gTimerBonusActivate);
            gTimerBonusActivate = ENGINE_setTimer(handlerBonusActivate, 10000U);
            return;
        }
    } else {
        do {
            lBonusNewAddress = ENGINE_getRandomBonusModule().address;
        } while ((lBonusNewAddress == gMineModule) && (lBonusNewAddress != "none"));
    }

    if (lBonusNewAddress != "none") {
        ENGINE_playSoundFromSoundSet(BonusActivated);
        gBonusModule = lBonusNewAddress;

        bonusEffectInit();

        // start yellow light at bonus and near lights
        ENGINE_lightSetColors(gBonusModule, gColorBonus, gColorBonus, gColorBonus, 1);
        ENGINE_clearTimer(gTimerBonusActivate);
        gTimerBonusDeactive = ENGINE_setTimer(handlerBonusDeactivate, 15000U);
        gvBonusNonactive = 0;
        ENGINE_lightLock(gBonusModule, 0x07);
    }
}

void handlerMineDeactivate() {
    // printf("Mine deactivated\n");
    ENGINE_lightSetColors(gMineModule, gColorArena, gColorBlack, gColorBlack, 1);
    ENGINE_clearTimer(gTimerMineDeactive);
    selectMineActivateTime();
    gvMineNonactive = 1;
    ENGINE_lightLock(gMineModule, 0x00);
    ENGINE_lightSetColors(gMineModule, gvColorsTable[gLeadingTeamIndex], gColorBlack, gColorBlack, 1);
}

void handlerMineShoot() {
    ENGINE_playSoundId(sfxMineExplosion);
    ENGINE_clearTimer(gTimerMineShoot);
    ENGINE_lightSetShooting(gMineModule, 0x00, 0x05, 2); // info, shooting periode*100ms, number of shots
    usleep(40000);
}

void handlerMineActivate() {
    // printf("Mine activated\n");
    // choose new module to be bonus
    std::string lMineNewAddress;
    if (gvSingleModule == 1) {
        if (gvBonusNonactive == 1) {
            lMineNewAddress = gMineModule;
            // printf("Mine the same\n");
        } else {
            // printf("Mine delay\n");
            ENGINE_clearTimer(gTimerMineActivate);
            gTimerMineActivate = ENGINE_setTimer(handlerMineActivate, 10000U);
            return;
        }
    } else {
        do {
            lMineNewAddress = ENGINE_getRandomBonusModule().address;
        } while ((lMineNewAddress == gBonusModule) && (lMineNewAddress != "none"));
    }

    if (lMineNewAddress != "none") {
        ENGINE_playSoundFromSoundSet(MineActivated);

        gMineModule = lMineNewAddress;

        mineEffectInit();

        ENGINE_lightStartSequence(gMineModule, 0x5550); // stop all operations
        usleep(40000);
        ENGINE_lightStartSequence(gMineModule, 0x9990); // switch to buffer 2
        usleep(40000);
        ENGINE_lightStartSequence(gMineModule, 0x3330); // run sequence once
        usleep(40000);

        ENGINE_clearTimer(gTimerMineActivate);
        gTimerMineShoot = ENGINE_setTimer(handlerMineShoot, 2900);
        gTimerMineDeactive = ENGINE_setTimer(handlerMineDeactivate, 3500);
        gvMineNonactive = 0;
        ENGINE_lightLock(gMineModule, 0x07);
    }
}

void selectNewBonus(void) {
    gvBonusIndex = rand() % 3 + 1;
    // printf("new bonus %d\n", gvBonusIndex);
}

void selectBonusActivateTime(void) {
    gTimerBonusActivate = ENGINE_setTimer(handlerBonusActivate, 5000 + rand() % 5000); // 15000 + rand() % 15000
}

void selectMineActivateTime(void) {
    gTimerMineActivate = ENGINE_setTimer(handlerMineActivate, 10000 + rand() % 10000);
}

void roundInitTeams(void) {
    uint8_t lTeamsFreeSpaces[MAX_TEAMS] = {0};
    uint8_t i = 0;
    uint8_t lMsg[2] = {'I', 0};

    /*clean old setup*/
    for (i = 0; i < gPlayersCount; i++) {
        gPlayerData[i].teamIndex = 255;
    }

    /*select how many players will be in each team*/
    for (i = 0; i < gTeamsCount; i++) {
        lTeamsFreeSpaces[i] = gPlayersInTeam;
    }

    /*for each player, choose randomly team index, check if there is free space in team*/
    for (i = 0; i < gPlayersCount; i++) {
        uint8_t lTeamIndex;
        do {
            lTeamIndex = rand() % gTeamsCount;
        } while (lTeamsFreeSpaces[lTeamIndex] == 0);
        lTeamsFreeSpaces[lTeamIndex]--;
        gPlayerData[i].teamIndex = lTeamIndex;
#ifdef SIMULATION_PLUGIN
        printf("player %d into team %d\n", i, lTeamIndex);
#endif
    }

    /*send new team setup to players*/
    for (uint8_t i = 0; i < gPlayersCount; i++) {
        lMsg[1] = gPlayerData[i].teamIndex;
        ENGINE_sendCustomMessage(lMsg, 2, i);
    }
}

void arenaColorProcess(void) {
    uint8_t lPlayersInTeams[MAX_TEAMS] = {0};
    uint8_t lColorChangeFlag = 0;
    uint8_t lLeadingTeamIndexTmp = gLeadingTeamIndex;
    for (uint8_t i = 0; i < gPlayersCount; i++) {
        uint8_t lTeamIndex = gPlayerData[i].teamIndex;
        lPlayersInTeams[lTeamIndex]++;
    }
    printf("in color new leader %d\n", gLeadingTeamIndex);
    for (uint8_t i = 0; i < gTeamsCount; i++) {
        printf("t %d %d, ", i, lPlayersInTeams[i]);
        if (lPlayersInTeams[i] > lPlayersInTeams[gLeadingTeamIndex]) {
            gLeadingTeamIndex = i;
            lColorChangeFlag = 1;
            printf("color change by new leader\n");
        }
    }
    printf("\n");
    if (lColorChangeFlag == 0) {
        printf("in color the same\n");
        uint8_t lCounter = 1;
        while (lCounter < gTeamsCount) {
            uint8_t lIndex = (lCounter + gLeadingTeamIndex) % gTeamsCount;
            printf("indx %d\n", lIndex);
            if (lPlayersInTeams[lIndex] == lPlayersInTeams[gLeadingTeamIndex]) {
                gLeadingTeamIndex = lIndex;
                lCounter = gTeamsCount;
                lColorChangeFlag = 1;
                printf("color change the same number\n");
            }
            lCounter++;
        }
    }

    if (lColorChangeFlag == 1) {
        printf("in color change %d\n", gLeadingTeamIndex);
        ColorT lColor = gvColorsTable[gLeadingTeamIndex];

        printf("color change 0x%02X, 0x%02X, 0x%02X\n", lColor.red, lColor.green, lColor.blue);
        /*set fade effect, one operation, going to new color*/
        usleep(40000);
        ENGINE_lightClearOperationBuffer(pgLightBroadcastAddress);
        ENGINE_lightClearSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
        ENGINE_lightAddOperation(pgLightBroadcastAddress, {1, lColor.red, lColor.green, lColor.blue, 50, 0}); // pulsing, team color, only increase
        usleep(80000);
        ENGINE_lightSyncOperationBuffer(pgLightBroadcastAddress);
        ENGINE_lightAddSequence(pgLightBroadcastAddress, {0, 1}, 0b00111111); //{index, repeat}
        usleep(80000);
        ENGINE_lightSyncSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
        usleep(80000);
        std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();
        for (DeviceT lModule : lBonusModules) {
            ENGINE_lightClearSequenceBuffer(lModule.address, 0b00111111);
            ENGINE_lightAddSequence(lModule.address, {0, 1}, 0b00000011); //{index, repeat}
            ENGINE_lightSyncSequenceBuffer(lModule.address, 0b00111111);
        }
        usleep(80000);
        ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x7770);
        usleep(40000);
        ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x3330);
    }
}

void mineEffectInit(void) {
    usleep(40000);
    ENGINE_lightClearOperationBuffer(gMineModule);
    ENGINE_lightClearSequenceBuffer(gMineModule, 0b00111111);

    // 0 blinking, white, fast
    ENGINE_lightAddOperation(gMineModule, {0, 0xFF, 0xFF, 0xFF, 5, 5});

    // 1 pulsing, red, slow
    ENGINE_lightAddOperation(gMineModule, {1, 0xFF, 0x00, 0x00, 40, 40});
    // 2 pulsing, red, medium slow
    ENGINE_lightAddOperation(gMineModule, {1, 0xFF, 0x00, 0x00, 30, 30});
    // 3 pulsing, red, medium
    ENGINE_lightAddOperation(gMineModule, {1, 0xFF, 0x00, 0x00, 20, 20});
    // 4 pulsing, red, medium fast
    ENGINE_lightAddOperation(gMineModule, {1, 0xFF, 0x00, 0x00, 10, 10});
    // 5 pulsing, red, fast
    ENGINE_lightAddOperation(gMineModule, {1, 0xFF, 0x00, 0x00, 5, 5});

    // red pulsing for mine + white boom, to circuit 2 and 3, buffer 2 for both
    // length is 3,35 s
    ENGINE_lightAddSequence(gMineModule, {1, 1}, 0b00101010); //{index, repeat}
    ENGINE_lightAddSequence(gMineModule, {2, 1}, 0b00101010); //{index, repeat}
    ENGINE_lightAddSequence(gMineModule, {3, 1}, 0b00101010); //{index, repeat}
    ENGINE_lightAddSequence(gMineModule, {4, 1}, 0b00101010); //{index, repeat}
    ENGINE_lightAddSequence(gMineModule, {5, 4}, 0b00101010); //{index, repeat}
    ENGINE_lightAddSequence(gMineModule, {0, 3}, 0b00101010); //{index, repeat}

    usleep(40000);
    ENGINE_lightSyncOperationBuffer(gMineModule);
    usleep(40000);
    ENGINE_lightSyncSequenceBuffer(gMineModule, 0b00111111);
    usleep(40000);
    ENGINE_lightStartSequence(gMineModule, 0x0770);
    usleep(40000);
}

void bonusEffectInit(void) {
    usleep(40000);
    ENGINE_lightClearOperationBuffer(gBonusModule);
    ENGINE_lightClearSequenceBuffer(gBonusModule, 0b00111111);

    // 0 blinking, white, fast
    ENGINE_lightAddOperation(gBonusModule, {0, 0xFF, 0xFF, 0xFF, 5, 5});

    // white blinking to circuit 2 and 3, buffer 1 for both
    ENGINE_lightAddSequence(gBonusModule, {0, 2}, 0b00010100); //{index, repeat}

    usleep(40000);
    ENGINE_lightSyncOperationBuffer(gBonusModule);
    usleep(40000);
    ENGINE_lightSyncSequenceBuffer(gBonusModule, 0b00111111);
    usleep(40000);
    ENGINE_lightStartSequence(gBonusModule, 0x0770);
    usleep(40000);
}

void PLUGIN_setup() {
    LIGHT_switchOffAllModules();
    LIGHT_setArenaLightsColor(gColorGray, 1);

    if (bonusEnabled == true || mineEnabled == true) {
        selectNewBonus();

        gvBonusShotCode = ENGINE_getTcvUInt("bonusShotCode", 101);
        if ((gvBonusShotCode < 101) || (gvBonusShotCode > 120)) {
            gvBonusShotCode = 101;
        }

        std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();

        if (lBonusModules.size() == 1) {
            // printf("Single module\n");
            gvSingleModule = 1;
            gBonusModule = lBonusModules[0].address;
            gMineModule = lBonusModules[0].address;
        }
        // uint8_t lBonusModulesCount = lBonusModules.size();
        // for(int i = 0; i < lBonusModulesCount; i++)

        // go thru all devices in lBonusModules
        for (DeviceT lModule : lBonusModules) {
            // printf("module %s\n",lModule.address.c_str());
            // send bonusShotCode to bonus module
            ENGINE_lightSetShootCode(lModule.address, bonusShotCode);

            // send color to selected bonus module, pulsing in buffer 1, 3 fast white blinks in buffer 2
            ENGINE_lightStartSequence(lModule.address, 0x0550); // stop all operations
            usleep(40000);
            ENGINE_lightClearOperationBuffer(lModule.address);
            ENGINE_lightClearSequenceBuffer(lModule.address, 0b00111111);

            // 0 blinking, white, fast
            ENGINE_lightAddOperation(lModule.address, {0, 0xFF, 0xFF, 0xFF, 5, 5});

            // 1 pulsing, red, slow
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 40, 40});
            // 2 pulsing, red, medium slow
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 30, 30});
            // 3 pulsing, red, medium
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 20, 20});
            // 4 pulsing, red, medium fast
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 10, 10});
            // 5 pulsing, red, fast
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 5, 5});

            // white blinking to circuit 2 and 3, buffer 1 for both
            ENGINE_lightAddSequence(lModule.address, {0, 2}, 0b00010100); //{index, repeat}

            // red pulsing for mine + white boom, to circuit 2 and 3, buffer 2 for both
            // length is 3,35 s
            ENGINE_lightAddSequence(lModule.address, {1, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {2, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {3, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {4, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {5, 4}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {0, 3}, 0b00101010); //{index, repeat}

            usleep(40000);
            ENGINE_lightSyncOperationBuffer(lModule.address);
            usleep(40000);
            ENGINE_lightSyncSequenceBuffer(lModule.address, 0b00111110);
            usleep(40000);
            ENGINE_lightStartSequence(lModule.address, 0x0770);
            usleep(40000);
        }
    }
}

void PLUGIN_destroyed() {
    LIGHT_setColorStandby();
}

void PLUGIN_gameLoaded() {
    gPlayersCount = ENGINE_getPlayersLength();
    if (singlePlayerTeams == 1 && gPlayersCount <= MAX_TEAMS) {
        gPlayersInTeam = 1;
    } else if (gPlayersCount < 5) {
        gPlayersInTeam = 1;
    } else {
        gPlayersInTeam = (gPlayersCount - 1) / 8 + 1; /*we want to use only 8 basic teams colors*/
        if (gPlayersInTeam < 2) {
            gPlayersInTeam = 2;
        }
    }
    gTeamsCount = gPlayersCount / gPlayersInTeam;
    if (gTeamsCount * gPlayersInTeam < gPlayersCount) {
        gTeamsCount++;
    }

    gvColorsTable[0] = color1;
    gvColorsTable[1] = color2;
    gvColorsTable[2] = color3;
    gvColorsTable[3] = color4;
    gvColorsTable[4] = color5;
    gvColorsTable[5] = color6;
    gvColorsTable[6] = color7;
    gvColorsTable[7] = color8;
    gvColorsTable[8] = color9;
    gvColorsTable[9] = color10;
    gvColorsTable[10] = color11;
    gvColorsTable[11] = color12;
    gvColorsTable[12] = color13;
    gvColorsTable[13] = color14;
    gvColorsTable[14] = color15;
    gvColorsTable[15] = color16;

#ifdef SIMULATION_PLUGIN
    for (uint8_t i = 0; i < MAX_TEAMS; i++) {
        printf("color %d: 0x%02X, 0x%02X, 0x%02X\n", i, gvColorsTable[i].red, gvColorsTable[i].green, gvColorsTable[i].blue);
    }
    printf("players %d, teams %d, players in team %d\n", gPlayersCount, gTeamsCount, gPlayersInTeam);
#endif
}

void PLUGIN_deviceIsReady(uint8_t aPlayerIndex) {
}

void PLUGIN_newLeader(const Player *apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    }
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();

    switch (time) {
    case 5:
        ENGINE_playSoundFromSoundSet(five);
        break;
    case 4:
        ENGINE_playSoundFromSoundSet(four);
        break;
    case 3:
        ENGINE_playSoundFromSoundSet(three);
        break;
    case 2:
        ENGINE_playSoundFromSoundSet(two);
        break;
    case 1:
        ENGINE_playSoundFromSoundSet(one);
        break;
    }

    if (state != 0x03 && time == 300) {
        ENGINE_playSoundFromSoundSet(Min5Remaining);
    }
    if (state != 0x03 && time == 60) {
        ENGINE_playSoundFromSoundSet(Min1Remaining);
    }

    if (state != 0x03) {
        uint8_t lResultTheSameTeam = 1;
        for (uint8_t i = 0; i < gPlayersCount; i++) {
            if (gPlayerData[0].teamIndex != gPlayerData[i].teamIndex) {
                lResultTheSameTeam = 0;
            }

            Player *p = ENGINE_getPlayerByIndex(i);
            int32_t score =
                pointsKill * p->kills +
                pointsDeath * (p->deaths - p->teamDeaths) +
                pointsHit * (p->hits - p->kills) +
                pointsPerShoot * p->usedAmmo +
                pointsDoubleKill * p->bonusKillCounter[2] +
                pointsMonsterKill * p->bonusKillCounter[3];
            p->score = score;
        }
        if (lResultTheSameTeam == 1) {
            if (gAllPlayersTheSameColor < 2) {
                gAllPlayersTheSameColor++;
            } else {
#ifdef SIMULATION_PLUGIN
                printf("round restart\n");
#endif
                /*TODO round restart*/
                // ENGINE_playSoundFromSoundSet(roundEnd);
                /*send Dead message*/
                uint8_t lMsg[2] = {'D', 0};
                for (uint8_t i = 0; i < gPlayersCount; i++) {
                    ENGINE_sendCustomMessage(lMsg, 2, i);
                }
                /*send new I message, randomly*/
                roundInitTeams();
                /*light of arena restart*/
            }
        } else {
            gAllPlayersTheSameColor = 0;
        }
    }

    /*leader team arena color*/
    arenaColorProcess();
}

void PLUGIN_gameStateChanged(uint8_t aState) {
#ifdef SIMULATION_PLUGIN
    printf("New state: %d\n", aState);
#endif
    if (aState == 0x01 && ENGINE_getPreviousGameState() == 0x03) {
        std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();
        if (lBonusModules.size() > 0) {
            if (bonusEnabled) {
                selectBonusActivateTime();
            }
            if (mineEnabled) {
                selectMineActivateTime();
            }
        }
    } else if (aState == 0x03) {
        roundInitTeams();
        for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
            uint8_t lMsg[2] = {'I', 0};

            lMsg[1] = gPlayerData[i].teamIndex;
            ENGINE_sendCustomMessage(lMsg, 2, i);
        }
    }
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    // printf("From plugin got hit %d, %d \n", aPlayerIndex, aWhoPlayerIndex);
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    // printf("From plugin killed %d, %d \n", aPlayerIndex, aWhoPlayerIndex);

    /*
        uint8_t lColorPlayer = playerIndexes[aPlayerIndex];
        uint8_t lColorWhoPlayer = playerIndexes[aWhoPlayerIndex];
        if (lColorWhoPlayer != lColorPlayer) {
            uint8_t lCount = 0;
            for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
                if (playerIndexes[i] == lColorPlayer) {
                    lCount++;
                }
            }
            if (lCount > 1) {
                gPlayersScore[aWhoPlayerIndex] += lCount * pointsKill;
            } else if (lCount == 1) {
                // Or maybe some bonus here
                gPlayersScore[aWhoPlayerIndex] += pointElimination;
            }

        } else {
            gPlayersFriendlyHits[aWhoPlayerIndex]++;
            gPlayersScore[aWhoPlayerIndex] += pointsFriendlyFire;
        }
        */
#ifdef SIMULATION_PLUGIN
    printf("aPlayerIndex: %d, aWhoPlayerIndex: %d\n", playerIndexes[aPlayerIndex], playerIndexes[aWhoPlayerIndex]);
#endif
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
#ifdef SIMULATION_PLUGIN
    // printf("data %d\n", aPlayerIndex);
#endif
    gPlayerData[aPlayerIndex].teamIndex = apData[0];

    /*
    playerIndexes[aPlayerIndex] = apData[0];
    uint8_t lIndex = playerIndexes[0];
    bool allSame = true;
    for (uint8_t i = 1; i < ENGINE_getPlayersLength(); i++) {
        if (lIndex != playerIndexes[i]) {
            allSame = false;
            break;
        }
    }*/
    /*
        if (allSame) {
            for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
                uint8_t data[2];
                data[0] = 'I';
                data[1] = i / playerCount;
                ENGINE_sendCustomMessage(data, 2, i);
            }
        }*/
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
    Player *p = ENGINE_getPlayerByCode(aCode);
#ifdef SIMULATION_PLUGIN
    printf("light hit %d, %s, %s\n", aCode, aAddress.c_str(), gBonusModule.c_str());
#endif

    if (bonusEnabled == true && (strcmp(aAddress.c_str(), gBonusModule.c_str()) == 0) && gvBonusNonactive == 0) {
        ENGINE_playSoundFromSoundSet(BonusTaken);
        ENGINE_clearTimer(gTimerBonusDeactive);
        gvBonusNonactive = 2;
        handlerBonusDeactivate();

        // blink to show hitted, once the sequence
        ENGINE_lightStartSequence(gBonusModule, 0x0550); // stop all operations
        usleep(40000);
        ENGINE_lightStartSequence(gBonusModule, 0x0770); // switch to buffer 1
        usleep(40000);
        ENGINE_lightStartSequence(gBonusModule, 0x0330); // do sequence once
        usleep(40000);

        if (bonusSendByXbee == true) {
            uint8_t lData2[2] = {'b', gvBonusIndex};
            ENGINE_sendCustomMessage((uint8_t *)lData2, 2, p->index);
        } else {
            ENGINE_lightSetShooting(gBonusModule, gvBonusIndex << 4, 0x05, 6); // info, shooting periode*100ms, number of shots
            usleep(40000);
        }

        // select next bonus
        selectNewBonus();
    }
}