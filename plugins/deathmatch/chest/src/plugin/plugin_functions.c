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

void PLUGIN_mainLoop(void) {

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

void PLUGIN_pressedTrigger(void) {
	uint8_t lGameState = ENGINE_getGameState();

	if ((lGameState == game_state_alive)
			|| (lGameState == game_state_revival)) {
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			if (ENGINE_getAmmo() > 0) {
				ENGINE_makeShoot(0xFF, 0x05); /*use default shot strength, no shot custom info*/
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

void PLUGIN_pressedUserButton(void) {
	ENGINE_toggleLightState();
}

void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
		uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {

	ENGINE_processHit(aHitCode, aHitFlag, aHitStrength);

	/*process kill*/
	if (ENGINE_getHealth() == 0) {
		ENGINE_processDeath(aHitCode, aHitFlag);
		if(aHitCustomInfo == 0x05) {
		  ENGINE_sendCustomMessage("HELLO", 5, aHitCode);
		}
	}
}

void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
		uint8_t aHitCode, uint8_t aHealth, volatile uint8_t* apModulesState,
		volatile uint8_t* apModulesDim1, volatile uint8_t* apModulesDim2,
		volatile colors_t* apModulesColor1, volatile colors_t* apModulesColor2) {
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
		ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
	}

	if (aHitCode != 0) { /* && (game_state == game_state_dead))*/
		/*change dim value, send for all chest slaves, not for weapon*/
		if (aGameState == game_state_dead) {
			/*reset dim to 100_*/
			ENGINE_setAllModulesDim(100, 100);
		} else {
			ENGINE_setColorEffectFade(0xFF); /*set according to the Health*/
			/*PLUGIN_setDimAccordingHealth(aHealth);*/
		}
		apModulesState[aHitCode - 1] |= LED1(
				led_stroboscope) | LED2(led_stroboscope);
		ENGINE_setVibrationAccordingHitCode(aHitCode);
	}

	/*backlight of display*/
	if ((aState == state_game) || (aState == state_ending)) {
		apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_special));
		uint8_t lOptionTouchEnabled = ENGINE_getOptionsTouchEnabled();
		if (((lOptionTouchEnabled != 0) && (ENGINE_getTouchPressed() == 1))
				|| (lOptionTouchEnabled == 0)) {
			apModulesState[MODULE_MAIN_BOARD] |= LED2(led_basic);
		} else {
			apModulesState[MODULE_MAIN_BOARD] &= ~(LED2(led_basic));
		}
	}
}

void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast) {
	gvTimeBlinking = 0;
	if (aGameStateLast == game_state_starting) {
		ENGINE_playSound(11);
	}
}

void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast) {
	gvTimeDeath = 1;
}

void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast) {
	gvTimeBlinking = 1;
	gvTimeRevival = 1;
	ENGINE_playSound(10);
	ENGINE_setHealth(100);
}

void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
	gvTimeBlinking = 1;
}

void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast) {
	ENGINE_setAllModulesDim(100, 100);
	ENGINE_setAllModulesState(1, 2, 0);
}

void PLUGIN_processCustomMessage(uint8_t* apData, uint16_t aLength,
		uint8_t aDevice) {
	ENGINE_setLightState(1);
}

void PLUGIN_customInit(volatile colors_t* apModulesColor1,
		volatile colors_t* apModulesColor2, volatile uint8_t* apModulesDim1,
		volatile uint8_t* apModulesDim2, uint8_t* apModulesVibrationStrength,
		volatile uint8_t* apModulesState) {
	gvLengthDeath = ENGINE_getLengthDeath();
	gvLengthRevival = ENGINE_getLengthRevival();
}
