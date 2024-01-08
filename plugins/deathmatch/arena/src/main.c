#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef VSCODE
#include "custom_variables_map.h"
#include "engine_functions.h"
#include "sound_set_map.h"
#include "submodules.h"
#include "fmod.hpp"
#endif

FMOD::Channel *gpMainChannel = nullptr;
FMOD::Channel *gpSoundChannel = nullptr;
FMOD::Channel *gpMineChannel = nullptr;
FMOD::Sound *gpMainMusicPlayer = nullptr;

volatile uint8_t gvBonusIndex = 1;
// volatile DeviceT gvBonusDevice;
volatile uint8_t gvBonusShotCode = 0;
// volatile uint8_t gvLastPlayerShotting = 0;
// volatile uint8_t gvLastPlayerObtainedBonus = 0;
// volatile uint8_t gvShotsCounter = 0;
// volatile uint8_t gvLightBufferActual = 0;
// volatile uint8_t gvLightBufferMask = 0;
// volatile uint16_t gvLightBufferCmd = 0;
volatile uint8_t gvBonusNonactive = 1;
volatile uint8_t gvMineNonactive = 1;
volatile uint8_t gvSingleModule = 0; // info if there is only one smart module in arena

int gTimerBonusDeactive = 0;
int gTimerBonusActivate = 0;

int gTimerMineDeactive = 0;
int gTimerMineActivate = 0;
int gTimerMineShoot = 0;

const ColorT gColorBonus = {0xFF, 0xFF, 0x00}; // yellow color
const ColorT gColorBlack = {0x00, 0x00, 0x00};
ColorT gColorArena = {0x00, 0x00, 0x00};
const char pgLightBroadcastAddress[] = "000000000000000000";

std::string gBonusModule;
std::string gMineModule;

void selectNewBonus(void);
void selectBonusActivateTime(void);
void selectMineActivateTime(void);
void playSoundFromSet(uint32_t aIndex);
void playSound(uint32_t aMediaId);

void stopMainChannel() {
    if(gpMainMusicPlayer != nullptr) {
        gpMainMusicPlayer->release();
    }
}

bool playMusicOnMainChannel(const std::string& aUrl) {
    if (aUrl.empty()) {
        return false;
    }
    if(gpMainMusicPlayer != nullptr) {
        gpMainMusicPlayer->release();
    }
    ENGINE_getAudioEngine()->createStream(
            (aUrl).data(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &gpMainMusicPlayer);
    ENGINE_getAudioEngine()->playSound(gpMainMusicPlayer, nullptr, false, &gpMainChannel);
    return true;
}

void handlerBonusDeactivate() {
    // printf("Bonus deactivated\n");
    if (gvBonusNonactive == 0) {
        playSoundFromSet(BonusDeactivated);
    } else {
    }
    ENGINE_lightSetColors(gBonusModule, gColorArena, gColorBlack, gColorBlack, 1);
    ENGINE_clearTimer(gTimerBonusDeactive);
    selectBonusActivateTime();
    gvBonusNonactive = 1;
}

void handlerBonusActivate() {
    // printf("Bonus activated\n");
    // choose new module to be bonus
    std::string lBonusNewAddress;
    if (gvSingleModule == 1) {
        if (gvMineNonactive == 1) {
            // printf("Bonus the same\n");
            lBonusNewAddress = gBonusModule;
        } else {
            // printf("Bonus delayed\n");
            ENGINE_clearTimer(gTimerBonusActivate);
            gTimerBonusActivate = ENGINE_setTimer(handlerBonusActivate, 10000U);
            return;
        }
    } else {
        do {
            lBonusNewAddress = ENGINE_getRandomBonusModule().address;
        } while ((lBonusNewAddress == gMineModule) && (lBonusNewAddress != "none"));
    }

    if (lBonusNewAddress != "none") {
        playSoundFromSet(BonusActivated);
        gBonusModule = lBonusNewAddress;

        // start yellow light at bonus and near lights
        ENGINE_lightSetColors(gBonusModule, gColorBonus, gColorBonus, gColorBonus, 1);
        ENGINE_clearTimer(gTimerBonusActivate);
        gTimerBonusDeactive = ENGINE_setTimer(handlerBonusDeactivate, 15000U);
        gvBonusNonactive = 0;
    }
}

void handlerMineDeactivate() {
    // printf("Mine deactivated\n");
    ENGINE_lightSetColors(gMineModule, gColorArena, gColorBlack, gColorBlack, 1);
    ENGINE_clearTimer(gTimerMineDeactive);
    selectMineActivateTime();
    gvMineNonactive = 1;
}

void handlerMineShoot() {
    playSound(sfxMineExplosion);
    ENGINE_clearTimer(gTimerMineShoot);
    ENGINE_lightSetShooting(gMineModule, 0x00, 0x05, 2); // info, shooting periode*100ms, number of shots
    usleep(40000);
}

void handlerMineActivate() {
    // printf("Mine activated\n");
    // choose new module to be bonus
    std::string lMineNewAddress;
    if (gvSingleModule == 1) {
        if (gvBonusNonactive == 1) {
            lMineNewAddress = gMineModule;
            // printf("Mine the same\n");
        } else {
            // printf("Mine delay\n");
            ENGINE_clearTimer(gTimerMineActivate);
            gTimerMineActivate = ENGINE_setTimer(handlerMineActivate, 10000U);
            return;
        }
    } else {
        do {
            lMineNewAddress = ENGINE_getRandomBonusModule().address;
        } while ((lMineNewAddress == gBonusModule) && (lMineNewAddress != "none"));
    }

    if (lMineNewAddress != "none") {
        playSoundFromSet(MineActivated);

        gMineModule = lMineNewAddress;

        ENGINE_lightStartSequence(gMineModule, 0x5550); // stop all operations
        usleep(40000);
        ENGINE_lightStartSequence(gMineModule, 0x9990); // switch to buffer 2
        usleep(40000);
        ENGINE_lightStartSequence(gMineModule, 0x3330); // run sequence once
        usleep(40000);

        ENGINE_clearTimer(gTimerMineActivate);
        gTimerMineShoot = ENGINE_setTimer(handlerMineShoot, 2900);
        gTimerMineDeactive = ENGINE_setTimer(handlerMineDeactivate, 3500);
        gvMineNonactive = 0;
    }
}

void selectNewBonus(void) {
    gvBonusIndex = rand() % 3 + 1;
    // printf("new bonus %d\n", gvBonusIndex);
}

void selectBonusActivateTime(void) {
    gTimerBonusActivate = ENGINE_setTimer(handlerBonusActivate, 5000 + rand() % 5000); // 15000 + rand() % 15000
}

void selectMineActivateTime(void) {
    gTimerMineActivate = ENGINE_setTimer(handlerMineActivate, 10000 + rand() % 10000);
}

void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
                              uint16_t aOldValue,
                              uint16_t aNewValue,
                              uint16_t aMissedAmmoInRow) {
}

void PLUGIN_newLeader(const Player *apPLayer) {
    uint8_t lPrevState = ENGINE_getPreviousGameState();
    if (lPrevState != 0x03 && lPrevState != 0xFF) {
        playSoundFromSet(arenaLeaderChange);
    }
}

void PLUGIN_setup() {
    ENGINE_customMusicControl();
    //playMusicOnMainChannel(ENGINE_getSelectedMusicUrl(Engine::musicLoaded));
    //playMusicOnMainChannel(ENGINE_getMediaUrl(mainMusic)); // Example how to play it directly from media id
    /*gpMainChannel->setCallback([](FMOD_CHANNELCONTROL *channelcontrol, FMOD_CHANNELCONTROL_TYPE controltype, FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, void *commanddata1, void *commanddata2) -> FMOD_RESULT {
        if (controltype == FMOD_CHANNELCONTROL_CALLBACK_END) {
            // the sound has finished playing here
        }
        printf("Callback called??\n");
        return FMOD_OK;  // indicate all went well
    });*/
    LIGHT_switchOffAllModules();
    LIGHT_setArenaLightsColor(colorArena, 1);

    gColorArena = colorArena;

    if (bonusEnabled == true || mineEnabled == true) {
        selectNewBonus();

        gvBonusShotCode = ENGINE_getTcvUInt("bonusShotCode", 101);
        if ((gvBonusShotCode < 101) || (gvBonusShotCode > 120)) {
            gvBonusShotCode = 101;
        }

        std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();

        if (lBonusModules.size() == 1) {
            // printf("Single module\n");
            gvSingleModule = 1;
            gBonusModule = lBonusModules[0].address;
            gMineModule = lBonusModules[0].address;
        }
        // uint8_t lBonusModulesCount = lBonusModules.size();
        // for(int i = 0; i < lBonusModulesCount; i++)

        // go thru all devices in lBonusModules
        for (DeviceT lModule : lBonusModules) {
            // printf("module %s\n",lModule.address.c_str());
            // send bonusShotCode to bonus module
            ENGINE_lightSetShootCode(lModule.address, bonusShotCode);

            // send color to selected bonus module, pulsing in buffer 1, 3 fast white blinks in buffer 2
            ENGINE_lightStartSequence(lModule.address, 0x0550); // stop all operations
            usleep(40000);
            ENGINE_lightClearOperationBuffer(lModule.address);
            ENGINE_lightClearSequenceBuffer(lModule.address, 0b00111111);

            // 0 blinking, white, fast
            ENGINE_lightAddOperation(lModule.address, {0, 0xFF, 0xFF, 0xFF, 5, 5});

            // 1 pulsing, red, slow
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 40, 40});
            // 2 pulsing, red, medium slow
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 30, 30});
            // 3 pulsing, red, medium
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 20, 20});
            // 4 pulsing, red, medium fast
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 10, 10});
            // 5 pulsing, red, fast
            ENGINE_lightAddOperation(lModule.address, {1, 0xFF, 0x00, 0x00, 5, 5});

            // white blinking to circuit 2 and 3, buffer 1 for both
            ENGINE_lightAddSequence(lModule.address, {0, 2}, 0b00010100); //{index, repeat}

            // red pulsing for mine + white boom, to circuit 2 and 3, buffer 2 for both
            // length is 3,35 s
            ENGINE_lightAddSequence(lModule.address, {1, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {2, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {3, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {4, 1}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {5, 4}, 0b00101010); //{index, repeat}
            ENGINE_lightAddSequence(lModule.address, {0, 3}, 0b00101010); //{index, repeat}

            usleep(40000);
            ENGINE_lightSyncOperationBuffer(lModule.address);
            usleep(40000);
            ENGINE_lightSyncSequenceBuffer(lModule.address, 0b00111110);
            usleep(40000);
            ENGINE_lightStartSequence(lModule.address, 0x0770);
            usleep(40000);
        }
    }
}

void PLUGIN_destroyed() {
    LIGHT_setColorStandby();
    if (gpMainMusicPlayer != nullptr){
		gpMainMusicPlayer->release();
		gpMainMusicPlayer = nullptr;
	}
}

FMOD_RESULT F_CALLBACK onSoundFinished(
    FMOD_CHANNELCONTROL *channelcontrol, 
    FMOD_CHANNELCONTROL_TYPE controltype, 
    FMOD_CHANNELCONTROL_CALLBACK_TYPE callbacktype, 
    void *commanddata1, void *commanddata2) {
    // @Daniel's Note ... This is probably sheduled from FMOD system
    // so mutex is not used like if any other PLUGIN function is called
    // be carefull about using any other ENGINE functions then the one
    // for controlling sounds
    if (controltype == FMOD_CHANNELCONTROL_CALLBACK_END) {
        auto* channel = reinterpret_cast<FMOD::Channel*>(channelcontrol);
        if (channel) {
            FMOD::Sound* currentSound;
            channel->getCurrentSound(&currentSound);
            if (currentSound) {
                // Do something with the currentSound...
                char name[256];
                currentSound->getName(name, 256);
                printf("%s\n", name);
            }
        }
    }
    return FMOD_OK;
}

void playSoundFromSet(uint32_t aIndex) {
    FMOD::Sound *lSound = ENGINE_getSoundFromSoundSet(aIndex);
    if(lSound != nullptr) {
        ENGINE_getAudioEngine()->playSound(lSound, nullptr, false, &gpSoundChannel);
        gpSoundChannel->setCallback(onSoundFinished);
    }   
}

void playSound(uint32_t aMediaId) {
    FMOD::Sound *lSound = ENGINE_getSoundFromMediaLibrary(aMediaId);
    if(lSound != nullptr) {
        ENGINE_getAudioEngine()->playSound(lSound, nullptr, false, &gpMineChannel);
        gpMineChannel->setCallback(onSoundFinished);
    }   
}

void PLUGIN_main() {
    int32_t time = ENGINE_getRemainingTime();
    uint8_t state = ENGINE_getPreviousGameState();
    switch (time) {
    case 5:
        playSoundFromSet(five);
        break;
    case 4:
        playSoundFromSet(four);
        break;
    case 3:
        playSoundFromSet(three);
        break;
    case 2:
        playSoundFromSet(two);
        break;
    case 1:
        playSoundFromSet(one);
        break;
    }

    if (state != 0x03 && time == 300) {
        playSoundFromSet(Min5Remaining);
    }
    if (state != 0x03 && time == 60) {
        playSoundFromSet(Min1Remaining);
    }

    for (uint8_t i = 0; i < ENGINE_getPlayersLength(); i++) {

        Player *p = ENGINE_getPlayerByIndex(i);
        int32_t score =
            pointsKill * p->kills +
            pointsDeath * (p->deaths - p->teamDeaths) +
            pointsHit * (p->hits - p->kills) +
            pointsPerShoot * p->usedAmmo +
            pointsDoubleKill * p->bonusKillCounter[2] +
            pointsMonsterKill * p->bonusKillCounter[3];
        p->score = score;
    }
}

void PLUGIN_gameStateChanged(uint8_t aState) {
    printf("New state: %d, %d\n", aState, ENGINE_getPreviousGameState());
    if(aState == 0x03 && ENGINE_getPreviousGameState() == 0xFF) {
        if(!playMusicOnMainChannel(ENGINE_getSelectedMusicUrl(Engine::musicPrepared))) {
            stopMainChannel();
        }
    }
    if (aState == 0x01 && ENGINE_getPreviousGameState() == 0x03) {
        std::vector<DeviceT> lBonusModules = ENGINE_getBonusModules();
        if(!playMusicOnMainChannel(ENGINE_getSelectedMusicUrl(Engine::musicMain))) {
            stopMainChannel();
        }
        if (lBonusModules.size() > 0) {
            if (bonusEnabled) {
                selectBonusActivateTime();
            }
            if (mineEnabled) {
                selectMineActivateTime();
            }
        }
    }
}

void PLUGIN_playerDidBonusKill(uint8_t aPlayerIndex, uint8_t aBonus) {
    ACHIEVEMENTS_playerDidBonusKill(aPlayerIndex, aBonus);
}

void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo) {
    Player *p = ENGINE_getPlayerByCode(aCode);

    if (p == NULL) {
        return;
    }

    if (bonusEnabled == true && (strcmp(aAddress.c_str(), gBonusModule.c_str()) == 0) && gvBonusNonactive == 0) {
        playSoundFromSet(BonusTaken);
        ENGINE_clearTimer(gTimerBonusDeactive);
        gvBonusNonactive = 2;
        handlerBonusDeactivate();

        // blink to show hitted, once the sequence
        ENGINE_lightStartSequence(gBonusModule, 0x0550); // stop all operations
        usleep(40000);
        ENGINE_lightStartSequence(gBonusModule, 0x0770); // switch to buffer 1
        usleep(40000);
        ENGINE_lightStartSequence(gBonusModule, 0x0330); // do sequence once
        usleep(40000);

        if (bonusSendByXbee == true) {
            uint8_t lData2[2] = {'b', gvBonusIndex};
            ENGINE_sendCustomMessage((uint8_t *)lData2, 2, p->index);
        } else {
            ENGINE_lightSetShooting(gBonusModule, gvBonusIndex << 4, 0x05, 6); // info, shooting periode*100ms, number of shots
            usleep(40000);
        }

        // select next bonus
        selectNewBonus();
    }
}

void PLUGIN_customVariableChanged(const std::string& aName) {
    if(aName == "mainVolume") {
        mainVolume = ENGINE_getTcvUInt("mainVolume", 100);
        gpMainChannel->setVolume((double)mainVolume * 0.01);    
    }
}