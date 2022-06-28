---
layout: default
title: Chest engine functions
parent: Engine API
---

# Chest unit API engine
{: .no_toc}
This is set of function that can be called from plugin to do something with chest.

<details markdown="block">
  <summary>
    Table of contents
  </summary>
{: .text-delta }
1. TOC
{:toc}
</details>

---
## ENGINE_getGameState
Get actual game state

```cpp
uint8_t ENGINE_getGameState(void);
```

### Params
{: .no_toc }
- **return** - actual game_state

---
## ENGINE_setGameState
Write new value to game_state

```cpp
void ENGINE_setGameState(uint8_t aGameState);
```

### Params
{: .no_toc }
- **aGameState** - new game state

---
## ENGINE_getTouchPressed
Get info about touch sensor

```cpp
uint8_t ENGINE_getTouchPressed(void);
```

### Params
{: .no_toc }
- **return** - touch pressed state, 0 not pressed, 1 pressed

---
## ENGINE_getOptionsTouchEnabled
Get settings about touch sensor enabled

```cpp
uint8_t ENGINE_getOptionsTouchEnabled(void);
```

### Params
{: .no_toc }
- **return** - options touch enabled state, 0 not enabled, 1 (other) enabled

---
## ENGINE_getLife
Get actual life

```cpp
uint16_t ENGINE_getLife(void);
```

### Params
{: .no_toc }
- **return** - actual life

---
## ENGINE_setLife
Write new value of life

```cpp
void ENGINE_setLife(uint16_t aLife);
```

### Params
{: .no_toc }
- **aLife** - new life value

---
## ENGINE_decrementLife
Decrement actual life value by selected value

```cpp
void ENGINE_decrementLife(uint16_t aLifeDecrement);
```

### Params
{: .no_toc }
- **aLifeDecrement** - selected life decrement

---
## ENGINE_getHealth
Get actual health

```cpp
uint8_t ENGINE_getHealth(void);
```

### Params
{: .no_toc }
- **return** - actual health

---
## ENGINE_setHealth
Write new value of health

```cpp
void ENGINE_setHealth(uint8_t aHealth);
```

### Params
{: .no_toc }
- **aHealth** - new health value

---
## ENGINE_decrementHealth
Decrement actual health value by selected value

```cpp
void ENGINE_decrementHealth(uint8_t aHealthDecrement);
```

### Params
{: .no_toc }
- **aHealthDecrement** - selected health decrement

---
## ENGINE_getAmmo
Get actual ammo

```cpp
uint16_t ENGINE_getAmmo(void);
```

### Params
{: .no_toc }
- **return** - actual ammo

---
## ENGINE_setAmmo
Write new value of ammo

```cpp
void ENGINE_setAmmo(uint16_t aAmmo);
```

### Params
{: .no_toc }
- **aAmmo** - new ammo value

---
## ENGINE_decrementAmmo
Decrement actual ammo value by selected value

```cpp
void ENGINE_decrementAmmo(uint16_t aAmmoDecrement);
```

### Params
{: .no_toc }
- **aAmmoDecrement** - selected ammo decrement

---
## ENGINE_getLengthDeath
Get time length of death

```cpp
uint16_t ENGINE_getLengthDeath(void);
```

### Params
{: .no_toc }
- **return** - length of death in seconds

---
## ENGINE_getLengthStarting
Get time length of starting interval

```cpp
uint8_t ENGINE_getLengthStarting(void);
```

### Params
{: .no_toc }
- **return** - length of starting interval in seconds

---
## ENGINE_getLengthRevival
Get time length of revival interval

```cpp
uint16_t ENGINE_getLengthRevival(void);
```

### Params
{: .no_toc }
- **return** - length of revival interval in seconds

---
## ENGINE_getLengthGame
Get time length of game

```cpp
uint16_t ENGINE_getLengthGame(void);
```

### Params
{: .no_toc }
- **return** - length of game in seconds

---
## ENGINE_makeShoot
Perform shoot process, without decreasing ammo and playing sound

```cpp
void ENGINE_makeShoot(uint8_t aShotStrength, uint8_t aShotCustomInfo);
```

### Params
{: .no_toc }
- **aShotStrength** - shot strength send in shot message, <0; 15>, 0xFF for default game shot strength
- **aShotCustomInfo** - custom info send in shot message, <0; 15>

---
## ENGINE_playShoot
Play shot sound

```cpp
void ENGINE_playShoot(uint8_t aShotType);
```

### Params
{: .no_toc }
- **aShotType** - select type of shot sound, 0 - basic shot sound, 1 - "no shoot" sound

---
## ENGINE_addTableHit
Add hit to specified table row

```cpp
void ENGINE_addTableHit(uint8_t aHitCode, uint8_t aHitFlag);
```

### Params
{: .no_toc }
- **aHitCode** - select table row, from which player hit was received, 0 is reserved
- **aHitFlag** - specify which module was hit,

		 0 reserved
		 1 front_1
		 2 front_2
		 3 left_1
		 4 left_2
		 5 right_1
		 6 right_2
		 7 back_1
		 8 back_2
		 9 weapon

---
## ENGINE_addTableKill
Add kill to specified table row

```cpp
void ENGINE_addTableKill(uint8_t aHitCode);
```

### Params
{: .no_toc }
- **aHitCode** - select table row, from which player kill was received, 0 is reserved

---
## ENGINE_playSound
Play selected sound, specified by databaseID

```cpp
void ENGINE_playSound(uint32_t aSoundID);
```

### Params
{: .no_toc }
- **aSoundID** - database ID of sound, which has to be played

---
## ENGINE_processDeath
Process death, add info to table, decrement life, show info at display, change game state

```cpp
void ENGINE_processDeath(uint8_t aHitCode, uint8_t aHitFlag);
```

### Params
{: .no_toc }
- **aHitCode** - select table row, from which player hit was received, 0 is reserved
- **aHitFlag** - specify which module was hit,

		 0 reserved
		 1 front_1
		 2 front_2
		 3 left_1
		 4 left_2
		 5 right_1
		 6 right_2
		 7 back_1
		 8 back_2
		 9 weapon

---
## ENGINE_processHit
Process hit, add info to table, decrement health, show at display, change game state

```cpp
void ENGINE_processHit(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength);
```

### Params
{: .no_toc }
- **aHitCode** - select table row, from which player hit was received, 0 is reserved
- **aHitFlag** - specify which module was hit,

		 0 reserved
		 1 front_1
		 2 front_2
		 3 left_1
		 4 left_2
		 5 right_1
		 6 right_2
		 7 back_1
		 8 back_2
		 9 weapon
- **aHitStrength** - strength of hit, how many healts to decrement, 0 means default strength 100

---
## ENGINE_setModuleState
Set specified settings for Led1, Led2 and vibration to slave with selected index

```cpp
void ENGINE_setModuleState(uint16_t aSlaveIndex, uint8_t aLed1, uint8_t aLed2,
		uint8_t aVibration);
```

### Params
{: .no_toc }
- **aSlaveIndex** - index of selected slave module, this parameter can be from 0 to NUM_OF_SLAVES
- **aLed1** - behaviour of Led1, this parameter can be

		 0 led circuit turned off
		 1 led circuit turned on to color1
		 2 led circuit turned on to color2
		 3 led circuit turned on to stroboscope
- **aLed2** - behaviour of Led2, this parameter can be

		 0 led circuit turned off
		 1 led circuit turned on to color1
		 2 led circuit turned on to color2
		 3 led circuit turned on to stroboscope
- **aVibration** - behaviour of vibration motor, this parameter can be

		 0 vibration motor disabled
		 1 vibration motor enabled

---
## ENGINE_setAllModulesState
Set specified settings for Led1, Led2 and vibration to all slave modules

```cpp
void ENGINE_setAllModulesState(uint8_t aLed1, uint8_t aLed2, uint8_t aVibration);
```

### Params
{: .no_toc }
- **aLed1** - behaviour of Led1, this parameter can be

		 0 led circuit turned off
		 1 led circuit turned on to color1
		 2 led circuit turned on to color2
		 3 led circuit turned on to stroboscope
- **aLed2** - behaviour of Led2, this parameter can be

		 0 led circuit turned off
		 1 led circuit turned on to color1
		 2 led circuit turned on to color2
		 3 led circuit turned on to stroboscope
- **aVibration** - behaviour of vibration motor, this parameter can be

		 0 vibration motor disabled
		 1 vibration motor enabled

---
## ENGINE_setModuleDim
Set dim settings for Led1 and Led2 to slave with selected index

```cpp
void ENGINE_setModuleDim(uint16_t aSlaveIndex, uint8_t aDim1, uint8_t aDim2);
```

### Params
{: .no_toc }
- **aSlaveIndex** - index of selected slave module, this parameter can be from 0 to NUM_OF_SLAVES
- **aDim1** - dim of Led1, this parameter can be between:

		 0 led fully turned off
		 100 led fully turned on
- **aDim2** - dim of Led2, this parameter can be between:

		 0 led fully turned off
		 100 led fully turned on

---
## ENGINE_setAllModulesDim
Set dim settings for Led1 and Led2 to all slave modules

```cpp
void ENGINE_setAllModulesDim(uint8_t aDim1, uint8_t aDim2);
```

### Params
{: .no_toc }
- **aDim1** - dim of Led1, this parameter can be between:

		 0 led fully turned off
		 100 led fully turned on
- **aDim2** - dim of Led2, this parameter can be between:

		 0 led fully turned off
		 100 led fully turned on

---
## ENGINE_setVibrationAccordingHitFlag
Set vibration according to hit code, vibrate with both shoulder modules no matter which was hitted

```cpp
void ENGINE_setVibrationAccordingHitFlag(uint8_t aHitFlag);
```

### Params
{: .no_toc }
- **aHitFlag** - specify which module was hit,

		 0 reserved
		 1 front_1
		 2 front_2
		 3 left_1
		 4 left_2
		 5 right_1
		 6 right_2
		 7 back_1
		 8 back_2
		 9 weapon

---
## ENGINE_setColorEffectFade
Set color and dim of modules according to aValue parameter, dimming from chest bottom to top

```cpp
void ENGINE_setColorEffectFade(uint8_t aValue);
```

### Params
{: .no_toc }
- **aValue** - specify how much is chest turned on,

		 0 fully off
		 100 fully on
		 255 set according to Health

---
## ENGINE_getLightState
Get state of weapon light

```cpp
uint8_t ENGINE_getLightState(void);
```

### Params
{: .no_toc }
- **return** - actual light state, 0 = off, 1 = on

---
## ENGINE_setLightState
Select new state of weapon light

```cpp
void ENGINE_setLightState(uint8_t aLightState);
```

### Params
{: .no_toc }
- **aLightState** - new state of light, 0 = off, 1 = on

---
## ENGINE_toggleLightState
Toggle state of weapon light

```cpp
void ENGINE_toggleLightState(void);
```

### Params
{: .no_toc }

---
## ENGINE_getDisplayTime
Get time shown at display (starting countdown, game time,...)

```cpp
uint16_t ENGINE_getDisplayTime(void);
```

### Params
{: .no_toc }
- **return** - time from dislay in seconds

---
## ENGINE_setDisplayTime
Write new value of time to display

```cpp
void ENGINE_setDisplayTime(uint16_t aDisplayTime);
```

### Params
{: .no_toc }
- **aDisplayTime** - new time value to be shown

---
## ENGINE_decrementDisplayTime
Decrement actual displayed time value by selected value

```cpp
void ENGINE_decrementDisplayTime(uint16_t aDisplayTimeDecrement);
```

### Params
{: .no_toc }
- **aDisplayTimeDecrement** - selected time decrement

---
## ENGINE_getShotStrength
Get selected shot strength (send by shot message)

```cpp
uint8_t ENGINE_getShotStrength(void);
```

### Params
{: .no_toc }
- **return** - shot strength in interval <SHOT_MULTIPLIER-100> with step size SHOT_MULTIPLIER

---
## ENGINE_setShotStrength
Write new shot strength value (send by shot message)

```cpp
void ENGINE_setShotStrength(uint8_t aShotStrength);
```

### Params
{: .no_toc }
- **aShotStrength** - new shot strength value, 1-100

---
## ENGINE_getShotRange
Get shot range value (physical current source settings)

```cpp
uint8_t ENGINE_getShotRange(void);
```

### Params
{: .no_toc }
- **return** - shot range value (0-100), 0 is smallest range

---
## ENGINE_setShotRange
Set new value of shot range (physical current source settings)

```cpp
void ENGINE_setShotRange(uint8_t aShotRange);
```

### Params
{: .no_toc }
- **aShotRange** - new shot range value (0-100), 0 is smallest range

---
## ENGINE_setPeriodicInfoLength
Write how many bytes are added to standard periodic B message (send each second)

```cpp
void ENGINE_setPeriodicInfoLength(uint8_t aPeriodicInfoLength);
```

### Params
{: .no_toc }
- **aPeriodicInfoLength** - number of bytes

---
## ENGINE_setPeriodicInfo
Write info into array connected with B message, number of bytes is set by ENGINE_setPeriodicInfoLength

```cpp
void ENGINE_setPeriodicInfo(uint8_t* aPeriodicInfo);
```

### Params
{: .no_toc }
- **aPeriodicInfo** - pointer to array with info

---
## ENGINE_setPeriodicInfoByte
Write one byte of info into array connected with B message according to specified index

```cpp
void ENGINE_setPeriodicInfoByte(uint8_t aPeriodicInfo,
		uint8_t aPeriodicInfoIndex);
```

### Params
{: .no_toc }
- **aPeriodicInfo** - byte with info
- **aPeriodicInfoIndex** - index of info byte

---
## ENGINE_sendCustomMessage
Prepare custom message to be send to specified target, sending in main in several miliseconds

```cpp
uint8_t ENGINE_sendCustomMessage(uint8_t* apMessage, uint8_t aMessageLength,
		uint8_t aTarget);
```

### Params
{: .no_toc }
- **apMessage** - pointer to array with message
- **aMessageLength** - length of message, number of valid bytes in apMessage array
- **aTarget** - specified device which should obtain message, number of chest corresponding to chest code (row in table), 0 means coordinator
- **return** - status of operation:

		 0x00 ENGINE_CUSTOM_MSG_SUCCES
		 0x01 ENGINE_CUSTOM_MSG_LENGTH_ERROR - message too long
		 0x02 ENGINE_CUSTOM_MSG_TARGET_ERROR - aTarget higher than number of players
		 0x03 ENGINE_CUSTOM_MSG_PENDING_MSG - previous message not sended yet

---
## ENGINE_getCustomMessageState
Get the state of sending custom message

```cpp
uint8_t ENGINE_getCustomMessageState(void);
```

### Params
{: .no_toc }
- **return** - state of message sending

		 0x00 ENGINE_CUSTOM_MSG_STATE_READY
		 0x01 ENGINE_CUSTOM_MSG_STATE_SENDING
		 0x02 ENGINE_CUSTOM_MSG_STATE_SENT
		 0x03 ENGINE_CUSTOM_MSG_STATE_NOT_SENT

---
## ENGINE_setModuleColor
Set new color of specified slave module

```cpp
void ENGINE_setModuleColor(uint16_t aSlaveIndex, uint8_t aColorType,
		colors_t aColor);
```

### Params
{: .no_toc }
- **aSlaveIndex** - index of selected slave module, this parameter can be from 0 to NUM_OF_SLAVES
- **aColorType** - select basic or special color (color 1 or 2), this parameter can be:

		 1 basic color (color 1)
		 2 special color (color 2)
- **aColor** - selected color code, structure with items red, green and blue, 8 bit each

---
## ENGINE_setAllModulesColor
Set new color of all slave modules

```cpp
void ENGINE_setAllModulesColor(uint8_t aColorType, colors_t aColor);
```

### Params
{: .no_toc }
- **aColorType** - select basic or special color (color 1 or 2), this parameter can be:

		 1 basic color (color 1)
		 2 special color (color 2)
- **aColor** - selected color code, structure with items red, green and blue, 8 bit each

---
## ENGINE_getModuleColors
Get basic and special color (color1 and color2) of module with selected index

```cpp
void ENGINE_getModuleColors(uint16_t aSlaveIndex, colors_t* apColor1,
		colors_t* apColor2);
```

### Params
{: .no_toc }
- **aSlaveIndex** - index of selected slave module, this parameter can be from 0 to NUM_OF_SLAVES
- **apColor1** - pointer to color structure with items red, green and blue, 8 bit each
- **apColor2** - pointer to color structure with items red, green and blue, 8 bit each

---
## ENGINE_getTriggerState
Get the state of trigger

```cpp
uint8_t ENGINE_getTriggerState(void);
```

### Params
{: .no_toc }
- **return** - 0 - pressed, 1 - released

---
## ENGINE_getUserButtonState
Get the state of user button

```cpp
uint8_t ENGINE_getUserButtonState(void);
```

### Params
{: .no_toc }
- **return** - 0 - pressed, 1 - released

---
## ENGINE_getSteps
Get the actual steps count

```cpp
uint16_t ENGINE_getSteps(void);
```

### Params
{: .no_toc }
- **return** - number of measured steps

---
## ENGINE_loadShot
Load specified sound from SD card to selected RAM buffer

```cpp
uint8_t ENGINE_loadShot(uint8_t aShotType, uint32_t aSoundID);
```

### Params
{: .no_toc }
- **aShotType** - specify RAM buffer

		 0 - sound for shot, 1s length
		 1 - sound for no shot, 0.5s length
- **aSoundID** - ID of sound to be found on SD card
- **return** - 0 - loading failed, 1 - load succesfull

---
## ENGINE_makeShootContinuousStart
Start continuous shooting (sending IR message)

```cpp
void ENGINE_makeShootContinuousStart(uint8_t aShotStrength,
		uint8_t aShotCustomInfo, uint8_t aDecreaseAmmoEnable, uint8_t aShotType,
		uint16_t aSoundRepeatLength);
```

### Params
{: .no_toc }
- **aShotStrength** - shot strength send in shot message, <0; 15>, 0xFF for default game shot strength
- **aShotCustomInfo** - custom info send in shot message, <0; 15>
- **aDecreaseAmmoEnable** - flag for enabling or disabling decreasing of ammo
- **aShotType** - select which shot buffer to use

		 0 - shot buffer
		 1 - no shot buffer
- **aSoundRepeatLength** - length in milliseconds for setting sound playing period. If 0 or bigger than sound length, the original sound length is used

---
## ENGINE_makeShootContinuousStop
Stop continuous shooting (sending shot message)

```cpp
void ENGINE_makeShootContinuousStop(void);
```

### Params
{: .no_toc }

---
## ENGINE_playSoundFromSoundSet
Play selected sound from sound set table, specified by index

```cpp
void ENGINE_playSoundFromSoundSet(uint8_t aSoundSetIndex);
```

### Params
{: .no_toc }
- **aSoundSetIndex** - index of sound in sound set table, <0; 99> or strictly <0; sound_set_nmbr_of_sounds>
