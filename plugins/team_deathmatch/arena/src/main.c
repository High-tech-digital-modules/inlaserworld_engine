

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
	  DEATHMATCH_playerAmmoChanged(aPlayerIndex, aOldValue, aNewValue, aMissedAmmoInRow);
}

void PLUGIN_newLeader(const Player* apPLayer) {
    DEATHMATCH_newLeader(apPLayer);
}

void PLUGIN_main() {
  DEATHMATCH_main();
}

