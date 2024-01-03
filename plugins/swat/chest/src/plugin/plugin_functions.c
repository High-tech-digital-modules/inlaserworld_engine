#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_def.h"
#include "sound_set_map.h"
#include <stdint.h>
#endif

#define DI_RANK 0x0001
#define DI_INIT 0x0002
#define DI_SWITCH_BASIC 0x0004
#define DI_KILLED 0x0008
#define DI_HIT 0x0010

#define DL_NONE 0
#define DL_KILLED 1
#define DL_HIT 2

volatile uint8_t gvTimeBlinking = 0;
volatile uint16_t gvTimeBlinkingCounter = 0;
volatile uint8_t gvTimeBlinkingLed = 0;

volatile uint8_t gvTimeStroboscope = 0;
volatile uint16_t gvTimeStroboscopeCounter = 0;
volatile uint8_t gvTimeStroboscopeChangesCounter = 0;
volatile uint8_t gvTimeStroboscopeLed = 0;

volatile uint8_t gvTimeDeath = 0;
volatile uint16_t gvTimeDeathCounter = 0;

volatile uint8_t gvTimeRevival = 0;
volatile uint16_t gvTimeRevivalCounter = 0;

volatile uint8_t gvTimeDisplayHitKill = 0;
volatile uint16_t gvTimeDisplayHitKillCounter = 0;

volatile uint16_t gvLengthBlinking = 20;        // in 0,01*seconds
volatile uint16_t gvLengthStroboscope = 10;     // in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;            // in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;          // in 0,01*seconds
volatile uint16_t gvLengthDisplayHitKill = 300; // in 0,01*seconds

volatile uint8_t gvHitCodeLast = 0;
volatile uint8_t gvAlreadyDead = 0;

volatile uint16_t gvDisplayIndex = 0;
volatile uint8_t gvOtherCode = 0;
volatile uint8_t gvDisplayLock = 0;
volatile uint8_t gvDisplayLockLast = 0;
const colors_t gcColorWhite = {0x80, 0x80, 0x80};
const colors_t gcColorGreen = {0x00, 0xF0, 0x00};
const colors_t gcColorGreenDark = {0x00, 0x32, 0x00};
const colors_t gcColorRed = {0xF0, 0x00, 0x00};
const colors_t gcColorRedDark = {0x32, 0x00, 0x00};
const colors_t gcColorYellow = {0xF0, 0xF0, 0x00};

void PLUGIN_changedRank(uint8_t aRank, uint8_t aRankLast) {
    gvDisplayIndex |= DI_RANK;
}

/*
 * part in while loop in main
 */
void PLUGIN_mainLoop(void) {
    if (gvDisplayIndex != 0) {
        uint8_t lGameState = ENGINE_getGameState();
        uint8_t lDisplayDraw = 0;

        if ((gvDisplayIndex & DI_RANK) != 0) {
            gvDisplayIndex &= ~DI_RANK;
            ENGINE_selectDisplayBuffer(1);
            DISPLAY_rank(37, 18, 1);
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
        } else if ((gvDisplayIndex & DI_SWITCH_BASIC) != 0) {
            gvDisplayIndex &= ~DI_SWITCH_BASIC;
            // if (lGameState != game_state_dead) {
            ENGINE_selectDisplayBuffer(1);
            gvDisplayLock = DL_NONE;
            lDisplayDraw = 1;
            //}
        } else if ((gvDisplayIndex & DI_KILLED) != 0) {
            gvDisplayIndex &= ~DI_KILLED;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_killed(gvOtherCode);
            gvOtherCode = 0;
            gvDisplayLock = DL_KILLED;
            lDisplayDraw = 1;
            if (gvTimeDisplayHitKill == 1) {
                gvTimeDisplayHitKillCounter = 0;
            } else {
                gvTimeDisplayHitKill = 1;
            }
        } else if ((gvDisplayIndex & DI_HIT) != 0) {
            gvDisplayIndex &= ~DI_HIT;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_hit(gvOtherCode);
            gvOtherCode = 0;
            gvDisplayLock = DL_HIT;
            lDisplayDraw = 1;
            gvTimeDisplayHitKill = 1;
        } else if ((gvDisplayIndex & DI_INIT) != 0) {
            gvDisplayIndex &= ~DI_INIT;
            ENGINE_selectDisplayBuffer(1);
            ENGINE_clearDisplayBuffer();
            DISPLAY_initLayout(1);
            gvDisplayIndex |= DI_RANK;
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
        gvTimeBlinkingLed = 0;
    }

    /*stroboscope, 100 ms, 10x switched*/
    if (gvTimeStroboscope == 1) {
        if (gvTimeStroboscopeCounter < gvLengthStroboscope)
            gvTimeStroboscopeCounter++;
        else {
            gvTimeStroboscopeCounter = 1;
            gvTimeStroboscopeLed = (gvTimeStroboscopeLed + 1) % 2;
            gvTimeStroboscopeChangesCounter++;
            if (gvTimeStroboscopeChangesCounter == 10) {
                gvTimeStroboscopeChangesCounter = 0;
                gvTimeStroboscopeLed = 0;
                gvTimeStroboscope = 0;
                gvHitCodeLast = 0;
            }
        }
    } else {
        gvTimeStroboscopeCounter = 0;
        gvTimeStroboscopeLed = 0;
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

    /*display counter*/
    if (gvTimeDisplayHitKill == 1) {
        if (gvTimeDisplayHitKillCounter < gvLengthDisplayHitKill)
            gvTimeDisplayHitKillCounter++;
        else {
            gvTimeDisplayHitKillCounter = 0;
            gvTimeDisplayHitKill = 0;
            gvDisplayIndex |= DI_SWITCH_BASIC;
        }
    } else {
        gvTimeDisplayHitKillCounter = 0;
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
                ENGINE_makeShoot(0xFF, 0x00); /*use default shot strength, no shot custom info*/
                ENGINE_decrementAmmo(1);
                ENGINE_playShoot(0);
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
        ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);
        gvTimeStroboscope = 1;

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
                            uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t *apModulesState,
                            volatile uint8_t *apModulesDim1, volatile uint8_t *apModulesDim2,
                            volatile colors_t *apModulesColor1, volatile colors_t *apModulesColor2) {
    uint8_t lMessageTemp = 0;
    uint8_t i = 0;

    if (aState == state_game) {
        if ((aGameState == game_state_starting) && (gvTimeBlinkingLed == 1)) {
            lMessageTemp = LED1(led_basic) | LED2(led_basic);
        } else if (aGameState == game_state_alive) {
            lMessageTemp = LED1(led_off) | LED2(led_off);
        } else if (aGameState == game_state_revival) {
            if (gvTimeBlinkingLed == 1)
                lMessageTemp = LED1(led_basic) | LED2(led_basic);
            else
                lMessageTemp = LED1(led_off) | LED2(led_off);
        } else if (aGameState == game_state_dead) {
            lMessageTemp = LED1(led_basic) | LED2(led_basic);
        }
    } else {
    }

    for (i = 0; i < MODULES_NUMBER; i++)
        apModulesState[i] = lMessageTemp;

    if (aHitFlag != 0 && gvAlreadyDead == 0) { /* && (game_state == game_state_dead))*/
        gvHitCodeLast = aHitFlag;
        ENGINE_setVibrationAccordingHitFlag(aHitFlag);
    }
    gvAlreadyDead = 0;

    if (gvHitCodeLast != 0) {
        if (gvTimeStroboscopeLed == 1) {
            apModulesState[gvHitCodeLast - 1] = LED1(
                                                    led_special) |
                                                LED2(led_special);
        } else {
        }
    }

    /*backlight of display*/
    if (gvDisplayLock != gvDisplayLockLast) {
        gvDisplayLockLast = gvDisplayLock;
        switch (gvDisplayLock) {
        case DL_NONE:
            apModulesColor1[MODULE_MAIN_BOARD] = gcColorRedDark;
            break;
        case DL_KILLED:
            apModulesColor1[MODULE_MAIN_BOARD] = gcColorRedDark;
            break;
        case DL_HIT:
            apModulesColor1[MODULE_MAIN_BOARD] = gcColorGreenDark;
            break;
        default:
            break;
        }
    }

    if ((aState == state_game) || (aState == state_ending)) {
        apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_stroboscope));
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if ((((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) && (displayBacklight == 1 || aGameState == game_state_dead || aGameState == game_state_starting)) {
            apModulesState[MODULE_MAIN_BOARD] |= LED2(led_basic);
        } else {
            apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_basic));
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
}

/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
    gvTimeBlinking = 1;
    ENGINE_setLightState(1);
}

/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast) {
    ENGINE_setAllModulesDim(100, 100);
    ENGINE_setAllModulesState(1, 2, 0);
    ENGINE_setLightState(0);
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
    ACHIEVEMENTS_customMessageBonusKill(apData, aLength, aDevice);
}

/*
 * part of PLUGIN_init, for users part of initialization, for example global vars for timers (length_death,...)
 */
void PLUGIN_customInit(volatile colors_t *apModulesColor1,
                       volatile colors_t *apModulesColor2, volatile uint8_t *apModulesDim1,
                       volatile uint8_t *apModulesDim2, uint8_t *apModulesVibrationStrength,
                       volatile uint8_t *apModulesState) {
    colors_t lBasicColor = {50, 0, 0};
    colors_t lStroboscopeColor = {255, 255, 255};

    gvLengthDeath = ENGINE_getLengthDeath();
    gvLengthRevival = ENGINE_getLengthRevival();
    ENGINE_loadShot(0, sfxShoot);
    ENGINE_loadShot(1, sfxEmptyShoot);
    ENGINE_playSoundFromSoundSet(loaded);

    /*set basic color to dark red, special color to white (stroboscope)*/
    ENGINE_setAllModulesColor(1, lBasicColor);
    ENGINE_setAllModulesColor(2, lStroboscopeColor);
    ENGINE_setAllModulesDim(100, 100);

    ENGINE_controlDisplayFromPlugin();

    /*set shot strength to max, disable health*/
    ENGINE_setShotStrength(100);
}
