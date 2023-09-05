#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_def.h"
#include "sound_set_map.h"
#include <stdint.h>
#endif

#define DI_RANK 0x0001
#define DI_SCORE 0x0002
#define DI_HEALTH 0x0004
#define DI_LIFE 0x0008
#define DI_AMMO 0x0010
#define DI_INIT 0x0020
#define DI_BONUS 0x0040
#define DI_BONUS_TIME 0x0080
#define DI_SWITCH_BASIC 0x0100
#define DI_KILLED 0x0200
#define DI_HIT 0x0400

#define DL_NONE 0
#define DL_BONUS 1
#define DL_KILLED 2
#define DL_HIT 3

volatile uint8_t gvTimeBlinking = 0;
volatile uint16_t gvTimeBlinkingCounter = 0;
volatile uint8_t gvTimeBlinkingLed = 0;

volatile uint8_t gvTimeDeath = 0;
volatile uint16_t gvTimeDeathCounter = 0;

volatile uint8_t gvTimeRevival = 0;
volatile uint16_t gvTimeRevivalCounter = 0;

volatile uint8_t gvTimeBonus = 0;
volatile uint16_t gvTimeBonusCounter = 0;

volatile uint8_t gvTimePulse = 1;
volatile uint16_t gvTimePulseCounter = 0;

volatile uint8_t gvTimeBonusObtainedDelay = 0;
volatile uint16_t gvTimeBonusObtainedDelayCounter = 0;

volatile uint8_t gvTimeDisplayHit = 0;
volatile uint16_t gvTimeDisplayHitCounter = 0;

volatile uint16_t gvLengthBlinking = 20;            // in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;                // in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;              // in 0,01*seconds
volatile uint16_t gvLengthBonus = 3000;             // in 0,01*seconds
volatile uint16_t gvLengthBonusObtainedDelay = 500; // in 0,01*seconds
volatile uint16_t gvLengthDisplayHit = 300;         // in 0,01*seconds

// volatile static char new_filename[50];
volatile uint8_t gvBonusObtained = 0;
static const uint8_t cPulseIncrement = 10;
volatile uint16_t gvMineHits = 0;

const uint16_t gcLengthBonusImmortality = 1500;  // in 0,01*seconds
const uint16_t gcLengthBonusInvisibility = 3000; // in 0,01*seconds
const uint16_t gcLengthBonusMachineGun = 3000;   // in 0,01*seconds

typedef enum {
    bonusNone,
    bonusMachineGun,
    bonusInvisibility,
    bonusImmortality,
    bonusRecoloration
} bonusType; // gvActualBonus = bonusNone;

volatile static bonusType gvActualBonus = bonusNone;
volatile uint8_t gvAlreadyDead = 0;

volatile uint16_t gvDisplayIndex = 0;
volatile uint8_t gvOtherCode = 0;
volatile uint8_t gvDisplayLock = 0;
volatile uint8_t gvDisplayLockLast = 0;
const colors_t gcColorWhite = {0x80, 0x80, 0x80};
const colors_t gcColorGreen = {0x00, 0xF0, 0x00};
const colors_t gcColorRed = {0xF0, 0x00, 0x00};
const colors_t gcColorYellow = {0xF0, 0xF0, 0x00};

void bonusMachineGunStop(void) {
    if (gvActualBonus == bonusMachineGun) {
        ENGINE_makeShootContinuousStop();
    }
}

void bonusImmortalityStop(void) {
    if (gvActualBonus == bonusImmortality) {
        ENGINE_setAllModulesDim(100, 100);
    }
}

void bonusObtained(uint8_t aBonusType) {
    bonusMachineGunStop();
    bonusImmortalityStop();
    gvActualBonus = aBonusType;
    gvTimeBonusCounter = 0;
    gvTimeBonus = 1;
    switch (gvActualBonus) {
    case bonusMachineGun:
        ENGINE_playSoundFromSoundSet(machine_gun);
        gvLengthBonus = gcLengthBonusMachineGun;
        break;
    case bonusInvisibility:
        ENGINE_playSoundFromSoundSet(invisibility);
        gvLengthBonus = gcLengthBonusInvisibility;
        break;
    case bonusImmortality:
        ENGINE_playSoundFromSoundSet(immortality);
        gvLengthBonus = gcLengthBonusImmortality;
        break;
    }
    gvDisplayIndex |= DI_BONUS;
}

/*
static FILE *open_next_file(char *filename) {
    int i = 1;
    bool file_exists = true;
    FILE *fp;

    while (file_exists) {
        snprintf(new_filename, sizeof new_filename, "%s%d", filename, i);
        fp = fopen(new_filename, "r");
        file_exists = (fp != NULL);
        if (fp != NULL) {
            fclose(fp);
        }
        i++;
    }

    fp = fopen(new_filename, "w");
    return fp;
}

void logToFile(char *text) {
  FILE *fp = fopen(new_filename, "a");
  fprintf(fp, text);
  fclose(fp);
}*/

void PLUGIN_changedRank(uint8_t aRank, uint8_t aRankLast) {
    gvDisplayIndex |= DI_RANK;
}

void PLUGIN_changedScore(int32_t aScore, int32_t aScoreLast) {
    // gvDisplayIndex |= DI_SCORE;
}

void PLUGIN_mainLoop(void) {
    if (gvDisplayIndex != 0) {
        uint8_t lGameState = ENGINE_getGameState();
        uint8_t lDisplayDraw = 0;

        if ((gvDisplayIndex & DI_RANK) != 0) {
            gvDisplayIndex &= ~DI_RANK;
            ENGINE_selectDisplayBuffer(1);
            if (shootPower == 100) {
                DISPLAY_rank(37, 18, 1);
            } else {
                DISPLAY_rank(37, 2, 1);
            }
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
        } else if ((gvDisplayIndex & DI_HEALTH) != 0) {
            gvDisplayIndex &= ~DI_HEALTH;
            if (shootPower != 100) {
                ENGINE_selectDisplayBuffer(1);
                DISPLAY_health(15, 39, 1);
                lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
            }

        } else if ((gvDisplayIndex & DI_BONUS) != 0) {
            gvDisplayIndex &= ~DI_BONUS;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_bonus(gvActualBonus);
            gvDisplayLock = DL_BONUS;
            lDisplayDraw = 1;
        } else if ((gvDisplayIndex & DI_BONUS_TIME) != 0) {
            gvDisplayIndex &= ~DI_BONUS_TIME;
            if (gvDisplayLock == DL_BONUS) {
                if (lGameState != game_state_dead) {
                    ENGINE_selectDisplayBuffer(2);
                    DISPLAY_bonusTime(gvLengthBonus - gvTimeBonusCounter);
                }
                lDisplayDraw = 1;
            }
        } else if ((gvDisplayIndex & DI_SWITCH_BASIC) != 0) {
            gvDisplayIndex &= ~DI_SWITCH_BASIC;
            if (lGameState != game_state_dead) {
                ENGINE_selectDisplayBuffer(1);
                gvDisplayLock = DL_NONE;
                lDisplayDraw = 1;
            }
        } else if ((gvDisplayIndex & DI_KILLED) != 0) {
            gvDisplayIndex &= ~DI_KILLED;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_killed(gvOtherCode);
            gvOtherCode = 0;
            gvDisplayLock = DL_KILLED;
            lDisplayDraw = 1;
        } else if ((gvDisplayIndex & DI_HIT) != 0) {
            gvDisplayIndex &= ~DI_HIT;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_hit(gvOtherCode);
            gvOtherCode = 0;
            gvDisplayLock = DL_HIT;
            lDisplayDraw = 1;
            gvTimeDisplayHit = 1;
        } else if ((gvDisplayIndex & DI_INIT) != 0) {
            gvDisplayIndex &= ~DI_INIT;
            ENGINE_selectDisplayBuffer(1);
            ENGINE_clearDisplayBuffer();
            if (shootPower == 100) {
                DISPLAY_initLayout(1);
            } else {
                DISPLAY_initLayout(2);
                gvDisplayIndex |= DI_HEALTH;
            }
            gvDisplayIndex |= DI_RANK;
        }
        if (lDisplayDraw == 1) {
            ENGINE_drawBufferToDisplay(0);
        }
    }
}

void PLUGIN_timer10ms(void) {
    /*blinking every 200 ms*/
    if (gvTimeBlinking == 1) {
        if (gvTimeBlinkingCounter < gvLengthBlinking)
            gvTimeBlinkingCounter++;
        else {
            gvTimeBlinkingCounter = 1;
            gvTimeBlinkingLed = (gvTimeBlinkingLed + 1) % 2;
        }
    } else {
        gvTimeBlinkingCounter = 0;
        gvTimeBlinkingLed = 1;
    }

    /*death counter*/
    if (gvTimeDeath == 1) {
        if (gvTimeDeathCounter < gvLengthDeath)
            gvTimeDeathCounter++;
        else {
            gvTimeDeath = 0;
            if (ENGINE_getLife() > 0) {
                ENGINE_setGameState(game_state_revival);
            }
        }
    } else {
        gvTimeDeathCounter = 0;
    }

    /*revival counter*/
    if (gvTimeRevival == 1) {
        if (gvTimeRevivalCounter < gvLengthRevival)
            gvTimeRevivalCounter++;
        else {
            gvTimeRevival = 0;
            ENGINE_setGameState(game_state_alive);
        }
    } else {
        gvTimeRevivalCounter = 0;
    }

    /*bonus obtained delay counter*/
    if (gvTimeBonusObtainedDelay == 1) {
        if (gvTimeBonusObtainedDelayCounter < gvLengthBonusObtainedDelay)
            gvTimeBonusObtainedDelayCounter++;
        else {
            gvTimeBonusObtainedDelay = 0;
            gvTimeBonusObtainedDelayCounter = 0;
        }
    } else {
        gvTimeBonusObtainedDelayCounter = 0;
    }

    /*bonus counter*/
    if (gvTimeBonus == 1) {
        if (gvTimeBonusCounter < gvLengthBonus) {
            gvTimeBonusCounter++;
            if (gvTimeBonusCounter % 10 == 0) {
                gvDisplayIndex |= DI_BONUS_TIME;
            }
        } else {
            gvTimeBonus = 0;
            bonusMachineGunStop();
            bonusImmortalityStop();
            gvActualBonus = bonusNone;
            gvDisplayIndex |= DI_SWITCH_BASIC;
        }
    } else {
        gvTimeBonusCounter = 0;
    }

    /*pulsing counter*/
    if (gvActualBonus == bonusImmortality) {
        if (gvTimePulse == 1) {
            if (gvTimePulseCounter < 100 - cPulseIncrement)
                gvTimePulseCounter += cPulseIncrement;
            else {
                gvTimePulse = 2;
                gvTimePulseCounter = 100;
            }
        } else if (gvTimePulse == 2) {
            if (gvTimePulseCounter > cPulseIncrement)
                gvTimePulseCounter -= cPulseIncrement;
            else {
                gvTimePulse = 1;
                gvTimePulseCounter = 0;
            }
        } else {
            gvTimePulseCounter = 0;
        }
    } else {
        gvTimePulseCounter = 0;
        gvTimePulse = 1;
    }

    /*display counter*/
    if (gvTimeDisplayHit == 1) {
        if (gvTimeDisplayHitCounter < gvLengthDisplayHit)
            gvTimeDisplayHitCounter++;
        else {
            gvTimeDisplayHitCounter = 0;
            gvTimeDisplayHit = 0;
            if (gvTimeBonus == 1) {
                gvDisplayIndex |= DI_BONUS;
            } else {
                gvDisplayIndex |= DI_SWITCH_BASIC;
            }
        }
    } else {
        gvTimeDisplayHitCounter = 0;
    }
}

void PLUGIN_pressedTrigger(void) {
    uint8_t lGameState = ENGINE_getGameState();

    if ((lGameState == game_state_alive) || (lGameState == game_state_revival)) {
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) {
            if (ENGINE_getAmmo() > 0) {
                if (gvActualBonus == bonusMachineGun) {
                    ENGINE_makeShootContinuousStart(0xFF, 0x00, 1, 0, 100);
                } else {
                    ENGINE_makeShoot(0xFF, 0x00); /*use default shot strength, no shot custom info*/
                    ENGINE_decrementAmmo(1);
                    ENGINE_playShoot(0);
                    gvDisplayIndex |= DI_AMMO;
                }
            } else {
                ENGINE_playShoot(1);
            }
        } else {
            ENGINE_playShoot(1);
        }
    } else if (lGameState == game_state_dead) {
        ENGINE_playShoot(1);
    }
}

void PLUGIN_releasedTrigger(void) {
    if (gvActualBonus == bonusMachineGun) {
        ENGINE_makeShootContinuousStop();
    }
}

void PLUGIN_pressedUserButton(void) {
    ENGINE_toggleLightState();
}

void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
                       uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
    uint8_t lGameState = ENGINE_getGameState();
    aHitStrength = shootPower;

    if (lGameState == game_state_alive) {
        if ((aHitCode == bonusShotCode) && (aHitCustomInfo != 0)) {
            if (gvTimeBonusObtainedDelay == 1) {
                return;
            }
            gvBonusObtained = 1;
            bonusObtained(aHitCustomInfo);
            gvTimeBonusObtainedDelay = 1;
            ENGINE_setVibrationAccordingHitFlag(9); // weapon vibration
            return;
        }

        if (gvActualBonus == bonusImmortality) {
            return;
        }

        if (aHitCode == bonusShotCode) {
            gvMineHits++;
            ENGINE_setPeriodicInfoByte((gvMineHits >> 8) & 0xFF, 0);
            ENGINE_setPeriodicInfoByte(gvMineHits & 0xFF, 1);
        }

        ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);
        gvDisplayIndex |= DI_HEALTH;

        /*process kill*/
        if (ENGINE_getHealth() == 0) {
            ENGINE_processDeath(aHitCode, aHitFlag);
            ENGINE_sendCustomMessage((uint8_t *)"H", 1, aHitCode);
            gvDisplayIndex |= DI_KILLED;
            gvOtherCode = aHitCode;
        }
    } else {
        gvAlreadyDead = 1;
    }
}

void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
                            uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t *apModulesState,
                            volatile uint8_t *apModulesDim1, volatile uint8_t *apModulesDim2,
                            volatile colors_t *apModulesColor1, volatile colors_t *apModulesColor2) {
    uint8_t lMessageTemp = 0;
    uint8_t i = 0;

    if (aState == state_game) {
        if ((aGameState == game_state_starting) && (gvTimeBlinkingLed == 1)) {
            lMessageTemp = LED1(led_basic) | LED2(led_basic);
        } else if (aGameState == game_state_alive) {
            lMessageTemp = LED1(led_basic) | LED2(led_basic);
        } else if (aGameState == game_state_revival) {
            if (gvTimeBlinkingLed == 1)
                lMessageTemp = LED1(led_basic) | LED2(led_special);
            else
                lMessageTemp = LED1(led_basic) | LED2(led_basic);
        }
    } else {
    }

    if (aGameState != game_state_alive) {
        for (i = 0; i < MODULES_NUMBER; i++)
            apModulesState[i] = lMessageTemp;
    } else {
        if (gvActualBonus == bonusInvisibility) {
            for (i = 0; i < MODULES_NUMBER; i++)
                apModulesState[i] = 0;
        } else if (gvActualBonus == bonusImmortality) {
            for (i = 0; i < MODULES_NUMBER; i++) {
                apModulesState[i] = lMessageTemp;
                apModulesDim1[i] = gvTimePulseCounter;
                apModulesDim2[i] = gvTimePulseCounter;
            }
        } else {
            ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
        }
    }

    if (gvBonusObtained == 1) {
        gvBonusObtained = 0;
        apModulesState[8] |= VIBRATION(VIBRATION_ON);
    }

    if ((aHitFlag != 0) && (gvTimeBonusObtainedDelay == 0) && gvAlreadyDead == 0) { /* && (game_state == game_state_dead))*/
        /*change dim value, send for all chest slaves, not for weapon*/
        if (aGameState == game_state_dead) {
            /*reset dim to 100_*/
            ENGINE_setAllModulesDim(100, 100);
        } else {
            ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
        }
        apModulesState[aHitFlag - 1] |= LED1(
                                            led_stroboscope) |
                                        LED2(led_stroboscope);
        ENGINE_setVibrationAccordingHitFlag(aHitFlag);
    }
    gvAlreadyDead = 0;

    /*backlight of display*/
    if (gvDisplayLock != gvDisplayLockLast) {
        gvDisplayLockLast = gvDisplayLock;
        switch (gvDisplayLock) {
        case DL_NONE:
            apModulesColor2[MODULE_MAIN_BOARD] = gcColorWhite;
            break;
        case DL_KILLED:
            apModulesColor2[MODULE_MAIN_BOARD] = gcColorRed;
            break;
        case DL_HIT:
            apModulesColor2[MODULE_MAIN_BOARD] = gcColorGreen;
            break;
        case DL_BONUS:
            apModulesColor2[MODULE_MAIN_BOARD] = gcColorYellow;
            break;
        default:
            break;
        }
    }

    if ((aState == state_game) || (aState == state_ending)) {
        apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_special));
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) {
            apModulesState[MODULE_MAIN_BOARD] |= LED2(led_special);
        } else {
            apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_special));
        }
    }
}

void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast) {
    // logToFile("Alive");
    gvTimeBlinking = 0;
    if (aGameStateLast == game_state_starting) {
        ENGINE_playSoundFromSoundSet(gameStarting);
        gvDisplayIndex |= DI_INIT;
    }
}

void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast) {
    gvTimeDeath = 1;
    ENGINE_playSoundFromSoundSet(death);
    // logToFile("Death");
}

void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast) {
    gvTimeBlinking = 1;
    gvTimeRevival = 1;
    ENGINE_playSoundFromSoundSet(aliveAgain);
    ENGINE_setHealth(100);

    if (gvTimeBonus == 1) {
        gvDisplayIndex |= DI_BONUS;
    } else {
        gvDisplayIndex |= DI_SWITCH_BASIC;
    }
    gvDisplayIndex |= DI_HEALTH;
    // logToFile("Revival");
}

void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
    gvTimeBlinking = 1;
    // logToFile("Starting");
}

void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast) {
    ENGINE_setAllModulesDim(100, 100);
    ENGINE_setAllModulesState(1, 2, 0);
    // logToFile("Ending");
}

void PLUGIN_processCustomMessage(uint8_t *apData, uint16_t aLength,
                                 uint8_t aDevice) {
    if (aLength == 1) {
        if (apData[0] == (uint8_t)'H') {
            ENGINE_playSound(sfxKillDone);
            gvDisplayIndex |= DI_HIT;
            gvOtherCode = aDevice;
        }
    }
    if (bonusEnabled == 1) {
        if ((apData[0] == (uint8_t)'b') && (aLength == 2)) {
            bonusObtained(apData[1]);
        }
    }
    ACHIEVEMENTS_customMessageBonusKill(apData, aLength, aDevice);
}

void PLUGIN_customInit(volatile colors_t *apModulesColor1,
                       volatile colors_t *apModulesColor2, volatile uint8_t *apModulesDim1,
                       volatile uint8_t *apModulesDim2, uint8_t *apModulesVibrationStrength,
                       volatile uint8_t *apModulesState) {
    gvLengthDeath = ENGINE_getLengthDeath();
    gvLengthRevival = ENGINE_getLengthRevival();
    ENGINE_loadShot(0, sfxShoot);
    ENGINE_loadShot(1, sfxEmptyShoot);
    ENGINE_playSoundFromSoundSet(loaded);
    ENGINE_setShotStrength(shootPower);

    ENGINE_setPeriodicInfoLength(2);
    ENGINE_controlDisplayFromPlugin();
    ENGINE_setModuleColor(MODULE_MAIN_BOARD, 2, gcColorWhite);
    /*
      FILE *fp = open_next_file("/tmp/chest_log_");
      fprintf(fp, "log begin\r\n");
      fclose(fp);
      */
}