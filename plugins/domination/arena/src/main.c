#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_functions.h"
#include "sound_set_map.h"
#include "submodules.h"
#endif
/*
#ifndef SIMULATION
#define SIMULATION
#endif
*/
#define MAX_TEAMS 16

const ColorT gColorGrey = {0x10, 0x10, 0x10};
const ColorT gColorYellow = {0xFF, 0xFF, 0x00};
const ColorT gColorRed = {0xFF, 0x00, 0x00};
const ColorT gColorBlue = {0x00, 0x00, 0xFF};
const ColorT gColorBlack = {0x00, 0x00, 0x00};
ColorT gColorArena = {0x00, 0x00, 0x00};
const char pgLightBroadcastAddress[] = "000000000000000000";
std::vector<DeviceT> gBonusModules;
uint8_t gBonusModulesLength = 0;
uint8_t gAutospawnOneEnabled = 1;
uint8_t gAutospawnTwoEnabled = 1;
uint8_t gTeamOneCount = 0;
uint8_t gTeamTwoCount = 0;
int32_t gTeamOneScore = 0;
int32_t gTeamTwoScore = 0;
int32_t gTeamsCount[MAX_TEAMS] = {0};
int32_t gTeamsScore[MAX_TEAMS] = {0};
uint8_t gAutospawnEnabled[MAX_TEAMS] = {0};

typedef struct
{
    uint8_t team;
    uint8_t hp;
} bonusInfo_t;

bonusInfo_t gBonusInfo[20] = {0};

uint8_t teamIndexGet(uint8_t aPlayerIndex) {
    Player *lpPlayer = ENGINE_getPlayerByIndex(aPlayerIndex);
    uint8_t lTeamsCount = ENGINE_getTeamsLength();
    uint8_t lTeamIndex = 0;
    uint8_t lResult = 0;
    while (lTeamIndex < lTeamsCount && lResult == 0) {
        Team *lpTeam = ENGINE_getTeamByIndex(lTeamIndex);
        if (lpTeam->id == lpPlayer->idOfTeam) {
            lResult = 1;
        } else {
            lTeamIndex++;
        }
    }
    return lTeamIndex;
}

void autospawnTeamSend(uint8_t aTeam, uint8_t aEnabled) {
    uint8_t lPlayersCount = ENGINE_getPlayersLength();
    uint8_t lTeamsCount = ENGINE_getTeamsLength();
    uint8_t lMsg[2] = {'r', aEnabled};

    printf("autospawn %d, team %d, players:\n", aEnabled, aTeam);

    for (uint8_t i = 0; i < lPlayersCount; i++) {
        Player *lpPlayer = ENGINE_getPlayerByIndex(i);
        uint8_t lTeamIndex = teamIndexGet(i);

        //   uint8_t lTeam = (lpPlayer->nameOfTeam == "TeamRed" ? (uint8_t)1 : (uint8_t)2);
        if (lTeamIndex == aTeam) {
            ENGINE_sendCustomMessage(lMsg, 2, lpPlayer->index);
            printf("index %d, name %s\n", lpPlayer->index, lpPlayer->name.c_str());
        }
    }
}

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
                              uint16_t aOldValue,
                              uint16_t aNewValue,
                              uint16_t aMissedAmmoInRow) {
}

void PLUGIN_newLeader(const Player *apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    }
}

void PLUGIN_setup() {
    LIGHT_switchOffAllModules();
    LIGHT_setArenaLightsColor(gColorBlack, 1);

    gBonusModules = ENGINE_getBonusModules();
    for (DeviceT lModule : gBonusModules) {
        usleep(40000);
        ENGINE_lightSetColors(lModule.address, gColorYellow, gColorYellow, gColorYellow, 1);
    }

    gBonusModulesLength = gBonusModules.size();

    for (uint8_t i = 0; i < gBonusModulesLength; i++) {
        gBonusInfo[i].team = 255;
    }
}

void PLUGIN_destroyed() {
    LIGHT_setColorStandby();
    usleep(80000);
    ENGINE_lightSetShooting(pgLightBroadcastAddress, 0x00, 0x00, 0x00); // stop endless shooting
    usleep(80000);
}

void PLUGIN_gameLoaded() {
    uint8_t lPlayersCount = ENGINE_getPlayersLength();
    uint8_t lTeamsCount = ENGINE_getTeamsLength();

    printf("list of players:");
    for (uint8_t i = 0; i < lPlayersCount; i++) {
        Player *lpPlayer = ENGINE_getPlayerByIndex(i);
        uint8_t lTeamIndex = teamIndexGet(i);
        printf("%s  %s  %X\n", lpPlayer->idOfTeam.c_str(), lpPlayer->nameOfTeam.c_str(), lpPlayer->primaryColor);
        uint8_t lMsg[2] = {'t', lTeamIndex}; // lpPlayer.idOfTeam
        ENGINE_sendCustomMessage(lMsg, 2, lpPlayer->index);
    }

    for (uint8_t i = 0; i < lTeamsCount; i++) {
        ENGINE_setTeamPropNumber(i, "scoreDomination", 0);
    }

    for (uint8_t i = 0; i < lTeamsCount; i++) {
        gAutospawnEnabled[i] = 1;
        printf("team index %d, count %d, autospawn %d\n", i, gTeamsCount[i], gAutospawnEnabled[i]);
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

    for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {

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

    uint8_t lTeamsLength = ENGINE_getTeamsLength();
    for (int i = 0; i < lTeamsLength; i++) {
        gTeamsCount[i] = 0;
    }

    for (int i = 0; i < gBonusModulesLength; i++) {
        if (gBonusInfo[i].team != 255) {
            gTeamsCount[gBonusInfo[i].team]++;
        }
    }

    for (int i = 0; i < lTeamsLength; i++) {
        Team *lpTeam = ENGINE_getTeamByIndex(i);
        gTeamsScore[i] += gTeamsCount[i] * pointsPerBonus;
        ENGINE_setTeamPropNumber(i, "scoreDomination", gTeamsScore[i] + lpTeam->score);
    }
}

void PLUGIN_gameStateChanged(uint8_t aState) {
    printf("New state: %d\n", aState);
    if (aState == 0x01 && ENGINE_getPreviousGameState() == 0x03) {
    }

    /*TODO send info to players*/
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
    Player *lpPlayer = ENGINE_getPlayerByCode(aCode);
    uint8_t i, j;
    uint8_t found = 0;

    printf("hitted, %s, info (team) %d, player %d, number %d\n", aAddress.c_str(), aInfo, aCode, gBonusModulesLength);
    /*search index of bonus module*/
    for (i = 0; i < gBonusModulesLength; i++) {
        // printf(" %s\n", gBonusModules[i].address.c_str());
        if (gBonusModules[i].address == aAddress) {
            found = 1;
            break;
        }
    }

    aInfo = (aInfo >> 4) & 0x0F;
    printf("hitted, bonus index %d, bonus hp %d, bonus team %d\n", i, gBonusInfo[i].hp, gBonusInfo[i].team);

    if (found == 1) {
        if (gBonusInfo[i].team == 255) {
            /*shot when no team assigned to module*/
            gBonusInfo[i].team = aInfo;
            gBonusInfo[i].hp = 3;
            Team *lpTeam = ENGINE_getTeamByIndex(aInfo);
            ColorT lColor;
            lColor.red = (lpTeam->color >> 16) & 0xFF;
            lColor.green = (lpTeam->color >> 8) & 0xFF;
            lColor.blue = (lpTeam->color) & 0xFF;
            usleep(40000);
            ENGINE_lightSetColors(aAddress, lColor, lColor, lColor, 1);
            if (expertMode == 1) {
                usleep(40000);
                ENGINE_lightSetShootCode(aAddress, 110 + aInfo);
                usleep(40000);
                ENGINE_lightSetShooting(aAddress, 0x00, 0x04); // endles, info 0, code at line before, 1s periode of shooting (old value 0x0A)

                uint8_t lTeam = gBonusInfo[i].team;
                if (gTeamsCount[lTeam] < gBonusModulesLength) {
                    gTeamsCount[lTeam]++;
                }

                for (uint8_t j = 0; j < ENGINE_getTeamsLength(); j++) {
                    printf("team  %d: %d  \n", j, gTeamsCount[j]);
                }
                printf("\n");

                printf("team id %d count %d, autospawn %d\n", lTeam, gTeamsCount[lTeam], gAutospawnEnabled[lTeam]);
                if (gTeamsCount[lTeam] > 0 && gAutospawnEnabled[lTeam] == 1) {
                    printf("A\n");
                    autospawnTeamSend(lTeam, 0);
                    gAutospawnEnabled[lTeam] = 0;
                }
            }
        } else if (aInfo != gBonusInfo[i].team) {
            /*different team shot*/
            gBonusInfo[i].hp--;
            if (gBonusInfo[i].hp == 0) {
                if (expertMode == 1) {
                    usleep(40000);
                    ENGINE_lightSetShooting(aAddress, 0x00, 0x00, 0x00); // stop shooting

                    uint8_t lTeam = gBonusInfo[i].team;
                    if (gTeamsCount[lTeam] > 0) {
                        gTeamsCount[lTeam]--;
                    }

                    for (uint8_t j = 0; j < ENGINE_getTeamsLength(); j++) {
                        printf("team  %d: %d  \n", j, gTeamsCount[j]);
                    }
                    printf("\n");

                    printf("team id %d count %d, autospawn %d\n", lTeam, gTeamsCount[lTeam], gAutospawnEnabled[lTeam]);
                    if (gTeamsCount[lTeam] == 0 && gAutospawnEnabled[lTeam] == 0) {
                        printf("C\n");
                        autospawnTeamSend(lTeam, 1);
                        gAutospawnEnabled[lTeam] = 1;
                    }
                }
                gBonusInfo[i].team = 255;
                usleep(40000);
                ENGINE_lightSetColors(aAddress, gColorYellow, gColorYellow, gColorYellow, 1);

            } else {
                Team *lpTeam = ENGINE_getTeamByIndex(gBonusInfo[i].team);
                ColorT lColor;
                lColor.red = (lpTeam->color >> 16) & 0xFF;
                lColor.green = (lpTeam->color >> 8) & 0xFF;
                lColor.blue = (lpTeam->color) & 0xFF;
                lColor.red = lColor.red * gBonusInfo[i].hp / 3;
                lColor.green = lColor.green * gBonusInfo[i].hp / 3;
                lColor.blue = lColor.blue * gBonusInfo[i].hp / 3;
                usleep(40000);
                ENGINE_lightSetColors(aAddress, lColor, lColor, lColor, 1);
            }
        } else {
#ifdef SIMULATION_PLUGIN
            uint8_t lMsg[2] = {'h', 1};
            ENGINE_sendCustomMessage(lMsg, 2, lpPlayer->index);
#endif
        }
    }
}