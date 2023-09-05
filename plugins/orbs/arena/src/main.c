
#include <cmath>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_functions.h"
#include "sound_set_map.h"
#endif

#define IDX_MACHINE_GUN 0
#define IDX_ARMOR 1
#define IDX_SNIPER 2
#define IDX_HEALING 3

// #define LOG_ENABLED

uint8_t gOrbs = 15;
uint8_t gOrbsMirror[100];
uint8_t gOrbsMirrorBackup[100];
const ColorT gColorBlack = {0x00, 0x00, 0x00};
volatile int gvTimerBonusSendRepeat[4] = {0};
volatile uint8_t gvBonusSendRepeatIndex[4] = {255};
char gBonusAddresses[4][30] = {0};
FILE *fp;

void handlerMachineGun(void) {
    uint8_t lData[2] = {0, IDX_MACHINE_GUN};
    ENGINE_sendCustomMessage((uint8_t *)lData, 2, gvBonusSendRepeatIndex[IDX_MACHINE_GUN]);
    printf("timeout 0\n");
}

void handlerArmor(void) {
    uint8_t lData[2] = {0, IDX_ARMOR};
    ENGINE_sendCustomMessage((uint8_t *)lData, 2, gvBonusSendRepeatIndex[IDX_ARMOR]);
    printf("timeout 1\n");
}

void handlerSniper(void) {
    uint8_t lData[2] = {0, IDX_SNIPER};
    ENGINE_sendCustomMessage((uint8_t *)lData, 2, gvBonusSendRepeatIndex[IDX_SNIPER]);
    printf("timeout 2\n");
}

void handlerHealing(void) {
    uint8_t lData[2] = {0, IDX_HEALING};
    ENGINE_sendCustomMessage((uint8_t *)lData, 2, gvBonusSendRepeatIndex[IDX_HEALING]);
    printf("timeout 3\n");
}

void setOrbColor(std::string aAddress, ColorT aColor) {
    /*ENGINE_lightStartSequence(aAddress, 0x5550 ); //stop all operations
    usleep(40000);
    ENGINE_lightClearOperationBuffer(aAddress);
    ENGINE_lightClearSequenceBuffer(aAddress, 0b00111111);
    ENGINE_lightAddOperation(aAddress, { 0, aColor.red, aColor.green, aColor.blue, 30, 0 });
    ENGINE_lightAddSequence(aAddress, { 0, 1 }, 0b00010101);
    usleep(40000);
    ENGINE_lightSyncOperationBuffer(aAddress);
    usleep(40000);
    ENGINE_lightSyncSequenceBuffer(aAddress, 0b00111111);
    usleep(40000);
    ENGINE_lightStartSequence(aAddress, 0x7770 );
    usleep(40000);
    ENGINE_lightStartSequence(aAddress, 0x4440 );*/

    ENGINE_lightSetColors(aAddress, aColor, aColor, aColor, 1);
}

void distributeBOnusRandomly(void) {
    uint8_t index;

    srand(time(NULL)); // seed the random number generator with the current time

    memcpy(&gBonusAddresses[0][0], bonusMachineGun, 30);
    memcpy(&gBonusAddresses[1][0], bonusArmor, 30);
    memcpy(&gBonusAddresses[2][0], bonusSniper, 30);
    memcpy(&gBonusAddresses[3][0], bonusHealing, 30);
    /*gBonusAddresses[0] = bonusMachineGun;
    gBonusAddresses[1] = bonusArmor;
    gBonusAddresses[2] = bonusSniper;
    gBonusAddresses[3] = bonusHealing;*/

    // assign code to bonusMachineGun
    index = rand() % 4;
    memcpy(bonusMachineGun, &gBonusAddresses[index][0], 30);
    memcpy(&gBonusAddresses[index][0], &gBonusAddresses[3][0], 30);
    memcpy(&gBonusAddresses[3][0], bonusMachineGun, 30);
    // bonusMachineGun = gBonusAddresses[index].c_str();
    // gBonusAddresses[index] = gBonusAddresses[3];
    // gBonusAddresses[3] = bonusMachineGun;

    // assign code to bonusArmor
    index = rand() % 3;
    memcpy(bonusArmor, &gBonusAddresses[index][0], 30);
    memcpy(&gBonusAddresses[index][0], &gBonusAddresses[2][0], 30);
    memcpy(&gBonusAddresses[2][0], bonusArmor, 30);
    // bonusArmor = gBonusAddresses[index].c_str();
    // gBonusAddresses[index] = gBonusAddresses[2];
    // gBonusAddresses[2] = bonusArmor;

    // assign code to bonusSniper
    index = rand() % 2;
    memcpy(bonusSniper, &gBonusAddresses[index][0], 30);
    memcpy(&gBonusAddresses[index][0], &gBonusAddresses[1][0], 30);
    memcpy(&gBonusAddresses[1][0], bonusSniper, 30);
    // bonusSniper = gBonusAddresses[index].c_str();
    // gBonusAddresses[index] = gBonusAddresses[1];
    // gBonusAddresses[1] = bonusSniper;

    // assign code to bonusHealing
    memcpy(bonusHealing, &gBonusAddresses[0][0], 30);
    // bonusHealing = gBonusAddresses[0].c_str();
}

void PLUGIN_setup() {
    LIGHT_switchOffAllModules();
    LIGHT_setArenaLightsColor(colorArena, 1);

    if (bonusRandomDistribution == 1) {
        distributeBOnusRandomly();
    }

    setOrbColor(bonusMachineGun, colorMachineGun);
    setOrbColor(bonusArmor, colorArmor);
    setOrbColor(bonusSniper, colorSniper);
    setOrbColor(bonusHealing, colorHealing);

#ifdef LOG_ENABLED
    fp = fopen("/var/www/lasergame/orb_log.txt", "a+");
    if (fp != NULL) {
        time_t curr_time;
        curr_time = time(NULL);
        char *tm = ctime(&curr_time);
        fprintf(fp, "\n\n\nNew agent game %s\n", tm);
    }
#endif
}

void PLUGIN_destroyed() {
    LIGHT_setColorStandby();
#ifdef LOG_ENABLED
    if (fp != NULL) {
        fclose(fp);
    }
#endif
}

void PLUGIN_gameStateChanged(uint8_t state) {
}

void PLUGIN_newLeader(const Player *apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    }
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_main() {
    int32_t lTime = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch (lTime) {
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

    if (state != 0x03 && lTime == 300) {
        ENGINE_playSoundFromSoundSet(Min5Remaining);
    }
    if (state != 0x03 && lTime == 60) {
        ENGINE_playSoundFromSoundSet(Min1Remaining);
    }

    for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {

        Player *p = ENGINE_getPlayerByIndex(i);
        int32_t score =
            pointsKill * p->kills +
            pointsDeath * (p->deaths) +
            pointsHit * (p->hits - p->kills) +
            pointsPerShoot * p->usedAmmo +
            pointsDoubleKill * p->bonusKillCounter[2] +
            pointsMonsterKill * p->bonusKillCounter[3];
        p->score = score;
    }

#ifdef LOG_ENABLED
    if (fp != NULL) {
        time_t curr_time;
        curr_time = time(NULL);
        char *tm = ctime(&curr_time);
        fprintf(fp, "%s", tm);
        uint8_t lPlayerLength = ENGINE_getPlayersLength();
        for (int i = 0; i < lPlayerLength; i++) {
            fprintf(fp, " %d", gOrbsMirror[i]);
        }
        fprintf(fp, "\n");
        for (int i = 0; i < lPlayerLength; i++) {
            fprintf(fp, " %d", gOrbsMirrorBackup[i]);
        }
        fprintf(fp, "\n");
    }
#endif
}

void processOrbs(uint8_t aPlayerOrbs, uint8_t aPlayerIndex) {
    gOrbsMirror[aPlayerIndex] = 0;
    if (aPlayerOrbs >> IDX_MACHINE_GUN & 1) {
        gOrbs |= 1 << IDX_MACHINE_GUN;
        setOrbColor(bonusMachineGun, colorMachineGun);
        // ENGINE_lightStartSequence(bonusMachineGun, 0x4440 );
    }
    if (aPlayerOrbs >> IDX_ARMOR & 1) {
        gOrbs |= 1 << IDX_ARMOR;
        setOrbColor(bonusArmor, colorArmor);
        // ENGINE_lightStartSequence(bonusArmor, 0x4440 );
    }
    if (aPlayerOrbs >> IDX_SNIPER & 1) {
        gOrbs |= 1 << IDX_SNIPER;
        setOrbColor(bonusSniper, colorSniper);
        // ENGINE_lightStartSequence(bonusSniper, 0x4440 );
    }
    if (aPlayerOrbs >> IDX_HEALING & 1) {
        gOrbs |= 1 << IDX_HEALING;
        setOrbColor(bonusHealing, colorHealing);
        // ENGINE_lightStartSequence(bonusHealing, 0x4440 );
    }
}

void PLUGIN_receivedCustomData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
#ifdef LOG_ENABLED
        if (fp != NULL) {
            fprintf(fp, "rec %d %d\n", apData[0], aLen);
        }
#endif

    /*if received ACK for sending bonus to player, clear repeat timer sending feature*/
    if (apData[0] == 1 && aLen == 2) {
#ifdef LOG_ENABLED
        if (fp != NULL) {
            fprintf(fp, "received %d %d\n", apData[1], aPlayerIndex);
        }
#endif
        // printf("received %d %d\n",apData[1], aPlayerIndex);
        uint8_t lBonusIndex = apData[1];
        if (aPlayerIndex == gvBonusSendRepeatIndex[lBonusIndex]) {
            ENGINE_clearTimer(gvTimerBonusSendRepeat[lBonusIndex]);
            gvBonusSendRepeatIndex[lBonusIndex] = 255;
            // printf("ACKed\n");
#ifdef LOG_ENABLED
            if (fp != NULL) {
                fprintf(fp, "ACKed\n");
            }
#endif
        }
    }
    if (apData[0] == 2 && aLen == 2) {
#ifdef LOG_ENABLED
        if (fp != NULL) {
            if (gOrbsMirror[aPlayerIndex] != 0) {
                fprintf(fp, "killed player %d with orbs %d %d\n", aPlayerIndex, gOrbsMirror[aPlayerIndex], apData[1]);
            }
        }
#endif
        uint8_t lData[2] = {3, 0};
        ENGINE_sendCustomMessage((uint8_t *)lData, 2, aPlayerIndex);
        processOrbs(gOrbsMirror[aPlayerIndex], aPlayerIndex);
    }
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
#ifdef LOG_ENABLED
    if (fp != NULL) {
        if (gOrbsMirror[aPlayerIndex] != 0) {
            fprintf(fp, "killed player %d with orbs %d, by %d\n", aPlayerIndex, gOrbsMirror[aPlayerIndex], aWhoPlayerIndex);
        }
    }
#endif
    // processOrbs(gOrbsMirror[aPlayerIndex], aPlayerIndex);
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
    gOrbsMirrorBackup[aPlayerIndex] = apData[0];

    /*if(gOrbsMirror[aPlayerIndex] != apData[0]) {
      for(uint8_t i = 0; i < 4; i++) {
        if((gOrbsMirror[aPlayerIndex] >> i & 1) != (apData[0] >> i & 1)) {
          uint8_t lData[2] = { 0, i };
          ENGINE_sendCustomMessage((uint8_t*)lData, 2, aPlayerIndex);
        }
      }
    }*/
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
    Player *p = ENGINE_getPlayerByCode(aCode);
    if (!p) {
        return;
    }
    // setOrbColor(aAddress, {0, 0, 0});
    // ENGINE_lightStartSequence(aAddress, 0x5550 );
    uint8_t orbIndex = 255;
    if (aAddress.compare(bonusMachineGun) == 0) {
        orbIndex = IDX_MACHINE_GUN;
    } else if (aAddress.compare(bonusArmor) == 0) {
        orbIndex = IDX_ARMOR;
    } else if (aAddress.compare(bonusSniper) == 0) {
        orbIndex = IDX_SNIPER;
    } else if (aAddress.compare(bonusHealing) == 0) {
        orbIndex = IDX_HEALING;
    } else {
        return;
    }
    ENGINE_lightSetColors(aAddress, colorArena, gColorBlack, gColorBlack, 1);
    uint8_t lData[2] = {0, orbIndex};
    if (gOrbs >> orbIndex & 1) {
        ENGINE_sendCustomMessage((uint8_t *)lData, 2, p->index);
#ifdef LOG_ENABLED
        if (fp != NULL) {
            fprintf(fp, "send %d %d\n", orbIndex, p->index);
        }
#endif
        // printf("send %d %d\n",orbIndex, p->index);
        gvBonusSendRepeatIndex[orbIndex] = p->index;
        switch (orbIndex) {
        case IDX_MACHINE_GUN:
            gvTimerBonusSendRepeat[0] = ENGINE_setTimer(handlerMachineGun, 1000);
            ENGINE_playSoundFromSoundSet(machineGunTaken);
            break;
        case IDX_ARMOR:
            gvTimerBonusSendRepeat[1] = ENGINE_setTimer(handlerArmor, 1000);
            ENGINE_playSoundFromSoundSet(armorTaken);
            break;
        case IDX_SNIPER:
            gvTimerBonusSendRepeat[2] = ENGINE_setTimer(handlerSniper, 1000);
            ENGINE_playSoundFromSoundSet(sniperTaken);
            break;
        case IDX_HEALING:
            gvTimerBonusSendRepeat[3] = ENGINE_setTimer(handlerHealing, 1000);
            ENGINE_playSoundFromSoundSet(healingTaken);
            break;
        }
        gOrbsMirror[p->index] |= (1UL << orbIndex);
        gOrbs &= ~(1UL << orbIndex);
    }
}
