---
layout: default
title: Main unit engine functions
parent: Engine API
---

# Main unit API engine
{: .no_toc }
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
Function for setting time interval.

```cpp
int ENGINE_setTimer(void (*apHandler)(), uint32_t aInterval);
```

### Params
{: .no_toc }
- **apHandler** - Handler called
- **aInterval** - Interval in miliseconds
- **return** - id of timer

### Usage
{: .no_toc }
```cpp
int gTimer = 0;

void handler() {

}
void PLUGIN_setup() {
...
    gTimer = ENGINE_setTimer(&handler, 100);
...
}
```
---
## ENGINE_clearTimer
ENGINE_setTimer will return id of timer. Use this id to clearInterval if needed.

```cpp
void ENGINE_clearTimer(uint8_t aTimerIndex);
```

### Params
{: .no_toc }
- **aTimerIndex** - id of timer

---
## ENGINE_getGameState
Return actual state of the game
```cpp
uint16_t ENGINE_getGameState();
```

### Params
{: .no_toc }
- **return** - game state 

---
## ENGINE_getPreviousGameState
Return state of game one second back, could be used to detect transition of state
```cpp
uint16_t ENGINE_getPreviousGameState();
```

### Params
{: .no_toc }
- **return** - game state one second back

---
## ENGINE_getRemainingTime
Get remaining time of game
```cpp
int32_t ENGINE_getRemainingTime();
```

### Params
{: .no_toc }
- **return** - Remaining time of game

---
## ENGINE_getElapsedTime
Get elapsed time of game
```cpp
int32_t ENGINE_getElapsedTime();
```

### Params
{: .no_toc }
- **return** - Elapsed time of game

---
## ENGINE_sendCustomMessage
This method is used to send custom data to any player by his index.
```cpp
void ENGINE_sendCustomMessage(const uint8_t *apData, 
    uint8_t aLen, int16_t aPlayerIndexTo);
```

### Params
{: .no_toc }
- **apData** - data to be send
- **aLen** - length of data
- **aPlayerIndexTo** - Index of player who will receive message

---
## ENGINE_getPLayers
Get list of actual players.
```cpp
Player *ENGINE_getPLayers();
```

### Params
{: .no_toc }
- **return** - List of players in game

---
## ENGINE_getPlayersLength
Get length of players.
```cpp
uint8_t ENGINE_getPlayersLength();
```

### Params
{: .no_toc }
- **return** - Length of players

---
## ENGINE_getPlayerByIndex
Get player by index
```cpp
Player *ENGINE_getPlayerByIndex(uint8_t aIndex);
```

### Params
{: .no_toc }
- **return** - player
- **aIndex** - index of player

---
## ENGINE_getPlayerByCode
Get player by index by code
```cpp
Player *ENGINE_getPlayerByCode(uint8_t aCode);
```

### Params
{: .no_toc }
- **return** - player
- **aCode** - code of player

---
## ENGINE_setPLayerByIndex
Set player by index
```cpp
void ENGINE_setPLayerByIndex(Player *aPlayer, uint8_t aIndex);
```

### Params
{: .no_toc }
- **aPlayer** - player
- **aIndex** - index of player

---
## ENGINE_setUVLightModule
Set uv set or not
```cpp
void ENGINE_setUVLightModule(uint8_t aModuleIndex, bool aOn);
```

### Params
{: .no_toc }
- **aModuleIndex** - Index of module where UV needs to be set
- **aOn** - set or reset UV

---

## ENGINE_playSound
Play sound by name
```cpp
uint8_t ENGINE_playSound(const char * apNameOfSound);
```

### Params
{: .no_toc }
- **apNameOfSound** - name of sound to be played
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_playSoundOnPlayersChest
Play sound on player chest
```cpp
uint8_t ENGINE_playSoundOnPlayersChest(const uint8_t aPLayerIndex, const uint8_t aIndexOfSound);
```

### Params
{: .no_toc }
- **aPLayerIndex** - index of player
- **aIndexOfSound** - index of sound
- **return** - 0 if OK, higher than 1 if error

---
## ENGINE_getTcvString
Get game template custom string variable by name
```cpp
std::string ENGINE_getTcvString(const char * aName, std::string aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - value

---
## ENGINE_getTcvUInt
Get game template custom unsigned integer variable by name
```cpp
uint32_t ENGINE_getTcvUInt(const char * aName, uint32_t aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - value

---
## ENGINE_getTcvInt
Get game template custom signed integer variable by name
```cpp
int32_t ENGINE_getTcvInt(const char * aName, int32_t aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - value

---
## ENGINE_getTcvDouble
Get game template custom double variable by name
```cpp
double (const char * aName, double aDefValue)
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - value

---
## ENGINE_getTcvBoolean
Get game template custom boolean variable by name
```cpp
bool ENGINE_getTcvBoolean(const char * aName, bool aDefValue);
```

### Params
{: .no_toc }
- **aName** - name of variable
- **aDefValue** - default value if variable with name not found
- **return** - value

---
## ENGINE_setPlayerPropString
Set string prop for player by index
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
Set number prop for player by index
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
Set boolean prop for player by index
```cpp
void ENGINE_setPlayerPropBool(uint8_t aIndex, const char* aName, bool aValue);s
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aValue** - value of property

---
## ENGINE_getPlayerPropString
Get string property by index and name
```cpp
const char* ENGINE_getPlayerPropString(uint8_t aIndex, const char* aName, const char* aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_getPlayerPropNumber
Get number property by index and name
```cpp
double ENGINE_getPlayerPropNumber(uint8_t aIndex, const char* aName, double aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_getPlayerPropBool
Get boolean property by index and name
```cpp
bool ENGINE_getPlayerPropBool(uint8_t aIndex, const char* aName, bool aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of player
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_setTeamPropString
Set string prop for team by index
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
Set number prop for team by index
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
Set boolean prop for team by index
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
Get string property by index and name
```cpp
const char* ENGINE_getTeamPropString(uint8_t aIndex, const char* aName, const char* aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_getTeamPropNumber
Get number property by index and name
```cpp
double ENGINE_getTeamPropNumber(uint8_t aIndex, const char* aName, double aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_getTeamPropBool
Get boolean property by index and name
```cpp
bool ENGINE_getTeamPropBool(uint8_t aIndex, const char* aName, bool aDefaultValue);
```

### Params
{: .no_toc }
- **aIndex** - index of team
- **aName** - name of property
- **aDefaultValue** - fallback value of property

---
## ENGINE_lightAddOperation
Add operation to light buffer
```cpp
bool ENGINE_lightAddOperation(
    std::string aAddress, const operationT &aOperation, bool aSendEnabled = false);
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
bool ENGINE_lightUpdateOperation(std::string aAddress, 
    const operationT &aOperation, uint8_t aIndex, bool aSendEnabled = false);
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
bool ENGINE_lightDeleteOperation(
    std::string aAddress, uint8_t aIndex, bool aSendEnabled = false);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aIndex** - index in buffer
- **aSendEnabled** - if true it sends to device directly
- **return** - true if error

---
## ENGINE_lightSyncOperationBuffer
Sync operation buffer
```cpp
void ENGINE_lightSyncOperationBuffer(std::string aAddress);
```

### Params
{: .no_toc }
- **aAddress** address of light device

---
## ENGINE_lightClearOperationBuffer
Clear operation buffer
```cpp
void ENGINE_lightClearOperationBuffer(std::string aAddress);
```

### Params
{: .no_toc }
- **aAddress** - address of light device

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
- **aSendEnabled** - directly send to device
- **return** - aMask based if there was error of not for each specific position bit error value provided

---
## ENGINE_lightSyncSequenceBuffer
Function for synchronize sequence buffer
```cpp
void ENGINE_lightSyncSequenceBuffer(std::string aAddress, uint8_t aMask);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - mask which channels will be synchronized

---
## ENGINE_lightClearSequenceBuffer
Function for clear sequence buffer
```cpp
void ENGINE_lightClearSequenceBuffer(std::string aAddress, uint8_t aMask);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - mask which channels will be synchronized

---
## ENGINE_lightStartSequence
Function start mode on channels
```cpp
void ENGINE_lightStartSequence(std::string aAddress, uint16_t aFlags);
```

### Params
{: .no_toc }
- **aAddress** - address of light device
- **aMask** - based on documentation
