
#include <cmath>

int gPointsKill = 0;
int gPointsDeath = 0;
int gPointsTeamKill = 0;
int gPointsHit = 0;
int gPointsTeamHit = 0;
int gPointsPerShoot = 0;
int gPointsDeathByTeamMate = 0;
int gPointsDoubleKill = 0;
int gPointsMonsterKill = 0;
double gPointsShootPrecision = 0;
bool gIsPointsPrecisionRelative = false;
std::string gCanGlobal = "000000000000000000";

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
}

void PLUGIN_setup() {
    gPointsKill = ENGINE_getTcvInt("pointsKill", 0);
    gPointsDeath = ENGINE_getTcvInt("pointsDeath", 0);
    gPointsTeamKill = ENGINE_getTcvInt("pointsTeamKill", 0);
    gPointsHit = ENGINE_getTcvInt("pointsHit", 0);
    gPointsTeamHit = ENGINE_getTcvInt("pointsTeamHit", 0);
    gPointsPerShoot = ENGINE_getTcvInt("pointsPerShoot", 0);
    gPointsDeathByTeamMate = ENGINE_getTcvInt("pointsDeathByTeamMate", 0);
    gPointsDoubleKill = ENGINE_getTcvInt("pointsDoubleKill", 0);
    gPointsMonsterKill = ENGINE_getTcvInt("pointsMonsterKill", 0);
    gPointsShootPrecision = ENGINE_getTcvDouble("pointsShootPrecision", 0);
    gIsPointsPrecisionRelative = ENGINE_getTcvBoolean("pointsPrecisionRelative", false);
}

void PLUGIN_gameStateChanged(uint8_t state) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
}

void PLUGIN_newLeader(const Player* apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSound("arenaLeaderChange.wav");
    } 
    
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch(time) {
        case 5: ENGINE_playSound("five.wav"); break;
        case 4: ENGINE_playSound("four.wav"); break;
        case 3: ENGINE_playSound("three.wav"); break;
        case 2: ENGINE_playSound("two.wav"); break;
        case 1: ENGINE_playSound("one.wav"); break;
    }
	
	if (state != 0x03 && time == 300) {
    	ENGINE_playSound("5MinReamining.wav");
	}
    if (state != 0x03 && time == 60) {
    	ENGINE_playSound("1MinRemaining.wav");
    }
    
    for(uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {
        
        Player *p = ENGINE_getPlayerByIndex(i);
        int32_t score = 
            gPointsKill * p->kills +
            gPointsDeath * (p->deaths - p->teamDeaths) +
            gPointsTeamKill * p->teamKills +
            gPointsHit * (p->hits - p->kills) + 
            gPointsTeamHit * (p->teamHits - p->teamKills) +
            gPointsPerShoot * p->usedAmmo + 
            gPointsDeathByTeamMate * p->teamDeaths + 
            gPointsDoubleKill * p->bonusKillounter[2] +
            gPointsMonsterKill * p->bonusKillounter[3];
        if (gIsPointsPrecisionRelative) {
            score = score + abs(((int32_t)round(p->shootingAccuracy * gPointsShootPrecision * ((double)score))));
        } else {
            score += (int32_t)round(round(p->shootingAccuracy) * gPointsShootPrecision);
        }
        p->score = score;
    }
}

void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    
}

void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex) {
    
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
  if (aBonus % 3 == 2) {
    ENGINE_playSoundOnPlayersChest(aPlayerIndex, 8);  
  } else if (aBonus % 3 == 0) {
    ENGINE_playSoundOnPlayersChest(aPlayerIndex, 9);
  }
}

