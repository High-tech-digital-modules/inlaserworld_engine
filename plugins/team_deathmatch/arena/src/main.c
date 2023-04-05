#ifdef VSCODE
#include "engine_functions.h"
#include "custom_variables_map.h"
#include "sound_set_map.h"
#include "submodules.h"
#endif

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
	DEATHMATCH_playerAmmoChanged(aPlayerIndex, aOldValue, aNewValue, aMissedAmmoInRow);
}

void PLUGIN_newLeader(const Player* apPLayer) {
  DEATHMATCH_newLeader(apPLayer);
}

void PLUGIN_setup() {
  LIGHT_switchOffAllModules();
  LIGHT_setArenaLightsColor(colorArena, 1);
  DEATHMATCH_setup(colorArena);
}

void PLUGIN_destroyed(){
  LIGHT_setColorStandby();
}

void PLUGIN_main() {
  DEATHMATCH_main();
}

void PLUGIN_gameStateChanged(uint8_t aState) {
  printf("New state: %d\n", aState);
  DEATHMATCH_gameStateChanged(aState);
}

void PLUGIN_playerDiBonusdKill(uint8_t aPlayerIndex, uint8_t aBonus) {
  ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
  DEATHMATCH_lightGotHit(aAddress.c_str(), aCode, aInfo);
}