
void PLUGIN_timer10ms(void) {
	DEATHMATCH_timer10ms();
}

void PLUGIN_pressedUserButton(void) {
	DEATHMATCH_pressedUserButton();
}

void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
		uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth) {
  DEATHMATCH_hitByEnemy(aHitCode, aHitFlag, aHitStrength, aHitCustomInfo, aLife, aHealth);
}

void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
		uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t* apModulesState,
		volatile uint8_t* apModulesDim1, volatile uint8_t* apModulesDim2,
		volatile colors_t* apModulesColor1, volatile colors_t* apModulesColor2) {
  DEATHMATCH_setModulesState(aState, aGameState, aHitFlag, aHealth, apModulesState, 
    apModulesDim1, apModulesDim2, apModulesColor1, apModulesColor2);
}

void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast) {
  DEATHMATCH_changedGameStateToAlive(aGameStateLast);
}

void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast) {
  DEATHMATCH_changedGameStateToDead(aGameStateLast);
}

void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast) {
  DEATHMATCH_changedGameStateToRevival(aGameStateLast);
}

void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast) {
  DEATHMATCH_changedGameStateToStarting(aGameStateLast);
}

void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast) {
  DEATHMATCH_changedGameStateToEnding(aGameStateLast);
}

void PLUGIN_processCustomMessage(uint8_t* apData, uint16_t aLength,
		uint8_t aDevice) {
	DEATHMATCH_processCustomMessage(apData, aLength, aDevice);
}

void PLUGIN_customInit(volatile colors_t* apModulesColor1,
		volatile colors_t* apModulesColor2, volatile uint8_t* apModulesDim1,
		volatile uint8_t* apModulesDim2, uint8_t* apModulesVibrationStrength,
		volatile uint8_t* apModulesState) {
		  DEATHMATCH_customInit(apModulesColor1, apModulesColor2, apModulesDim1,
		    apModulesDim2, apModulesVibrationStrength, apModulesState);
}