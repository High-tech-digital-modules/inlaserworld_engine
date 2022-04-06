
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

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow) {
    if(aMissedAmmoInRow == 5) {
        ENGINE_playSoundOnPlayersChest(aPlayerIndex, 7);
    } else if (aMissedAmmoInRow == 10) {
        ENGINE_playSoundOnPlayersChest(aPlayerIndex, 9);
    }
}

void PLUGIN_setup() {
    gPointsKill = ENGINE_getTcvInt("pointsKill", 0);
    gPointsDeath = ENGINE_getTcvInt("pointsDeath", 0);
    gPointsHit = ENGINE_getTcvInt("pointsHit", 0);
    gPointsPerShoot = ENGINE_getTcvInt("pointsPerShoot", 0);
    gPointsDoubleKill = ENGINE_getTcvInt("pointsDoubleKill", 0);
    gPointsMonsterKill = ENGINE_getTcvInt("pointsMonsterKill", 0);
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
            gPointsHit * (p->hits - p->kills) +
            gPointsPerShoot * p->usedAmmo +
            gPointsDoubleKill * p->bonusKillounter[2] +
            gPointsMonsterKill * p->bonusKillounter[3];
        score += (int32_t)round(round(p->shootingAccuracy) * gPointsShootPrecision);
        p->score = score;
    }
}
