
#include <cmath>

uint8_t gOrbs = 15;

void setOrbColor(std::string aAddress, ColorT aColor) {
  ENGINE_lightClearOperationBuffer(aAddress);
  ENGINE_lightClearSequenceBuffer(aAddress, 0b01010101);
  ENGINE_lightAddOperation(aAddress, { 0, aColor.red, aColor.green, aColor.blue, 30, 0 });
  ENGINE_lightAddSequence(aAddress, { 0, 1 }, 0b01010101);
  ENGINE_lightSyncOperationBuffer(aAddress);
  ENGINE_lightSyncSequenceBuffer(aAddress, 0b01010101);
  ENGINE_lightStartSequence(aAddress, 0x7770 );
  ENGINE_lightStartSequence(aAddress, 0x4440 );
}

void PLUGIN_setup() {
    setOrbColor(bonusMachineGun, colorMachineGun);
    setOrbColor(bonusArmor, colorArmor);
    setOrbColor(bonusSniper, colorSniper);
    setOrbColor(bonusHealing, colorHealing);
}

void PLUGIN_gameStateChanged(uint8_t state) {
    
}

void PLUGIN_newLeader(const Player* apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    } 
    
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch(time) {
        case 5: ENGINE_playSoundFromSoundSet(five); break;
        case 4: ENGINE_playSoundFromSoundSet(four); break;
        case 3: ENGINE_playSoundFromSoundSet(three); break;
        case 2: ENGINE_playSoundFromSoundSet(two); break;
        case 1: ENGINE_playSoundFromSoundSet(one); break;
    }
	
	if (state != 0x03 && time == 300) {
    	ENGINE_playSoundFromSoundSet(Min5Remaining);
	}
    if (state != 0x03 && time == 60) {
    	ENGINE_playSoundFromSoundSet(Min1Remaining);
    }
    
    for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        
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
}

void PLUGIN_receivedCustomData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
  if(apData[0] == 0) {
    if (apData[1] >> 0 & 1) {
      gOrbs |= 1 << 0;
      setOrbColor(bonusMachineGun, colorMachineGun);
    } 
    if (apData[1] >> 1 & 1) {
      gOrbs |= 1 << 1;
      setOrbColor(bonusArmor, colorArmor);
    } 
    if (apData[1] >> 2 & 1) {
      gOrbs |= 1 << 2;
      setOrbColor(bonusSniper, colorSniper);
    } 
    if (apData[1] >> 3 & 1) {
      gOrbs |= 1 << 3;
      setOrbColor(bonusHealing, colorHealing);
    }
  }
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
  
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
  Player *p = ENGINE_getPlayerByCode(aCode);
  setOrbColor(aAddress, {0, 0, 0});
  uint8_t orbIndex = 255;
  if (aAddress.compare(bonusMachineGun) == 0) {
    orbIndex = 0;
  } else if (aAddress.compare(bonusArmor) == 0) {
    orbIndex = 1;
  } else if (aAddress.compare(bonusSniper) == 0) {
    orbIndex = 2;
  } else if (aAddress.compare(bonusHealing) == 0) {
    orbIndex = 3;
  } 
  uint8_t lData[2] = { 0, orbIndex };
  if (gOrbs >> orbIndex & 1) {
    ENGINE_sendCustomMessage((uint8_t*)lData, 2, p->index);
    switch(orbIndex) {
      case 0:
        ENGINE_playSoundFromSoundSet(machineGunTaken);
        break;
      case 1:
        ENGINE_playSoundFromSoundSet(armorTaken);
        break;
      case 2:
        ENGINE_playSoundFromSoundSet(sniperTaken);
        break;
      case 3:
        ENGINE_playSoundFromSoundSet(healingTaken);
        break;
    }
  }
  gOrbs &= ~(1UL << orbIndex);
}
