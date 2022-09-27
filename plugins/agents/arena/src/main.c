
#include <cmath>

typedef struct {
  int agentPoints;
  uint32_t killsAsAgent;
  uint32_t becomeAgent;
  bool isAgent;
  bool requestToBeAgent;
} PlayerData;

PlayerData gPlayerData[100];

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
}

void PLUGIN_setup() {

}

void PLUGIN_gameStateChanged(uint8_t state) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState == 0xFF) {
        
    }
    if (state != 0x03 && lPrevState == 0x03 && state != 0) {
        ENGINE_playSound("startingGame.wav");
    } else if (state == 0) {
        
    }
}

void PLUGIN_newLeader(const Player* apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    } 
    
}

void setupAgents() {
  uint8_t lLen = ENGINE_getPlayersLength();
  uint8_t i = 4;
  uint8_t step = 1;
  uint8_t limit = 4;
  while (i <= lLen) {
    if (i == limit) {
      step++;
      limit += step;
      uint8_t lNum = (rand() % lLen);
      while(1) {
        if (!gPlayerData[lNum].requestToBeAgent) {
          gPlayerData[lNum].requestToBeAgent = true;
          break;
        }
        lNum = (rand() % lLen);
      }
    }
    i++;
  }
}

void PLUGIN_gameLoaded() {
  uint8_t lLen = ENGINE_getPlayersLength();
  for(uint8_t i = 0; i < lLen; i++) {
    gPlayerData[i].agentPoints = 0;
    gPlayerData[i].killsAsAgent = 0;
    gPlayerData[i].becomeAgent = 0;
    gPlayerData[i].isAgent = false;
    gPlayerData[i].requestToBeAgent = false;
  }
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch(time) {
        case 5: ENGINE_playSoundFromSoundSet(five); break;
        case 4: ENGINE_playSoundFromSoundSet(four); break;
        case 3: 
            ENGINE_playSoundFromSoundSet(three); 
            setupAgents();
          break;
        case 2: ENGINE_playSoundFromSoundSet(two); break;
        case 1: ENGINE_playSoundFromSoundSet(one); break;
    }
  	if (state != 0x03 && time == 300) {
      	ENGINE_playSoundFromSoundSet(Min5Remaining);
  	}
    if (state != 0x03 && time == 60) {
    	ENGINE_playSoundFromSoundSet(Min1Remaining);
    }
    
    if (state != 0x03) {
      for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        
        Player *p = ENGINE_getPlayerByIndex(i);
        if (gPlayerData[i].isAgent) {
          gPlayerData[i].agentPoints += pointsAgent;
        }
        ENGINE_setPlayerPropBool(i, "isAgent", gPlayerData[i].isAgent);
        ENGINE_setPlayerPropNumber(i, "agentPoints", gPlayerData[i].agentPoints);
        ENGINE_setPlayerPropNumber(i, "killsAsAgent", gPlayerData[i].killsAsAgent);
        ENGINE_setPlayerPropNumber(i, "becomeAgent", gPlayerData[i].becomeAgent);
        p->score = gPlayerData[i].agentPoints + 
          gPlayerData[i].killsAsAgent * pointsAgentKill +
          gPlayerData[i].becomeAgent * pointsBecomeAgent;
      }  
    }
    
}

void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    if (gPlayerData[aWhoPlayerIndex].isAgent) {
      gPlayerData[aWhoPlayerIndex].killsAsAgent++;
    } else {
      gPlayerData[aWhoPlayerIndex].requestToBeAgent = true;
      gPlayerData[aWhoPlayerIndex].becomeAgent++;
    }
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    
}

void PLUGIN_deviceIsReady(uint8_t aPlayerIndex) {
  
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
  if (aLen > 0) {
    if (!gPlayerData[aPlayerIndex].isAgent && apData[0] == 1) {
      gPlayerData[aPlayerIndex].requestToBeAgent = false;
    }
    if(gPlayerData[aPlayerIndex].requestToBeAgent) {
      ENGINE_sendCustomMessage((uint8_t*)("A"), 1, aPlayerIndex);
    }
    gPlayerData[aPlayerIndex].isAgent = apData[0] == 1;
  }
}
