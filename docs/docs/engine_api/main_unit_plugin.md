---
layout: default
title: Main unit plugin events handlers
parent: Engine API
---

# Main unit API plugin
{: .no_toc}
This is available events that is called by engine in certain situations

<details markdown="block">
  <summary>
    Table of contents
  </summary>
{: .text-delta }
1. TOC
{:toc}
</details>

---
## PLUGIN_setup
Function for setup - This is called before game setup is uploaded to devices

```cpp
void PLUGIN_setup();
```


---
## PLUGIN_gameLoaded
When game setting is uploaded this function is called

```cpp
void PLUGIN_gameLoaded();
```


---
## PLUGIN_gameStateChanged
When game state is changed

```cpp
void PLUGIN_gameStateChanged(uint8_t aState);
```

### Params
{: .no_toc }
- **aState** - new state of game

---
## PLUGIN_receivedCustomData
When some of the devices sends custom message

```cpp
void PLUGIN_receivedCustomData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex);
```

### Params
{: .no_toc }
- **apData** - Bytes array with data
- **aLen** - length of data
- **aPlayerIndex** - Player index who send message

---
## PLUGIN_receivedCustomBackupData
Some custom data added to backup message

```cpp
void PLUGIN_receivedCustomBackupData(uint8_t *apData, uint8_t aLen, uint8_t aPlayerIndex);
```

### Params
{: .no_toc }
- **apData** - Bytes array with data
- **aLen** - length of data
- **aPlayerIndex** - Player index

---
## PLUGIN_main
Main function besides custom timers this is called every one second -
		 typically for whole game evaluation

```cpp
void PLUGIN_main();
```


---
## PLUGIN_newLeader
When system detect new leader based on score

```cpp
void PLUGIN_newLeader(const Player *apPlayer);
```

### Params
{: .no_toc }
- **apPlayer** - player object

---
## PLUGIN_playerGotHit
System detected player hit

```cpp
void PLUGIN_playerGotHit(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player who received hit
- **aWhoPlayerIndex** - index of player who did hit
- **aFriendlyFire** - if hit was friendly

---
## PLUGIN_playerGetKilled
System detected player get killed

```cpp
void PLUGIN_playerGetKilled(uint8_t aPlayerIndex, uint8_t aWhoPlayerIndex);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player who received kill
- **aWhoPlayerIndex** - index of player who did kill

---
## PLUGIN_playerDiBonusdKill
System detected player did kill

```cpp
void PLUGIN_playerDiBonusdKill(uint8_t aPlayerIndex, uint8_t aBonus);
```

### Params
{: .no_toc }
- **aPlayerIndex** - who did kill
- **aBonus** - bonus if more players where killed in row

---
## PLUGIN_playerLifeChanged
When player life changed

```cpp
void PLUGIN_playerLifeChanged(uint8_t aPlayerIndex, uint16_t aOldValue, uint16_t aNewValue);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player
- **aOldValue** - previous value
- **aNewValue** - new value

---
## PLUGIN_playerAmmoChanged
When player ammo changed

```cpp
void PLUGIN_playerAmmoChanged(uint8_t aPlayerIndex,
		uint16_t aOldValue,
		uint16_t aNewValue,
		uint16_t aMissedAmmoInRow);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player
- **aOldValue** - previous value
- **aNewValue** - new value
- **aMissedAmmoInRow** - used ammo from last hit

---
## PLUGIN_playerHealthChanged
When player health changed

```cpp
void PLUGIN_playerHealthChanged(uint8_t aPlayerIndex, uint16_t aOldValue, uint16_t aNewValue);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player
- **aOldValue** - previous value
- **aNewValue** - new value

---
## PLUGIN_playerFootStepsChanged
When footsteps changed

```cpp
void PLUGIN_playerFootStepsChanged(uint8_t aPlayerIndex, uint16_t aOldValue, uint16_t aNewValue);
```

### Params
{: .no_toc }
- **aPlayerIndex** - index of player
- **aOldValue** - previous value
- **aNewValue** - new value

---
## PLUGIN_deviceIsReady
When device is ready

```cpp
void PLUGIN_deviceIsReady(uint8_t aPlayerIndex);
```

### Params
{: .no_toc }
- **aPlayerIndex** - player's device which is ready

---
## PLUGIN_lightGotHit
When light receive hit on IR sensor

```cpp
void PLUGIN_lightGotHit(std::string aAddress, uint8_t aCode, uint8_t aInfo);
```

### Params
{: .no_toc }
- **aAddress** - address of device
- **aCode** - code of player who did hit
- **aInfo** - info coded in shot received

---
## PLUGIN_destroyed
game ended and plugin is destroyed - should be used only for cleanup

```cpp
void PLUGIN_destroyed();
```


---
## PLUGIN_stopped
game received stop command after this last PLUGIN_main is called use this to finalize data etc.

```cpp
void PLUGIN_stopped(bool aForce);
```

### Params
{: .no_toc }
- **aForce** - if game was stop by time or by command from application

---
## PLUGIN_serializeOtherCustomVariables
When engine is going to save or stream data serialize your own custom

```cpp
void PLUGIN_serializeOtherCustomVariables(rapidjson::Value& aValue, rapidjson::Document::AllocatorType& al, bool aIsFinal);
```

### Params
{: .no_toc }
- **aValue** - predefined rapid json Value as object
- **al** - rapid json allocator
- **aIsFinal** - if the last call before saving results

---
## PLUGIN_customVariableChanged
When custom variable is changed when game is active

```cpp
void PLUGIN_customVariableChanged(const std::string& aName);
```

### Params
{: .no_toc }
- **aName** - name of custom variable

---
## PLUGIN_customMessageFromVisualization
When web results sends some data

```cpp
void PLUGIN_customMessageFromVisualization(const rapidjson::Value& aValue);
```

### Params
{: .no_toc }
- **aDocument** json value
