#ifdef VSCODE
#include "../custom_variables_map.h"
#include "engine_def.h"
#include "sound_set_map.h"
#include <stdint.h>
#endif

#define DI_RANK 0x0001
#define DI_HEALTH 0x0002
#define DI_INIT 0x0004
#define DI_BONUS 0x0008
#define DI_ICON 0x0010
#define DI_SWITCH_BASIC 0x0020
#define DI_KILLED 0x0040
#define DI_HIT 0x0080

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

volatile uint16_t gvTimeHealthCounter = 0;

volatile uint8_t gvTimeMsgTimeout = 0;
volatile uint16_t gvTimeMsgTimeoutCounter = 0;

volatile uint8_t gvTimeDisplayHit = 0;
volatile uint16_t gvTimeDisplayHitCounter = 0;

volatile uint16_t gvLengthBlinking = 20;    // in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;        // in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;      // in 0,01*seconds
volatile uint16_t gvLengthMsgTimeout = 50;  // in 0,01*seconds
volatile uint16_t gvLengthDisplayHit = 300; // in 0,01*seconds

volatile uint8_t gvOrbs = 0;
volatile uint8_t gvOrbsTmp = 0;
volatile uint8_t gvOrbsCount = 0;
volatile uint8_t gvOrbReceived = 255;
    colors_t gvBaseColor = {200, 0, 0};
volatile uint8_t gvHittedModuleIndex = 0xFF;  // specify if some module was hitted last run of algorithm
volatile uint8_t gvHittedModuleLastState = 0; // state of module before hitted for restore light circuits settings
volatile uint8_t gvAlreadyDead = 0;
volatile uint8_t gvSendOrbMsg = 0;

volatile uint16_t gvDisplayIndex = 0;
volatile uint8_t gvOtherCode = 0;
volatile uint8_t gvDisplayLock = 0;
volatile uint8_t gvDisplayLockLast = 0;
const colors_t gcColorWhite = {0x80, 0x80, 0x80};
const colors_t gcColorGreen = {0x00, 0xF0, 0x00};
const colors_t gcColorRed = {0xF0, 0x00, 0x00};
const colors_t gcColorYellow = {0xF0, 0xF0, 0x00};

void PLUGIN_changedRank(uint8_t aRank, uint8_t aRankLast) {
    gvDisplayIndex |= DI_RANK;
}

/*
 * part in while loop in main
 */
void PLUGIN_mainLoop(void) {
    if (gvSendOrbMsg != 0) {
        uint8_t lData[2] = {2, gvOrbsTmp};
        gvSendOrbMsg = 0;
        ENGINE_sendCustomMessage(lData, 2, 0);
    }

    if (gvDisplayIndex != 0) {
        uint8_t lGameState = ENGINE_getGameState();
        uint8_t lDisplayDraw = 0;

        if ((gvDisplayIndex & DI_RANK) != 0) {
            gvDisplayIndex &= ~DI_RANK;
            ENGINE_selectDisplayBuffer(1);
            DISPLAY_rank(5, 2, 1);
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
        } else if ((gvDisplayIndex & DI_HEALTH) != 0) {
            gvDisplayIndex &= ~DI_HEALTH;
            ENGINE_selectDisplayBuffer(1);
            DISPLAY_health(68, 7, 3);
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
        } else if ((gvDisplayIndex & DI_BONUS) != 0) {
            gvDisplayIndex &= ~DI_BONUS;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_orbReceived(gvOrbReceived);
            gvOrbReceived = 255;
            gvDisplayLock = DL_BONUS;
            lDisplayDraw = 1;
            if (gvTimeDisplayHit == 1) {
                gvTimeDisplayHitCounter = 0;
            } else {
                gvTimeDisplayHit = 1;
            }
        } else if ((gvDisplayIndex & DI_ICON) != 0) {
            gvDisplayIndex &= ~DI_ICON;
            ENGINE_selectDisplayBuffer(1);
            DISPLAY_drawOrbs(4, 35, gvOrbs);
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
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
            if (gvTimeDisplayHit == 1) {
                gvTimeDisplayHitCounter = 0;
            } else {
                gvTimeDisplayHit = 1;
            }
        } else if ((gvDisplayIndex & DI_INIT) != 0) {
            gvDisplayIndex &= ~DI_INIT;
            ENGINE_selectDisplayBuffer(1);
            ENGINE_clearDisplayBuffer();
            DISPLAY_initLayout(3);
            gvDisplayIndex |= DI_HEALTH;
            gvDisplayIndex |= DI_RANK;
            gvDisplayIndex |= DI_ICON;
        }
        if (lDisplayDraw == 1) {
            ENGINE_drawBufferToDisplay(0);
        }
    }
}
/*
 * part in timer interrupt with period 10 ms
 */
void PLUGIN_timer10ms(void) {
    if (gvOrbs >> 3 & 1) {
        if (gvTimeHealthCounter < 10) {
            gvTimeHealthCounter++;
        } else {
            uint8_t lHealth = ENGINE_getHealth();
            lHealth += 2;
            gvDisplayIndex |= DI_HEALTH;
            if (lHealth > 100) {
                lHealth = 100;
            }
            ENGINE_setHealth(lHealth);
            gvTimeHealthCounter = 1;
        }
    } else {
        gvTimeHealthCounter = 0;
    }
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
            } else {
                // TODO some signalization of 0 life?
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

    /*msg timeout counter*/
    if (gvTimeMsgTimeout == 1) {
        if (gvTimeMsgTimeoutCounter < gvLengthMsgTimeout)
            gvTimeMsgTimeoutCounter++;
        else {
            gvSendOrbMsg = 0xFF;
            gvTimeMsgTimeoutCounter = 0;
            gvLengthMsgTimeout = 50;
        }
    } else {
        gvTimeMsgTimeoutCounter = 0;
    }

    /*display counter*/
    if (gvTimeDisplayHit == 1) {
        if (gvTimeDisplayHitCounter < gvLengthDisplayHit)
            gvTimeDisplayHitCounter++;
        else {
            gvTimeDisplayHitCounter = 0;
            gvTimeDisplayHit = 0;
            gvDisplayIndex |= DI_SWITCH_BASIC;
        }
    } else {
        gvTimeDisplayHitCounter = 0;
    }
}
/*
 * part in external interrupt for trigger press
 */
void PLUGIN_pressedTrigger(void) {
    uint8_t lGameState = ENGINE_getGameState();
    if ((lGameState == game_state_alive) || (lGameState == game_state_revival)) {
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) {
            if (ENGINE_getAmmo() > 0) {
                if (!(gvOrbs >> 0 & 1)) {
                    ENGINE_makeShoot((gvOrbs >> 2 & 1) ? 0x0F : 0x01, 0x00); /*use default shot strength, no shot custom info*/
                    ENGINE_decrementAmmo(1);
                    ENGINE_playShoot(0);
                } else {
                    ENGINE_makeShootContinuousStart((gvOrbs >> 2 & 1) ? 0x0F : 0x01, 0x00, 1, 0, 100);
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
/*
 * part in external interrupt for trigger release
 */
void PLUGIN_releasedTrigger(void) {
    if (gvOrbs >> 0 & 1) {
        ENGINE_makeShootContinuousStop();
    }
}
/*
 * part in external interrupt for user button press
 */
void PLUGIN_pressedUserButton(void) {
    ENGINE_toggleLightState();
}
/*
 * part in external interrupt for user button release
 */
void PLUGIN_releasedUserButton(void) {
}
/*
 * part in while loop in main after detecting hit from slave module
 */
void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
                       uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
    uint8_t lGameState = ENGINE_getGameState();

    if (lGameState == game_state_alive) {
        if (aHitStrength > 80) {
            aHitStrength = 50;
        } else {
            aHitStrength = 26; /*26 instead of 25 due to shield and /2, which will now lead to 13 (8 shots) instead of 12 (9 shots)*/
        }
        if (gvOrbs >> 1 & 1) {
            aHitStrength /= 2;
        }
        ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);
        gvDisplayIndex |= DI_HEALTH;
        /*process kill*/
        if (ENGINE_getHealth() == 0) {
            ENGINE_processDeath(aHitCode, aHitFlag);
            ENGINE_sendCustomMessage((uint8_t *)"H", 1, aHitCode);
            gvDisplayIndex |= DI_KILLED;
            gvDisplayIndex |= DI_ICON;
            gvOtherCode = aHitCode;
            if (gvOrbs != 0) {
                // gvSendOrbMsg = 0xFF;
                gvOrbsTmp = gvOrbs;
                gvLengthMsgTimeout = 10;
                gvTimeMsgTimeout = 1;
            }
            // uint8_t lData[2] = {2, gvOrbs};
            gvOrbs = 0;
            gvOrbsCount = 0;
            // ENGINE_sendCustomMessage(lData, 2, 0);
            ENGINE_setPeriodicInfoByte(gvOrbs, 0);
            ENGINE_setAllModulesColor(1, gvBaseColor);
            ENGINE_setAllModulesColor(2, gvBaseColor);
            ENGINE_setAllModulesState(1, 1, 0);
        }
    } else {
        gvAlreadyDead = 1;
    }
}
/*
 * part in while loop in main after detecting hit from slave module
 */
void PLUGIN_hitByTeam(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
                      uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
}
/*
 * part in while loop in main for selecting color and behavior of slave modules
 */
void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
                            uint8_t aHitCode, uint8_t aHealth, volatile uint8_t *apModulesState,
                            volatile uint8_t *apModulesDim1, volatile uint8_t *apModulesDim2,
                            volatile colors_t *apModulesColor1, volatile colors_t *apModulesColor2) {
    uint8_t lMessageTemp = 0;
    uint8_t i = 0;
    if (aState == state_game) {
        if ((aGameState == game_state_starting) && (gvTimeBlinkingLed == 1)) {
            lMessageTemp = LED1(led_basic) | LED2(led_basic);
        } else if (aGameState == game_state_alive) {
            // lMessageTemp = LED1(led_basic) | LED2(led_basic);
        } else if (aGameState == game_state_revival) {
            if (gvTimeBlinkingLed == 1)
                lMessageTemp = LED1(led_basic) | LED2(led_off);
            else
                lMessageTemp = LED1(led_basic) | LED2(led_basic);
        }
    } else {
    }
    if (aGameState != game_state_alive) {
        for (i = 0; i < MODULES_NUMBER; i++)
            apModulesState[i] = lMessageTemp;
    } else {
        // ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
        ENGINE_setAllModulesDim(aHealth, aHealth);
        if (gvHittedModuleIndex != 0xFF) {
            apModulesState[gvHittedModuleIndex] = gvHittedModuleLastState;
            for (i = 0; i < MODULES_NUMBER; i++)
                apModulesState[i] &= ~(VIBRATION(VIBRATION_ON));
            gvHittedModuleIndex = 0xFF;
        }
    }
    if (aHitCode != 0 && gvAlreadyDead == 0) { /* && (game_state == game_state_dead))*/
        /*change dim value, send for all chest slaves, not for weapon*/
        if (aGameState == game_state_dead) {
            /*reset dim to 100_*/
            ENGINE_setAllModulesDim(100, 100);
        } else {
            gvHittedModuleIndex = aHitCode - 1;
            gvHittedModuleLastState = apModulesState[gvHittedModuleIndex];
            // ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
            /*PLUGIN_setDimAccordingHealth(aHealth);*/
        }
        apModulesState[aHitCode - 1] |= LED1(
                                            led_stroboscope) |
                                        LED2(led_stroboscope);
        ENGINE_setVibrationAccordingHitFlag(aHitCode);
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
        apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_stroboscope));
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) {
            apModulesState[MODULE_MAIN_BOARD] |= LED2(led_special);
        } else {
            apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_special));
        }
    }
}
/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast) {
    gvTimeBlinking = 0;
    if (aGameStateLast == game_state_starting) {
        ENGINE_playSoundFromSoundSet(gameStarting);
        gvDisplayIndex |= DI_INIT;
    }
    ENGINE_setAllModulesState(1, 1, 0);
}
/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast) {
    gvTimeDeath = 1;
    ENGINE_playSoundFromSoundSet(death);
}
/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast) {
    gvTimeBlinking = 1;
    gvTimeRevival = 1;
    ENGINE_playSoundFromSoundSet(aliveAgain);
    ENGINE_setHealth(100);

    gvDisplayIndex |= DI_SWITCH_BASIC;
    gvDisplayIndex |= DI_HEALTH;
}
/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
    gvTimeBlinking = 1;
}
/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast) {
    ENGINE_setAllModulesDim(100, 100);
    ENGINE_setAllModulesState(1, 2, 0);
}
/*
 * part in data_process for processing custom message
 */
void PLUGIN_processCustomMessage(uint8_t *apData, uint16_t aLength,
                                 uint8_t aDevice) {
    if (aLength == 1) {
        if (apData[0] == (uint8_t)'H') {
            ENGINE_playSound(sfxKillDone);
            gvDisplayIndex |= DI_HIT;
            gvOtherCode = aDevice;
        }
    }
    if (apData[0] == 0) {
        if (!(gvOrbs >> apData[1] & 1)) {
            gvOrbsCount++;
            colors_t lColor;
            gvOrbReceived = apData[1];
            gvDisplayIndex |= DI_BONUS | DI_ICON;
            switch (apData[1]) {
            case 0:
                ENGINE_playSoundFromSoundSet(machineGunReceived);
                lColor = colorMachineGun;
                break;
            case 1:
                ENGINE_playSoundFromSoundSet(armorReceived);
                lColor = colorArmor;
                break;
            case 2:
                ENGINE_playSoundFromSoundSet(sniperReceived);
                lColor = colorSniper;
                break;
            case 3:
                ENGINE_playSoundFromSoundSet(healingReceived);
                lColor = colorHealing;
                break;
            }
            switch (gvOrbsCount) {
            case 1:
                ENGINE_setModuleColor(2, 1, lColor);
                ENGINE_setModuleColor(3, 1, lColor);
                ENGINE_setModuleColor(4, 1, lColor);
                ENGINE_setModuleColor(5, 1, lColor);
                ENGINE_setModuleState(2, 1, 2, 0);
                ENGINE_setModuleState(3, 1, 2, 0);
                ENGINE_setModuleState(4, 1, 2, 0);
                ENGINE_setModuleState(5, 1, 2, 0);
                break;
            case 2:
                ENGINE_setModuleColor(2, 2, lColor);
                ENGINE_setModuleColor(3, 2, lColor);
                ENGINE_setModuleColor(4, 2, lColor);
                ENGINE_setModuleColor(5, 2, lColor);
                ENGINE_setModuleColor(1, 2, lColor);
                ENGINE_setModuleColor(6, 2, lColor);
                ENGINE_setModuleState(2, 1, 2, 0);
                ENGINE_setModuleState(3, 1, 2, 0);
                ENGINE_setModuleState(4, 1, 2, 0);
                ENGINE_setModuleState(5, 1, 2, 0);
                ENGINE_setModuleState(1, 1, 2, 0);
                ENGINE_setModuleState(6, 1, 2, 0);
                break;
            case 3:
                ENGINE_setModuleColor(0, 1, lColor);
                ENGINE_setModuleColor(1, 1, lColor);
                ENGINE_setModuleColor(6, 1, lColor);
                ENGINE_setModuleColor(7, 1, lColor);
                ENGINE_setModuleState(0, 1, 2, 0);
                ENGINE_setModuleState(1, 1, 2, 0);
                ENGINE_setModuleState(6, 1, 2, 0);
                ENGINE_setModuleState(7, 1, 2, 0);
                break;
            case 4:
                ENGINE_setModuleColor(0, 2, lColor);
                ENGINE_setModuleColor(7, 2, lColor);
                ENGINE_setModuleState(0, 1, 2, 0);
                ENGINE_setModuleState(7, 1, 2, 0);
                break;
            }
        }
        uint8_t lData[2] = {1, apData[1]};
        ENGINE_sendCustomMessage(lData, 2, 0);
        gvOrbs |= 1 << apData[1];
        ENGINE_setPeriodicInfoByte(gvOrbs, 0);
    }
    if (apData[0] == 3) {
        gvTimeMsgTimeout = 0;
        gvOrbsTmp = 0;
    }

    ACHIEVEMENTS_customMessageBonusKill(apData, aLength, aDevice);
}
/*
 * part of PLUGIN_init, for users part of initialization, for example global vars for timers (length_death,...)
 */
void PLUGIN_customInit(volatile colors_t *apModulesColor1,
                       volatile colors_t *apModulesColor2, volatile uint8_t *apModulesDim1,
                       volatile uint8_t *apModulesDim2, uint8_t *apModulesVibrationStrength,
                       volatile uint8_t *apModulesState) {
    ENGINE_loadShot(0, sfxShoot);
    ENGINE_loadShot(1, sfxEmptyShoot);
    gvLengthDeath = ENGINE_getLengthDeath();
    gvLengthRevival = ENGINE_getLengthRevival();
    gvBaseColor.red = apModulesColor1[0].red;
    gvBaseColor.green = apModulesColor1[0].green;
    gvBaseColor.blue = apModulesColor1[0].blue;
    for (uint8_t i = 0; i < MODULES_NUMBER; i++) {
        apModulesColor1[i].red = gvBaseColor.red;
        apModulesColor1[i].green = gvBaseColor.green;
        apModulesColor1[i].blue = gvBaseColor.blue;
        apModulesColor2[i].red = gvBaseColor.red;
        apModulesColor2[i].green = gvBaseColor.green;
        apModulesColor2[i].blue = gvBaseColor.blue;
        apModulesState[i] = LED1(led_basic) | LED2(led_basic);
    }
    // ENGINE_setAllModulesColor(1, gvBaseColor);
    // ENGINE_setAllModulesColor(2, gvBaseColor);
    // ENGINE_setAllModulesState(1, 1, 0);
    ENGINE_setPeriodicInfoLength(1);
    ENGINE_controlDisplayFromPlugin();
    ENGINE_setModuleColor(MODULE_MAIN_BOARD, 2, gcColorWhite);

    ENGINE_playSoundFromSoundSet(loaded);
}
