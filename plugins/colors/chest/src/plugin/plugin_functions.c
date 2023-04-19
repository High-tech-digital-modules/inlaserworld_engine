
#define COLORS_MAX_NMBR		16

volatile uint8_t gvTimeBlinking = 0;
volatile uint16_t gvTimeBlinkingCounter = 0;
volatile uint8_t gvTimeBlinkingLed = 0;

volatile uint8_t gvTimeDeath = 0;
volatile uint16_t gvTimeDeathCounter = 0;

volatile uint8_t gvTimeRevival = 0;
volatile uint16_t gvTimeRevivalCounter = 0;

volatile uint16_t gvLengthBlinking = 20;		//in 0,01*seconds
volatile uint16_t gvLengthDeath = 0;		//in 0,01*seconds
volatile uint16_t gvLengthRevival = 0;		//in 0,01*seconds

colors_t gvColorsTable[COLORS_MAX_NMBR];
volatile uint8_t gvGameStarted = 0;
volatile uint8_t gvColorIndex = 255;

/*
 * part in while loop in main
 */
void PLUGIN_mainLoop(void) {

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
				//TODO some signalization of 0 life?
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
}

/*
 * part in external interrupt for trigger press
 */
void PLUGIN_pressedTrigger(void) {
	uint8_t lGameState = ENGINE_getGameState();

	if ((lGameState == game_state_alive)
			|| (lGameState == game_state_revival)) {
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			if (ENGINE_getAmmo() > 0) {
				ENGINE_makeShoot(0xFF, gvColorIndex); /*use default shot strength, custom info with actual color from table*/
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

	if (lGameState == game_state_alive){
		ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);

		/*process kill*/
		if (ENGINE_getHealth() == 0) {
			ENGINE_processDeath(aHitCode, aHitFlag);
			if (aHitCustomInfo != gvColorIndex) {
				gvColorIndex = aHitCustomInfo;
				ENGINE_setAllModulesColor(1, gvColorsTable[gvColorIndex]);
				ENGINE_setPeriodicInfoByte(gvColorIndex, 0);
			}
		}
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
		uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t* apModulesState,
		volatile uint8_t* apModulesDim1, volatile uint8_t* apModulesDim2,
		volatile colors_t* apModulesColor1, volatile colors_t* apModulesColor2) {
	uint8_t lMessageTemp = 0;
	uint8_t i = 0;

	if (aState == state_game) {
		if ((aGameState == game_state_starting) && (gvTimeBlinkingLed == 1)) {
			uint16_t lTimeTemp = ENGINE_getDisplayTime();
			if (lTimeTemp > 5)
				lMessageTemp = LED1(led_special) | LED2(led_special);
			else
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
		ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
	}

	if (aHitFlag != 0) { /* && (game_state == game_state_dead))*/
		/*change dim value, send for all chest slaves, not for weapon*/
		if (aGameState == game_state_dead) {
			/*reset dim to 100_*/
			ENGINE_setAllModulesDim(100, 100);
		} else {
			ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
			/*PLUGIN_setDimAccordingHealth(aHealth);*/
		}
		apModulesState[aHitFlag - 1] |= LED1(
				led_stroboscope) | LED2(led_stroboscope);
		ENGINE_setVibrationAccordingHitFlag(aHitFlag);
	}

	/*backlight of display*/
	if ((aState == state_game) || (aState == state_ending)) {
		apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_stroboscope));
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			if (aGameState == game_state_starting) {
				uint16_t lTimeTemp = ENGINE_getDisplayTime();
				if (lTimeTemp > 5)
					apModulesState[MODULE_MAIN_BOARD] |= LED2(led_special);
				else
					apModulesState[MODULE_MAIN_BOARD] |= LED2(led_basic);
			} else {
				apModulesState[MODULE_MAIN_BOARD] |= LED2(led_basic);
			}
		} else {

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
}

/*
 * part in while loop in main triggered by game_state change
 */
void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
	gvTimeBlinking = 1;
	gvGameStarted = 1;
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
void PLUGIN_processCustomMessage(uint8_t* apData, uint16_t aLength,
		uint8_t aDevice) {

	/*receive selected color by its index*/
	if ((apData[0] == 'I') && (aDevice == 0x00)) {
		gvColorIndex = apData[1];
		ENGINE_setAllModulesColor(1, gvColorsTable[gvColorIndex]);
		ENGINE_setPeriodicInfoByte(gvColorIndex, 0);
	}
}

/*
 * part of PLUGIN_init, for users part of initialization, for example global vars for timers (length_death,...)
 */
void PLUGIN_customInit(volatile colors_t* apModulesColor1,
		volatile colors_t* apModulesColor2, volatile uint8_t* apModulesDim1,
		volatile uint8_t* apModulesDim2, uint8_t* apModulesVibrationStrength,
		volatile uint8_t* apModulesState) {
	ENGINE_loadShot(0, sfxShoot);
  ENGINE_loadShot(1, sfxEmptyShoot);
	colors_t lColorWhite = { 100, 100, 100 };
	colors_t lColorBlack = { 0, 0, 0 };

	gvLengthDeath = ENGINE_getLengthDeath();
	gvLengthRevival = ENGINE_getLengthRevival();

	ENGINE_setAllModulesColor(1, lColorBlack);
	ENGINE_setAllModulesColor(2, lColorWhite);
	ENGINE_setAllModulesDim(100, 100);
	ENGINE_setAllModulesState(led_special, led_special, 0);

	ENGINE_setPeriodicInfoLength(1);
	ENGINE_setPeriodicInfoByte(gvColorIndex, 0);
	
	gvColorsTable[0] = color1;
	gvColorsTable[1] = color2;
	gvColorsTable[2] = color3;
	gvColorsTable[3] = color4;
	gvColorsTable[4] = color5;
	gvColorsTable[5] = color6;
}
