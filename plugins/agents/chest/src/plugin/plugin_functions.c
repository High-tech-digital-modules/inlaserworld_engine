/*
 * p_main.c
 *
 *  Created on: 13. 9. 2020
 *      Author: Bodie
 */
#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_def.h"
#include "sound_set_map.h"
#include <stdint.h>
#endif

#define CODE_LAST_SIZE 4

#define DI_RANK 0x0001
#define DI_INIT 0x0002
#define DI_SWITCH_BASIC 0x0004
#define DI_KILLED 0x0008
#define DI_HIT 0x0010
#define DI_AGENT 0x0020
#define DI_ICON 0x0040

#define DL_NONE 0
#define DL_KILLED 1
#define DL_HIT 2
#define DL_AGENT 3

volatile uint8_t gvTimeBlinking = 0;
volatile uint16_t gvTimeBlinkingCounter = 0;
volatile uint8_t gvTimeBlinkingLed = 0;

volatile uint8_t gvTimeDeath = 0;
volatile uint16_t gvTimeDeathCounter = 0;

volatile uint8_t gvTimeRevival = 0;
volatile uint16_t gvTimeRevivalCounter = 0;

volatile uint8_t gvTimeAgentReceived = 0;
volatile uint16_t gvTimeAgentReceivedCounter = 0;

volatile uint8_t gvTimeDisplayHit = 0;
volatile uint16_t gvTimeDisplayHitCounter = 0;

volatile uint16_t gvLengthBlinking = 20;       // in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;           // in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;         // in 0,01*seconds
volatile uint16_t gvLengthAgentReceived = 200; // in 0,01*seconds
volatile uint16_t gvLengthDisplayHit = 300;    // in 0,01*seconds

volatile uint8_t gvIsAgent = 0;
volatile uint8_t gvAgentBuffered = 0;
volatile uint8_t gvChestCodeLast[CODE_LAST_SIZE] = {0};
volatile uint8_t gvBackupCodeLast[CODE_LAST_SIZE] = {0};
volatile uint8_t gvAlreadyDead = 0;

volatile uint16_t gvDisplayIndex = 0;
volatile uint8_t gvOtherCode = 0;
volatile uint8_t gvDisplayLock = 0;
volatile uint8_t gvDisplayLockLast = 0;
const colors_t gcColorWhite = {0x80, 0x80, 0x80};
const colors_t gcColorGreen = {0x00, 0xF0, 0x00};
const colors_t gcColorRed = {0xF0, 0x00, 0x00};
const colors_t gcColorYellow = {0xF0, 0xF0, 0x00};

void clearCodeLastArray(uint8_t *apCodeArray) {
    uint8_t i;
    for (i = 0; i < CODE_LAST_SIZE; i++) {
        apCodeArray[i] = 0;
    }
}

void addCodeLastArray(uint8_t *apCodeArray, uint8_t aCode) {
    uint8_t i;
    for (i = 1; i < CODE_LAST_SIZE; i++) {
        apCodeArray[i] = apCodeArray[i - 1];
    }
    apCodeArray[0] = aCode;
}

/*
 * checks if apCodeArray contains aCode, if yes, returns 1, otherwice returns 0
 */
uint8_t checkCodeLastArray(uint8_t *apCodeArray, uint8_t aCode) {
    uint8_t i;
    for (i = 0; i < CODE_LAST_SIZE; i++) {
        if (apCodeArray[i] == aCode) {
            return 1;
        }
    }
    return 0;
}

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
            if (gvIsAgent == 0) {
                DISPLAY_rank(37, 18, 1);
            } else {
                DISPLAY_rank(8, 18, 1);
            }
            lDisplayDraw = (gvDisplayLock == DL_NONE ? 1 : 0);
        } else if ((gvDisplayIndex & DI_ICON) != 0) {
            gvDisplayIndex &= ~DI_ICON;
            gvDisplayIndex |= DI_RANK;
            ENGINE_selectDisplayBuffer(1);
            ENGINE_fillRectangle(3, 3, 122, 58, 0);
            if (gvIsAgent == 1) {
                DISPLAY_drawAgent(80, 12);
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
            if (gvTimeDisplayHit == 1) {
                gvTimeDisplayHitCounter = 0;
            } else {
                gvTimeDisplayHit = 1;
            }
        } else if ((gvDisplayIndex & DI_AGENT) != 0) {
            gvDisplayIndex &= ~DI_AGENT;
            ENGINE_selectDisplayBuffer(2);
            ENGINE_clearDisplayBuffer();
            DISPLAY_agent(gvAgentBuffered);
            gvDisplayLock = DL_AGENT;
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
            DISPLAY_initLayout(1);
            if (gvIsAgent == 1) {
                gvDisplayIndex |= DI_ICON;
            } else {
                gvDisplayIndex |= DI_RANK;
            }
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

    /*agent received counter*/
    if (gvTimeAgentReceived == 1) {
        if (gvTimeAgentReceivedCounter < gvLengthAgentReceived)
            gvTimeAgentReceivedCounter++;
        else {
            gvTimeAgentReceived = 0;
            clearCodeLastArray(gvBackupCodeLast);
            clearCodeLastArray(gvChestCodeLast);
        }
    } else {
        gvTimeAgentReceivedCounter = 0;
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
                ENGINE_makeShoot(0xFF, gvIsAgent); /*use default shot strength, no shot custom info*/
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
 * part in external interrupt for user button press
 */
void PLUGIN_pressedUserButton(void) {
    ENGINE_toggleLightState();
}

/*
 * part in while loop in main after detecting hit from slave module
 */
void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
                       uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
    uint8_t lGameState = ENGINE_getGameState();

    if (lGameState == game_state_alive) {
        if (gvIsAgent == aHitCustomInfo) {
            uint8_t lHealthTemp = ENGINE_getHealth();
            ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);
            ENGINE_setHealth(lHealthTemp);
        } else {
            ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);

            /*process kill*/
            if (ENGINE_getHealth() == 0) {
                ENGINE_processDeath(aHitCode, aHitFlag);
                gvDisplayIndex |= DI_KILLED;
                gvOtherCode = aHitCode;
                if (gvIsAgent == 1) {
                    if (gvAgentBuffered == 0) {
                        gvIsAgent = 0;
                        gvDisplayIndex |= DI_ICON;
                    } else {
                        gvAgentBuffered--;
                    }
                    ENGINE_setPeriodicInfoByte(gvAgentBuffered + gvIsAgent, 0);
                    ENGINE_sendCustomMessage((uint8_t *)"A", 1, aHitCode);
                } else {
                    ENGINE_sendCustomMessage((uint8_t *)"H", 1, aHitCode);
                }
            }
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
    uint8_t lLedColor;
    uint8_t lLedDisplay;
    colors_t lDisplayColor = gcColorWhite;

    if (gvIsAgent == 1) {
        lLedColor = led_special;
        lLedDisplay = led_basic;
    } else {
        lLedColor = led_basic;
        lLedDisplay = led_special;
    }

    if (aState == state_game) {
        if (aGameState == game_state_starting) {
            uint16_t lTimeTemp = ENGINE_getDisplayTime();
            if (lTimeTemp > 3)
                lLedColor = led_basic;
            if (gvTimeBlinkingLed == 1)
                lMessageTemp = LED1(lLedColor) | LED2(lLedColor);
        } else if (aGameState == game_state_alive) {
            lMessageTemp = LED1(lLedColor) | LED2(lLedColor);
        } else if (aGameState == game_state_revival) {
            if (gvTimeBlinkingLed == 1)
                lMessageTemp = LED1(led_off) | LED2(lLedColor);
            else
                lMessageTemp = LED1(lLedColor) | LED2(lLedColor);
        }
    } else {
    }

    for (i = 0; i < MODULES_NUMBER; i++)
        apModulesState[i] = lMessageTemp;

    if (aHitFlag != 0 && gvAlreadyDead == 0) { /* && (game_state == game_state_dead))*/
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
            lDisplayColor = gcColorWhite;
            break;
        case DL_KILLED:
            lDisplayColor = gcColorRed;
            break;
        case DL_HIT:
            lDisplayColor = gcColorGreen;
            break;
        case DL_AGENT:
            lDisplayColor = gcColorYellow;
            break;
        default:
            break;
        }

        if (gvIsAgent == 1) {
            apModulesColor1[MODULE_MAIN_BOARD] = lDisplayColor;
            apModulesColor2[MODULE_MAIN_BOARD] = agentColor;            
        } else {
            apModulesColor1[MODULE_MAIN_BOARD] = normalColor;
            apModulesColor2[MODULE_MAIN_BOARD] = lDisplayColor;
        }
    }

    if ((aState == state_game) || (aState == state_ending)) {
        apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_stroboscope));
        uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
        if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1)) || (lOptionTouchEnabled == 0)) {
            apModulesState[MODULE_MAIN_BOARD] |= LED2(lLedDisplay);
        } else {
            apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(lLedDisplay));
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
    if (gvIsAgent == 1) {
        ENGINE_playSoundFromSoundSet(becomeAgent);
    }
    gvDisplayIndex |= DI_SWITCH_BASIC;
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
    if (apData[0] == 'A') {
        if (gvTimeAgentReceived == 1 && checkCodeLastArray(gvBackupCodeLast, aDevice) == 1) {
            // ENGINE_setHealth((gvAgentBuffered + gvIsAgent) * 10);
            // ENGINE_setAmmo(aDevice);
            // ENGINE_setLife(gvBackupCodeLast[0]*100);
            return;
        } // else if(gvTimeAgentReceived == 1){
          // ENGINE_setHealth((gvAgentBuffered + gvIsAgent) * 10);
          // ENGINE_setAmmo(aDevice);
          // ENGINE_setLife(gvBackupCodeLast[0]*100);
        //}
        if (gvIsAgent == 0) {
            ENGINE_playSoundFromSoundSet(becomeAgent);
            gvIsAgent = 1;
            gvDisplayIndex |= DI_AGENT;
            gvDisplayIndex |= DI_ICON;
        } else {
            gvAgentBuffered++;
            ENGINE_playSoundFromSoundSet(doubleAgent);
            gvDisplayIndex |= DI_AGENT;
            gvDisplayIndex |= DI_ICON;
        }
        // enable timer for checking if the same message is received from chest
        if (gvTimeAgentReceived == 0) {
            gvTimeAgentReceived = 1;
        } else {
            gvTimeAgentReceivedCounter = 0;
        }
        addCodeLastArray(gvChestCodeLast, aDevice);
        ENGINE_setPeriodicInfoByte(gvAgentBuffered + gvIsAgent, 0);
    } else if (apData[0] == 'B') {
        // if the code in backup message is the same as in array from chests, ignore it
        if (gvTimeAgentReceived == 1 && checkCodeLastArray(gvChestCodeLast, apData[2]) == 1) {
            // ENGINE_setAmmo(apData[2]);
            // ENGINE_setLife(gvChestCodeLast[0]*100);
            return;
        }
        // if agent backup message contains the same agent number as actual, ignore it
        if ((gvIsAgent + gvAgentBuffered) >= apData[1]) {
            return;
        }
        if (apData[1] == 1) {
            ENGINE_playSoundFromSoundSet(becomeAgent);
            gvIsAgent = 1;
            gvDisplayIndex |= DI_AGENT;
            gvDisplayIndex |= DI_ICON;
        } else {
            gvAgentBuffered = apData[1] - 1;
            gvIsAgent = 1;
            ENGINE_playSoundFromSoundSet(doubleAgent);
            gvDisplayIndex |= DI_AGENT;
            gvDisplayIndex |= DI_ICON;
        }
        // enable timer for checking if the same message is received from chest
        if (gvTimeAgentReceived == 0) {
            gvTimeAgentReceived = 1;
        } else {
            gvTimeAgentReceivedCounter = 0;
        }
        addCodeLastArray(gvBackupCodeLast, apData[2]);
        // gvBackupCodeLast = apData[2];
        ENGINE_setPeriodicInfoByte(gvAgentBuffered + gvIsAgent, 0);
    }
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

    gvLengthDeath = 500;   /*in 0,01 ms -> 5s*/
    gvLengthRevival = 100; /*in 0,01 ms -> 1s*/

    /*set basic color to dark red, special color to white (stroboscope)*/
    ENGINE_setAllModulesColor(1, normalColor);
    ENGINE_setAllModulesColor(2, agentColor);
    ENGINE_setAllModulesDim(100, 100);

    /*add to B message info about Agent state*/
    ENGINE_setPeriodicInfoLength(1);

    ENGINE_controlDisplayFromPlugin();

    ENGINE_loadShot(0, sfxShoot);
    ENGINE_loadShot(1, sfxEmptyShoot);
    ENGINE_playSoundFromSoundSet(loaded);
}
