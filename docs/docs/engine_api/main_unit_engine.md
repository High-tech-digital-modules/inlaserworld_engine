---
layout: default
title: Main unit engine functions
parent: Engine API
---

# Main unit API engine
{: .no_toc}
This is set of function that can be called from plugin to do something with system.

<details markdown="block">
  <summary>
    Table of contents
  </summary>
{: .text-delta }
1. TOC
{:toc}
</details>

---
## ENGINE_setTimer
Setup timer which calls handler when interval elapsed

```cpp
int ENGINE_setTimer(void (*apHandler)(), uint32_t aInterval);
```

### Params
{: .no_toc }
- **apHandler** - Handler called
- **aInterval** - Interval in miliseconds
- **return** - index of timer

### Usage
{: .no_toc }
```cpp
 int gTimer = 0;

 void handler() {

 }
 void PlUGIN_setup() {
 ...
    gTimer = ENGINE_setTimer(&handler, 100);
 ...
 }
```

---
## ENGINE_clearTimer
Clear timer created by setTimer

```cpp
void ENGINE_clearTimer(uint8_t aTimerIndex);
```

### Params
{: .no_toc }
- **aTimerIndex** index of timer

---
## ENGINE_getGameState
Get game state

```cpp
uint16_t ENGINE_getGameState();
```

- **return** - Return state of the running game

---
## ENGINE_getPreviousGameState
Get game previous state

```cpp
uint16_t ENGINE_getPreviousGameState();
```

- **return** - Return previous state of the running game

---
## ENGINE_getRemainingTime
Get remaining time of game

```cpp
int32_t ENGINE_getRemainingTime();
```

- **return** - Remaining time of game

---
## ENGINE_getElapsedTime
Get elapsed time of game

```cpp
int32_t ENGINE_getElapsedTime();
```

- **return** - Elapsed time of the game

---
## ENGINE_sendCustomMessage
Send custom message to player

```cpp
void ENGINE_sendCustomMessage(const uint8_t *apData, uint8_t aLen, int16_t aPlayerIndexTo);
```

### Params
{: .no_toc }
- **apData** - data to be send
- **aLen** - Length of data
- **aPlayerIndexTo** - Index of player who will receive message

---
## ENGINE_getPlayers
get list of players

```cpp
Player * ENGINE_getPlayers();
```

- **return** - list of players

---
## ENGINE_getPlayersLength
get length of player

```cpp
uint8_t ENGINE_getPlayersLength();
```

- **return** - length of player

---
## ENGINE_getPlayerByIndex
get player by index

```cpp
Player * ENGINE_getPlayerByIndex(uint8_t aIndex);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **return** - player

---
## ENGINE_getPlayerByCode
get player by index

```cpp
Player * ENGINE_getPlayerByCode(uint8_t aCode);
```

### Params
{: .no_toc }
- **aCode** - index of device
- **return** - player

---
## ENGINE_getTeamsLength
get length of teams

```cpp
uint8_t ENGINE_getTeamsLength();
```

- **return** - length of teams

---
## ENGINE_getTeamByIndex
get team by index

```cpp
Team * ENGINE_getTeamByIndex(uint8_t aIndex);
```

### Params
{: .no_toc }
- **aCode** - index of team
- **return** - team

---
## ENGINE_getTeamById
get team by id

```cpp
Team * ENGINE_getTeamById(std::string aId);
```

### Params
{: .no_toc }
- **aCode** - id of team
- **return** - team

---
## ENGINE_setUVLightModule
Set UV module color

```cpp
void ENGINE_setUVLightModule(uint8_t aModuleIndex, bool aOn);
```

### Params
{: .no_toc }
- **aModuleIndex** - Index of module where UV needs to be set
- **aOn** - set or reset UV

---
## ENGINE_playSound
play sound by name

```cpp
uint8_t ENGINE_playSound(const char * apNameOfSound);
```

### Params
{: .no_toc }
- **apNameOfSound** - name of sound to be played
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_playSoundId
play sound by name

```cpp
uint8_t ENGINE_playSoundId(const uint32_t aMediaId);
```

### Params
{: .no_toc }
- **apNameOfSound** - name of sound to be played
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_playSoundFromSoundSet
play sound from sound set

```cpp
uint8_t ENGINE_playSoundFromSoundSet(const uint32_t aIndex);
```

### Params
{: .no_toc }
- **aIndex** - index of sound from selected set
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_playSoundOnPlayersChest
play sound on players device

```cpp
uint8_t ENGINE_playSoundOnPlayersChest(const uint8_t aPlayerIndex, const uint32_t aIdOfSound);
```

### Params
{: .no_toc }
- **aPlayerIndex\n** aPlayerIndex
- **aIdOfSound\n** aIdOfSound
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_getTcvString
get game template custom string variable by name

```cpp
std::string ENGINE_getTcvString(const char * aName, const char * aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - property value, default if not found

---
## ENGINE_getTcvUInt
get game template custom unsigned integer variable by name

```cpp
uint32_t ENGINE_getTcvUInt(const char * aName, uint32_t aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - property value, default if not found

---
## ENGINE_getTcvInt
get game template custom signed integer variable by name

```cpp
int32_t ENGINE_getTcvInt(const char * aName, int32_t aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - property value, default if not found

---
## ENGINE_getTcvDouble
get game template custom double variable by name

```cpp
double ENGINE_getTcvDouble(const char * aName, double aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - property value, default if not found

---
## ENGINE_getTcvBoolean
get game template custom boolean variable by name

```cpp
bool ENGINE_getTcvBoolean(const char * aName, bool aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - property value, default if not found

---
## ENGINE_getTcvDevice
get game template custom device struct by name

```cpp
DeviceT ENGINE_getTcvDevice(const char * aName);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **return** - property value, default if not found

---
## ENGINE_getTcvColorStruct
get game template custom color struct by name

```cpp
ColorT ENGINE_getTcvColorStruct(const char * aName);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **return** - property value, default if not found

---
## ENGINE_setPlayerPropString
set string prop for player by index

```cpp
void ENGINE_setPlayerPropString(uint8_t aIndex, const char* aName, const char* aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_setPlayerPropNumber
set number prop for player by index

```cpp
void ENGINE_setPlayerPropNumber(uint8_t aIndex, const char* aName, double aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_setPlayerPropBool
set boolean prop for player by index

```cpp
void ENGINE_setPlayerPropBool(uint8_t aIndex, const char* aName, bool aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_getPlayerPropString
get string property by index and name

```cpp
const char* ENGINE_getPlayerPropString(uint8_t aIndex, const char* aName, const char* aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_getPlayerPropNumber
get number property by index and name

```cpp
double ENGINE_getPlayerPropNumber(uint8_t aIndex, const char* aName, double aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_getPlayerPropBool
get boolean property by index and name

```cpp
bool ENGINE_getPlayerPropBool(uint8_t aIndex, const char* aName, bool aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_setTeamPropString
set string prop for team by index

```cpp
void ENGINE_setTeamPropString(uint8_t aIndex, const char* aName, const char* aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_setTeamPropNumber
set number prop for team by index

```cpp
void ENGINE_setTeamPropNumber(uint8_t aIndex, const char* aName, double aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_setTeamPropBool
set boolean prop for team by index

```cpp
void ENGINE_setTeamPropBool(uint8_t aIndex, const char* aName, bool aValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_getTeamPropString
get string property by index and name

```cpp
const char* ENGINE_getTeamPropString(uint8_t aIndex, const char* aName, const char* aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_getTeamPropNumber
get number property by index and name

```cpp
double ENGINE_getTeamPropNumber(uint8_t aIndex, const char* aName, double aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_getTeamPropBool
get boolean property by index and name

```cpp
bool ENGINE_getTeamPropBool(uint8_t aIndex, const char* aName, bool aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property
- **return** - property value, default if not found

---
## ENGINE_createOperation
create light operation

```cpp
operationT ENGINE_createOperation(uint8_t aMode, std::string aHex, uint16_t aT1, uint16_t aT2);
```

### Params
{: .no_toc }
- **aMode** - mode 0 - blinking, 1 - pulsing
- **aHex** - color
- **aT1** - switch on or rising time
- **aT2** - switch off or faling time
- **return** - structure of operation

---
## ENGINE_lightAddOperation
Add operation to light buffer

```cpp
 bool ENGINE_lightAddOperation(std::string aAddress, const operationT &aOperation, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aOperation** - operation struct
- **aSendEnabled** - if true it sends to device directly
- **return** - true if error

---
## ENGINE_lightUpdateOperation
Update operation in index

```cpp
 bool ENGINE_lightUpdateOperation(std::string aAddress, const operationT &aOperation, uint8_t aIndex, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aOperation** - operation struct
- **aIndex** - index in buffer
- **aSendEnabled** - if true it sends to device directly
- **return** - true if error

---
## ENGINE_lightDeleteOperation
Delete operation at index

```cpp
 bool ENGINE_lightDeleteOperation(std::string aAddress, uint8_t aIndex, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aIndex** - index in buffer
- **aSendEnabled** - if true it sends to device directly
- **return** - true if error

---
## ENGINE_lightSyncOperationBuffer
sync operation buffer

```cpp
void ENGINE_lightSyncOperationBuffer(std::string aAddress);
```

### Params
{: .no_toc }
- **aAddress** address of light device

---
## ENGINE_lightClearOperationBuffer
sync operation buffer

```cpp
void ENGINE_lightClearOperationBuffer(std::string aAddress);
```

### Params
{: .no_toc }
- **aAddress** address of light device

---
## ENGINE_lightAddSequence
Add sequence to sequence buffer for light

```cpp
 uint8_t  ENGINE_lightAddSequence(std::string aAddress,
		const sequenceT &aSequence, uint8_t aMask, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aSequence** - sequence struct
- **aMask** - mask which channels will receive this update
- **aSendEnabled** - directly send to device
- **return** - aMask based if there was error of not for each specific position bit error value provided

---
## ENGINE_lightUpdateSequence
Update sequence buffer

```cpp
 uint8_t  ENGINE_lightUpdateSequence(std::string aAddress,
		const sequenceT &aSequence, uint8_t aMask, uint8_t aIndex, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aSequence** - sequence stuct
- **aMask** - mask which channels will receive this update
- **aIndex** - index of sequence to be updated
- **aSendEnabled** - directly send to device
- **return** - aMask based if there was error of not for each specific position bit error value provided

---
## ENGINE_lightDeleteSequence
Delete from sequence buffer

```cpp
 uint8_t  ENGINE_lightDeleteSequence(std::string aAddress,
		uint8_t aMask, uint8_t aIndex, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aMask** - mask which channels will receive this update
- **aIndex** - index of sequence to be deleted
- **aSendEnabled-** directly send to device
- **return** - aMask based if there was error of not for each specific position bit error value provided

---
## ENGINE_lightSyncSequenceBuffer
function for synchronize sequence buffer

```cpp
void ENGINE_lightSyncSequenceBuffer(std::string aAddress, uint8_t aMask);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - mask which channels will be synchronized

---
## ENGINE_lightClearSequenceBuffer
function for clear sequence buffer

```cpp
void ENGINE_lightClearSequenceBuffer(std::string aAddress, uint8_t aMask);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - mask which channels will be synchronized

---
## ENGINE_lightStartSequence
function start mode on channels

```cpp
void ENGINE_lightStartSequence(std::string aAddress, uint16_t aFlags);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - based on documentation

---
## ENGINE_lightSetShootCode
set code used for shoot

```cpp
void ENGINE_lightSetShootCode(std::string aAddress, uint8_t aCode);
```

### Params
{: .no_toc }
- **code** of shoot

---
## ENGINE_lightSetShooting
set shooting by bonus module

```cpp
 void ENGINE_lightSetShooting(std::string aAddress,
		int16_t aInfo = -1, int16_t aDelay = -1, int16_t
		aCount = -1);
```

### Params
{: .no_toc }
- **aInfo** - info in shoot
- **aDelay** - Period in N x 100ms while 5 is minimum value
- **aCount** - Number of shoots

### Usage
{: .no_toc }
```cpp

 // This will do one shot with available code, info 0
 ENGINE_lightSetShooting("<address>");

 // This will do one shot with available code, info 0x01
 ENGINE_lightSetShooting("<address>", 0x01);

 // This will do endless shooting, with info 0x00
 ENGINE_lightSetShooting("<address>", 0x00, 0x05);

 // This will do endless shooting, with info 0x00 with 0,5s shooting period
 ENGINE_lightSetShooting("<address>", 0x00, 0x05);

 // This will do specific number (32) of shoots, with info 0x00 with 0,5s period
 ENGINE_lightSetShooting("<address>", 0x00, 0x05, 32);

 // To stop endless shooting
 ENGINE_lightSetShooting("<address>", 0x00, 0x00);
```

---
## ENGINE_lightLock
Lock circuits to not be override by global setting

```cpp
void ENGINE_lightLock(std::string aAddress, uint8_t aLock);
```

### Params
{: .no_toc }
- **aLock** - lock 0b0000YXVU

		 U - First circuit
		 V - Second circuit
		 X - Third circuit
		 Y - UV circuit
		 0 - unlocked
		 1 - locked

---
## ENGINE_lightSetColors
Set module colors

```cpp
void ENGINE_lightSetColors(
		const std::string aAddress,
		ColorT aCircuitOne,
		ColorT aCircuitTwo,
		ColorT aCircuitThree,
		uint8_t aCircuitUv);
```

### Params
{: .no_toc }
- **aAddress** - Address of module
- **aCircuitOne** - Color struct of first circuit
- **aCircuitTwo** - Color struct of second circuit
- **aCircuitThree** - Color struct of third circuit
- **aCircuitUv** - UV circuit value

---
## ENGINE_getRandomBonusModule
Get random bonus module from list of device selected as bonus

```cpp
DeviceT ENGINE_getRandomBonusModule();
```

- **return** - DeviceT structure

---
## ENGINE_getBonusModules
Get all bonus modules from list of device selected as bonus

```cpp
std::vector ENGINE_getBonusModules;
```

- **return** - vector of DeviceT structure

---
## ENGINE_switchPlayerTeam
Switch player team by team index and player index

```cpp
 void  ENGINE_switchPlayerTeam(const uint32_t aPlayerIndex, const uint32_t aTeamIndex, const uint8_t aFlags = 0x03);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player
- **aTeamIndex** - index of team
- **aFlags** - 0x000000ct - c = send color, t = send table

---
## ENGINE_saveResultSnapshot
Save actual results generated to its own snapshot

```cpp
void ENGINE_saveResultSnapshot();
```


---
## ENGINE_customMusicControl
Call this if music is controlled by plugin

```cpp
void ENGINE_customMusicControl();
```


---
## ENGINE_getAudioEngine
Get sound system engine

```cpp
FMOD::System* ENGINE_getAudioEngine();
```

- **return** pointer to audio system

---
## ENGINE_getSelectedMusicUrl
Get selected music url

```cpp
std::string ENGINE_getSelectedMusicUrl(Engine::MusicSelected aSelection);
```

- **return** url for selected music item

---
## ENGINE_getSoundFromMediaLibrary
Get Fmod sound object

```cpp
FMOD::Sound* ENGINE_getSoundFromMediaLibrary(const uint32_t aMediaId);
```

### Params
{: .no_toc }
- **aMediaId** -Media id of sound
- **return** sound

---
## ENGINE_getSoundFromSoundSet
Get Fmod sound object from selected sound set

```cpp
FMOD::Sound* ENGINE_getSoundFromSoundSet(const uint32_t aIndex);
```

### Params
{: .no_toc }
- **aIndex** - index in list
- **return** sound

---
## ENGINE_getMediaUrl
Get url to media item

```cpp
std::string ENGINE_getMediaUrl(const uint32_t aMediaId);
```

### Params
{: .no_toc }
- **aMediaId** - media id
- **return** Url to media item

---
## ENGINE_sendCustomMessageToVisualization
This function takes rapid json and sends it to web results

```cpp
void ENGINE_sendCustomMessageToVisualization(rapidjson::Document& aDocument);
```

### Params
{: .no_toc }
- **aValue** - rapid json value with message

---
## ENGINE_useVirtualScreen
This function let know web virtual screen to load this game

```cpp
void ENGINE_useVirtualScreen(uint8_t aScreenId, uint8_t aState);
```

### Params
{: .no_toc }
- **aScreenId** - ID of screen
- **aState** - state of screen

		 default_ - Default screen
		 gameLoaded - When game loaded
		 gameRunning - When game running
		 gameFreshFinish - When game just finished
		 gameFinished - When some previous game is loaded to be visualized
		 error - Error screen could be done

### Usage
{: .no_toc }
```cpp
 ENGINE_useVirtualScreen(1, Engine::VirtualScreen::gameLoaded);
```
