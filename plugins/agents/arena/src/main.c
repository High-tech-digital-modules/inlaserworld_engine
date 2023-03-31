#include <unistd.h>
#ifdef VSCODE
#include "engine_functions.h"
#include "custom_variables_map.h"
#include "sound_set_map.h"
#endif
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

//#define LOG_ENABLED

typedef struct {
  int agentPoints;
  uint32_t killsAsAgent;
  uint32_t becomeAgent;
  uint8_t isAgent;
  uint8_t isAgentBackup;
  bool requestToBeAgent;
} PlayerData;

PlayerData gPlayerData[100];
volatile uint8_t gvAgentsNumber = 0;
volatile uint8_t gvBadAgentNumberCounter = 0;
volatile int gTimerLightPulse = 0;
const ColorT gColorBlack = {0x00, 0x00, 0x00};
const char pgLightBroadcastAddress[] = "000000000000000000";
FILE * fp;

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
}

void handlerLightPulse(void){
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x3330);
}

void PLUGIN_setup() {
  LIGHT_switchOffAllModules();
  LIGHT_setArenaLightsColor(gColorBlack, 1);
  usleep(40000);
  ENGINE_lightClearOperationBuffer(pgLightBroadcastAddress);
  ENGINE_lightClearSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 1, 0xFF, 0x00, 0x00, 40, 0 }); //pulsing, red full, only increase
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 1, 0x55, 0x00, 0x00, 40, 0 }); //pulsing, red low, only increase
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 0, 0x55, 0x00, 0x00, 10, 0 }); //lighting, red low, only increase
  ENGINE_lightAddOperation(pgLightBroadcastAddress, { 0, 0x00, 0x00, 0x00, 10, 0 }); //switched off
  ENGINE_lightAddSequence(pgLightBroadcastAddress, { 0, 1 }, 0b00010101); //{index, repeat}
  ENGINE_lightAddSequence(pgLightBroadcastAddress, { 1, 1 }, 0b00010101); //{index, repeat}
  ENGINE_lightAddSequence(pgLightBroadcastAddress, { 2, 1 }, 0b00010101); //{index, repeat}
  usleep(40000);        
  ENGINE_lightSyncOperationBuffer(pgLightBroadcastAddress);    
  usleep(40000);
  ENGINE_lightSyncSequenceBuffer(pgLightBroadcastAddress, 0b00111111);
  usleep(40000);
  ENGINE_lightStartSequence(pgLightBroadcastAddress, 0x7770);  

  std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();

  //go thru all devices in lBonusModules
  for(DeviceT lModule : lBonusModules)
  {
    usleep(40000);    
    ENGINE_lightClearSequenceBuffer(lModule.address, 0b00111111);    
    ENGINE_lightAddSequence(lModule.address, { 0, 1 }, 0b00000001); //{index, repeat}
    ENGINE_lightAddSequence(lModule.address, { 1, 1 }, 0b00000001); //{index, repeat}
    ENGINE_lightAddSequence(lModule.address, { 2, 1 }, 0b00000001); //{index, repeat}
    ENGINE_lightAddSequence(lModule.address, { 3, 1 }, 0b00010100); //{index, repeat}       
    usleep(40000);
    ENGINE_lightSyncSequenceBuffer(lModule.address, 0b00111111);
    usleep(40000);
    ENGINE_lightStartSequence(lModule.address, 0x7770);
  }

  gTimerLightPulse = ENGINE_setTimer(handlerLightPulse, 1500);

   
#ifdef LOG_ENABLED
  fp = fopen ("/var/www/lasergame/agent_log.txt", "a+");
  if(fp != NULL){
    time_t curr_time;
	  curr_time = time(NULL);
	  char *tm = ctime(&curr_time);
    fprintf(fp, "New agent game %s\n", tm);
  } 
#endif
  
}

void PLUGIN_destroyed(){
  LIGHT_setColorStandby();
#ifdef LOG_ENABLED
  if(fp != NULL){
    fclose(fp);
  }
#endif
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
        if (gPlayerData[lNum].isAgent == 0) {
          gPlayerData[lNum].isAgent = 1;
          ENGINE_sendCustomMessage((uint8_t*)("A"), 1, lNum);
          break;
        }
        lNum = (rand() % lLen);
      }
      gvAgentsNumber++;
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
    gPlayerData[i].isAgent = 0;
    gPlayerData[i].requestToBeAgent = false;
  }
}

void PLUGIN_main() {
    int32_t lTime = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch(lTime) {
        case 5: ENGINE_playSoundFromSoundSet(five); break;
        case 4: ENGINE_playSoundFromSoundSet(four); break;
        case 3: 
            ENGINE_playSoundFromSoundSet(three);
            if(state == 0x03){
              setupAgents();
            }            
          break;
        case 2: ENGINE_playSoundFromSoundSet(two); break;
        case 1: ENGINE_playSoundFromSoundSet(one); break;
    }
  	if (state != 0x03 && lTime == 300) {
      	ENGINE_playSoundFromSoundSet(Min5Remaining);
  	}
    if (state != 0x03 && lTime == 60) {
    	ENGINE_playSoundFromSoundSet(Min1Remaining);
    }
    
    if (state != 0x03) {
      for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        
        Player *p = ENGINE_getPlayerByIndex(i);
        if (gPlayerData[i].isAgent > 0) {
          gPlayerData[i].agentPoints += pointsAgent;
        }
        ENGINE_setPlayerPropNumber(i, "isAgent", gPlayerData[i].isAgent);
        ENGINE_setPlayerPropNumber(i, "agentPoints", gPlayerData[i].agentPoints);
        ENGINE_setPlayerPropNumber(i, "killsAsAgent", gPlayerData[i].killsAsAgent);
        ENGINE_setPlayerPropNumber(i, "becomeAgent", gPlayerData[i].becomeAgent);
        p->score = gPlayerData[i].agentPoints + 
          gPlayerData[i].killsAsAgent * pointsAgentKill +
          gPlayerData[i].becomeAgent * pointsBecomeAgent;
      }

      //check number of agents in game
      uint8_t lActualAgentsNumber = 0;
      for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        lActualAgentsNumber +=gPlayerData[i].isAgent;
      }
      if(lActualAgentsNumber < gvAgentsNumber){
        gvBadAgentNumberCounter++;
        //f("bad number %d\n", gvBadAgentNumberCounter);
      } else {
        gvBadAgentNumberCounter = 0;
      }  
      if(gvBadAgentNumberCounter == 5){
        gvBadAgentNumberCounter = 0;
        uint8_t lLen = ENGINE_getPlayersLength();
        uint8_t lNum =  (rand() % lLen);
        while(1){
          if (gPlayerData[lNum].isAgent == 0) {
            gPlayerData[lNum].isAgent = 1;
            uint8_t lMessage[3] = {'B', 1, 0}; //identifier B as backup agent, 1 as number of agents, 0 as ID of coodinator
            //ENGINE_sendCustomMessage(lMessage, 3, lNum);
#ifdef LOG_ENABLED
            if(fp != NULL){
              fprintf(fp, "new agent for %d\n", lNum);
            }
#endif
            //printf("new agent for %d\n", lNum);
            break;
          }
          lNum = (rand() % lLen);
        }
      }

#ifdef LOG_ENABLED
      if(fp != NULL){
        time_t curr_time;
	      curr_time = time(NULL);
	      char *tm = ctime(&curr_time);
        fprintf(fp, "%s", tm);
        uint8_t lPlayerLength = ENGINE_getPlayersLength();
        for(int i = 0; i < lPlayerLength; i++){
          fprintf(fp, " %d", gPlayerData[i].isAgent);  
        }
        fprintf(fp, "\n");  
        for(int i = 0; i < lPlayerLength; i++){
          fprintf(fp, " %d", gPlayerData[i].isAgentBackup);  
        }
        fprintf(fp, "\n");  
      }
#endif        
    }  
}

void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
#ifdef LOG_ENABLED  
    if(fp != NULL){
      fprintf(fp, "%d -> %d\n", aWhoPlayerIndex, aPlayerIndex);
    }
#endif    
    if (gPlayerData[aWhoPlayerIndex].isAgent > 0) {
      gPlayerData[aWhoPlayerIndex].killsAsAgent++;
      //printf("%d add agent kill\n",aWhoPlayerIndex);
#ifdef LOG_ENABLED      
      if(fp != NULL){
        fprintf(fp, "added agent kill\n");
      }
#endif            
    } else {
      gPlayerData[aWhoPlayerIndex].becomeAgent++;
      //printf("%d become agent\n",aWhoPlayerIndex);
#ifdef LOG_ENABLED      
      if(fp != NULL){
        fprintf(fp, "become agent\n");
      }
#endif      
    }

    if(gPlayerData[aPlayerIndex].isAgent > 0){
      gPlayerData[aPlayerIndex].isAgent--;
      gPlayerData[aWhoPlayerIndex].isAgent++;
      //printf("player %d agents %d\n", aPlayerIndex, gPlayerData[aPlayerIndex].isAgent);
      //printf("player %d agents %d\n", aWhoPlayerIndex, gPlayerData[aWhoPlayerIndex].isAgent);

      Player *p = ENGINE_getPlayerByIndex(aPlayerIndex);
      uint8_t lMessage[3] = {'B', gPlayerData[aWhoPlayerIndex].isAgent, p->code}; //identifier B as backup agent, number of agents to be transmitted, ID of killed chest
      //ENGINE_sendCustomMessage(lMessage, 3, aWhoPlayerIndex);
#ifdef LOG_ENABLED      
      if(fp != NULL){
        fprintf(fp, "regular new agent for %d\n", aWhoPlayerIndex);
      }
#endif      
      //printf("send B for player (index) %d, agents %d, from (code) %d\n", aWhoPlayerIndex, gPlayerData[aWhoPlayerIndex].isAgent, p->code);
    }    
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_deviceIsReady(uint8_t aPlayerIndex) {
  
}

void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex) {
  if (aLen > 0) {
    /*if (gPlayerData[aPlayerIndex].isAgent == 0 && apData[0] == 1) {
      gPlayerData[aPlayerIndex].requestToBeAgent = false;
    }
    if(gPlayerData[aPlayerIndex].requestToBeAgent) {
      //ENGINE_sendCustomMessage((uint8_t*)("A"), 1, aPlayerIndex);
    }
    gPlayerData[aPlayerIndex].isAgent = apData[0];*/

    //if(apData[0] != gPlayerData[aPlayerIndex].isAgent){
      gPlayerData[aPlayerIndex].isAgentBackup = apData[0];
      //printf("backup mismatch player %d isAgent %d isAgetBackup %d\n", aPlayerIndex, gPlayerData[aPlayerIndex].isAgent, gPlayerData[aPlayerIndex].isAgentBackup);
    //}
  }
}
