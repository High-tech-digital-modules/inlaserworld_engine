
#include <cmath>

ColorT gColorDarkRed = {0x10, 0x00, 0x00};
const ColorT gColorBlack = {0x00, 0x00, 0x00};

void PLUGIN_newLeader(const Player *apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        ENGINE_playSoundFromSoundSet(arenaLeaderChange);
    }
}

void PLUGIN_setup() {
    if (redLightPercentage > 100) {
        redLightPercentage = 100;
    }
    gColorDarkRed.red = 255 * redLightPercentage / 100;
    LIGHT_switchOffAllModules();
    LIGHT_setArenaLightsColor(redLightsEnabled ? gColorDarkRed : gColorBlack, UVEnabled ? 1 : 0);
}

void PLUGIN_destroyed() {
    LIGHT_setColorStandby();
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch (time) {
    case 5:
        ENGINE_playSoundFromSoundSet(five);
        break;
    case 4:
        ENGINE_playSoundFromSoundSet(four);
        break;
    case 3:
        ENGINE_playSoundFromSoundSet(three);
        break;
    case 2:
        ENGINE_playSoundFromSoundSet(two);
        break;
    case 1:
        ENGINE_playSoundFromSoundSet(one);
        break;
    }

    if (state != 0x03 && time == 300) {
        ENGINE_playSoundFromSoundSet(Min5Remaining);
    }
    if (state != 0x03 && time == 60) {
        ENGINE_playSoundFromSoundSet(Min1Remaining);
    }

    for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {

        Player *p = ENGINE_getPlayerByIndex(i);
        int32_t score =
            pointsKill * p->kills +
            pointsDeath * (p->deaths) +
            pointsPerShoot * p->usedAmmo +
            pointsDoubleKill * p->bonusKillCounter[2] +
            pointsMonsterKill * p->bonusKillCounter[3];
        p->score = score;
    }
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}
