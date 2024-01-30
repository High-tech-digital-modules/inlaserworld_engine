---
layout: default
title: Music engine
parent: Concepts
---

# Music engine
There is possibility to control arena music from plugin now. To start control
arena music engine use:

```cpp
void PLUGIN_setup() {
    // ...
    ENGINE_customMusicControl();
    // ...
}
```

this will let engine know that music will be controlled from plugin. Than we need
two objects to get started:
```cpp
FMOD::Channel *gpSoundChannel = nullptr;
FMOD::Channel *gpMainChannel = nullptr;
FMOD::Sound *gpMainMusicPlayer = nullptr;
```
 - ```FMOD::Channel``` is object that can be used for effects, volume control etc.
 - ```FMOD::Sound``` is object used for music stream

## Music
Before we actually play something note following functions:
```cpp
ENGINE_getSelectedMusicUrl(Engine::musicLoaded)
```
 - ```Engine::musicLoaded``` - when game is uploaded to chest
 - ```Engine::musicPrepared,``` - when game started, countdown
 - ```Engine::musicEnded,``` - when game ends
 - ```Engine::musicMain``` - main music during game

```cpp
ENGINE_getMediaUrl(mainMusic)
```
where ```mainMusic``` is custom variable.

Both functions return url string and music can be played by:

```cpp
// This is helper function of course could be used differently
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
```

if sound needs to be stopped just use:
```cpp
if(gpMainMusicPlayer != nullptr) {
    gpMainMusicPlayer->release();
}
```

## Sounds
Sounds are almost the same check following code how to use it:

```cpp
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
```

for the sounds it is useful to use callback e.g. queue could be implemented and
when callback is called the plugin can take another sound and play it. Check out 
example of callback:
```cpp
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
```