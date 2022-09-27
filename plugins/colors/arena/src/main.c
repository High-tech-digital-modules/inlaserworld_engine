
#include <cmath>

uint8_t playerIndexes[100];

ColorT gColorArray[6];
int gPlayersScore[100];
uint32_t gPlayersFriendlyHits[100];

void PLUGIN_setup() {
    gColorArray[0] = color1;
    gColorArray[1] = color2;
    gColorArray[2] = color3;
    gColorArray[3] = color4;
    gColorArray[4] = color5;
    gColorArray[5] = color6;
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
        p->score = gPlayersScore[i];
    }
}

void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    //printf("From plugin got hit %d, %d \n", aPlayerIndex, aWhoPlayerIndex);
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    //printf("From plugin killed %d, %d \n", aPlayerIndex, aWhoPlayerIndex);
    
    uint8_t lColorPlayer = playerIndexes[aPlayerIndex];
    uint8_t lColorWhoPlayer = playerIndexes[aWhoPlayerIndex];
    if (lColorWhoPlayer != lColorPlayer) {
      uint8_t lCount = 0;
      for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        if(playerIndexes[i] == lColorPlayer) {
          lCount++;
        }
      }
      if(lCount > 1) {
        gPlayersScore[aWhoPlayerIndex] += lCount * pointsKill;  
      } else if (lCount == 1) {
        // Or maybe some bonus here
        gPlayersScore[aWhoPlayerIndex] += pointElimination;
      }
      
    } else {
      gPlayersFriendlyHits[aWhoPlayerIndex]++;
      gPlayersScore[aWhoPlayerIndex] += pointsFriendlyFire;
    }
    printf("aPlayerIndex: %d, aWhoPlayerIndex: %d\n", playerIndexes[aPlayerIndex], playerIndexes[aWhoPlayerIndex]);
}

void PLUGIN_deviceIsReady(uint8_t aPlayerIndex) {
  uint8_t data[2];
  data[0] = 'I';
  data[1] = aPlayerIndex / playerCount;
  ENGINE_sendCustomMessage(data, 2, aPlayerIndex);
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
  playerIndexes[aPlayerIndex] = apData[0];
  uint8_t lIndex = playerIndexes[0];
  bool allSame = true;
  for(uint8_t i = 1; i < ENGINE_getPlayersLength(); i++) {
    if(lIndex != playerIndexes[i]) {
      allSame = false;
      break;
    }
  }
  
  if(allSame) {
    for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
      uint8_t data[2];
      data[0] = 'I';
      data[1] = i / playerCount;
      ENGINE_sendCustomMessage(data, 2, i);
    }
  }
}
