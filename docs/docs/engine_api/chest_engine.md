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

- **return** - touch pressed state, 0 not pressed, 1 pressed

---
## ENGINE_getOptionsTouchEnabled
Get settings about touch sensor enabled

```cpp
uint8_t ENGINE_getOptionsTouchEnabled(void);
```

- **return** - options touch enabled state, 0 not enabled, 1 (other) enabled

---
## ENGINE_getLife
Get actual life

```cpp
uint16_t ENGINE_getLife(void);
```

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

- **return** - length of death in seconds

---
## ENGINE_getLengthStarting
Get time length of starting interval

```cpp
uint8_t ENGINE_getLengthStarting(void);
```

- **return** - length of starting interval in seconds

---
## ENGINE_getLengthRevival
Get time length of revival interval

```cpp
uint16_t ENGINE_getLengthRevival(void);
```

- **return** - length of revival interval in seconds

---
## ENGINE_getLengthGame
Get time length of game

```cpp
uint16_t ENGINE_getLengthGame(void);
```

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


---
## ENGINE_getDisplayTime
Get time shown at display (starting countdown, game time,...)

```cpp
uint16_t ENGINE_getDisplayTime(void);
```

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

- **return** - 0 - pressed, 1 - released

---
## ENGINE_getUserButtonState
Get the state of user button

```cpp
uint8_t ENGINE_getUserButtonState(void);
```

- **return** - 0 - pressed, 1 - released

---
## ENGINE_getSteps
Get the actual steps count

```cpp
uint16_t ENGINE_getSteps(void);
```

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


---
## ENGINE_playSoundFromSoundSet
Play selected sound from sound set table, specified by index

```cpp
void ENGINE_playSoundFromSoundSet(uint8_t aSoundSetIndex);
```

### Params
{: .no_toc }
- **aSoundSetIndex** - index of sound in sound set table, <0; 99> or strictly <0; sound_set_nmbr_of_sounds>

---
## ENGINE_controlDisplayFromPlugin
Enable control of display from plugin, disable default layout and info showing

```cpp
void ENGINE_controlDisplayFromPlugin(void);
```


---
## ENGINE_selectDisplayBuffer
Switch actual buffer for all drawing to selected one

```cpp
void ENGINE_selectDisplayBuffer(uint8_t aNumber);
```

### Params
{: .no_toc }
- **buffer_nmbr** - number of display buffer to be used, 1 or 2

---
## ENGINE_clearDisplayBuffer
Clear actual buffer

```cpp
void ENGINE_clearDisplayBuffer(void);
```


---
## ENGINE_drawBufferToDisplay
Draws buffer to display

```cpp
void ENGINE_drawBufferToDisplay(uint8_t aBufferType);
```

### Params
{: .no_toc }
- **BufferType** - select which buffer will be drawn to display, valid values are 0 for actual, 1 for buffer1 and 2 for buffer2

---
## ENGINE_drawBufferToDisplayTimeouted
Draws buffer to display and after timeout switch to other

```cpp
void ENGINE_drawBufferToDisplayTimeouted(uint8_t aBufferType, uint16_t aTimeout);
```

### Params
{: .no_toc }
- **BufferType** - select which buffer will be drawn to display, valid values are 0 for the other than actual, 1 for buffer1 and 2 for buffer2
- **Timeout** - the time in [ms] for how long the buffer will be displayed

---
## ENGINE_drawPixel
Draw pixel of specified color to coordinates [x,y]

```cpp
void ENGINE_drawPixel(uint8_t aX, uint8_t aY, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **color** - white = 0, black = 1

---
## ENGINE_drawLine
Draw line of specified color between coordinates [x0,y0] and [x1,y1]

```cpp
void ENGINE_drawLine(uint8_t aX0, uint8_t aY0, uint8_t aX1, uint8_t aY1, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **color** - white = 0, black = 1

---
## ENGINE_drawRectangle
Draw rectangle of specified color between coordinates [x0,y0] and [x1,y1]

```cpp
void ENGINE_drawRectangle(uint8_t aX0, uint8_t aY0, uint8_t aX1, uint8_t aY1, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **color** - white = 0, black = 1

---
## ENGINE_fillRectangle
Draw filled reclangle of specified color with selected width and height from point [x,y]

```cpp
void ENGINE_fillRectangle(uint8_t aX, uint8_t aY, uint8_t aWidth,
		uint8_t aHeight, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **width** - width of rectangle (x axis)
- **height** - height of rectangle (y axis)
- **color** - white = 0, black = 1

---
## ENGINE_drawCircle
Draw circle of specified color with center in coordinates [x,y] and radius r

```cpp
void ENGINE_drawCircle(uint8_t aX, uint8_t aY, uint8_t aR, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **R** - radius
- **color** - white = 0, black = 1

---
## ENGINE_fillCircle
Draw filled circle of specified color with selected radius from pivot [x,y]

```cpp
void ENGINE_fillCircle(uint8_t aX, uint8_t aY, uint8_t aRadius, uint8_t aColor);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate of pivot
- **Y** - vertical coordinate of pivot
- **Radius** - circle radius
- **color** - white = 0, black = 1

---
## ENGINE_drawChar
Draw single character from point [x,y] (upper left point)

```cpp
void ENGINE_drawChar(uint8_t aX, uint8_t aY, uint8_t aChar, uint8_t aSize);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **Char** - character to be drawn
- **Size** - size of font, 0 is small, 1 is big

---
## ENGINE_drawString
Draw string from point [x,y] (upper left point)

```cpp
void ENGINE_drawString(uint8_t aX, uint8_t aY, uint8_t* aString, uint8_t aSize);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **String** - text to be drawn
- **Size** - size of font, 0 is small, 1 is big

---
## ENGINE_drawInt
Draw integer number aligned with point [x,y]

```cpp
void ENGINE_drawInt(uint8_t aX, uint8_t aY, int32_t aValue, uint8_t aAlign,
		uint8_t aSize);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **Value** - number to be drawn
- **Align** - select align of number against point, left 'L', right 'R' and center 'C'
- **Size** - size of font, 0 is small, 1 is big

---
## ENGINE_drawBar
Draw bar from upper left point [x,y] with border according to width and height and percentage bar

```cpp
void ENGINE_drawBar(uint8_t aX, uint8_t aY, uint8_t aWidth, uint8_t aHeight,
		uint8_t aPercentage, uint8_t aOrientation);
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **width** - width of rectangle (x axis)
- **height** - height of rectangle (y axis)
- **Percentage** - size of bar
- **Orientation** - H for horizontal and V for vertical bar

---
## ENGINE_drawBitmap
Draw bitmap with [width,height] from upper left point [x,y], each row divided into whole bytes

```cpp
void ENGINE_drawBitmap(uint8_t aX, uint8_t aY, uint8_t aWidth, uint8_t aHeight,
		uint8_t* aBitmap );
```

### Params
{: .no_toc }
- **X** - horizontal coordinate
- **Y** - vertical coordinate
- **width** - width of bitmap (x axis)
- **height** - height of bitmap (y axis)
- **Bitmap** - pointer to uint8_t array with bitmap, each row starts with new byte

---
## ENGINE_invertDisplayBuffer
Inverts each bit in selected display buffer

```cpp
void ENGINE_invertDisplayBuffer(uint8_t aBufferType);
```

### Params
{: .no_toc }
- **BufferType** - select which buffer will be drawn to display, valid values are 0 for actual, 1 for buffer1 and 2 for buffer2

---
## ENGINE_getRank
Returns actual rank of player

```cpp
uint8_t ENGINE_getRank(void);
```

- **return** Rank

---
## ENGINE_getScore
Returns actual score of player

```cpp
int32_t ENGINE_getScore(void);
```

- **return** Score

---
## ENGINE_getCode
Returns code of player

```cpp
uint8_t ENGINE_getCode(void);
```

- **return** Code

---
## ENGINE_getPlayerName
Returns name of player selected by code

```cpp
uint8_t ENGINE_getPlayerName(uint8_t* apName, uint8_t aCode);
```

### Params
{: .no_toc }
- **Code** - code of player whose name will be returned
- **Name** - pointer to buffer, where the player name will be copied, at least 21 bytes
- **return** Length - returns length of Name

---
## ENGINE_setLaserAutoControl
Select if laser is automatically controlled by shooting or not

```cpp
void ENGINE_setLaserAutoControl(uint8_t aState);
```

### Params
{: .no_toc }
- **State** - new state of automatic laser control, 1 is enabled, 0 is disabled

---
## ENGINE_setLaserFlashing
Select if laser is continuously flashing

```cpp
void ENGINE_setLaserFlashing(uint8_t aState);
```

### Params
{: .no_toc }
- **State** - new state of laser flashing, 1 is enabled, 0 is disabled

---
## ENGINE_stopSound
Stops playing of sound, clear all sounds in sound buffer if channel1 selected

```cpp
void ENGINE_stopSound(uint8_t aChannel);
```

### Params
{: .no_toc }
- **Channel** - selects which channel is stopped. 1 = channel1 (sounds), 2 = channel2 (shoot), 0 = both channels

---
## ENGINE_clearSoundBuffer
Clears sound buffer. Actually played sound on ch1 is finished normally

```cpp
void ENGINE_clearSoundBuffer(void);
```


---
## ENGINE_deleteSoundFromBuffer
delete all instances of selected sound from sound buffer, no influence if already playing

```cpp
void ENGINE_deleteSoundFromBuffer(uint32_t aSoundID, uint8_t aSoundFromSoundSet);
```

### Params
{: .no_toc }
- **SoundID** - ID of sound selected to be deleted (or SoundSetID)
- **SoundFromSoundSet** - specifies if selected sound is from sound set, 1 = sound from soundset, 0 = only soundID

---
## ENGINE_playSoundImmediately
play selected sound immediately (add it to front of sound buffer)

```cpp
void ENGINE_playSoundImmediately(uint32_t aSoundID, uint8_t aSoundFromSoundSet, uint8_t aStopActualSound);
```

### Params
{: .no_toc }
- **SoundID** - ID of sound selected to be deleted (or SoundSetID)
- **SoundFromSoundSet** - specifies if selected sound is from sound set, 1 = sound from soundset, 0 = only soundID
- **StopActualSound** - specifies if demand to stop actually playing sound (1) or not (0). If 1, actual sound is stopped and selected is played immediately, if 0, selected sound is played after actual ends

---
## ENGINE_generateRandomNumber
generate random number from 0 to selected max value

```cpp
uint32_t ENGINE_generateRandomNumber(uint32_t aMaxValue);
```

### Params
{: .no_toc }
- **MaxValue** - upper limit of interval for generating random number
- **return** generated random number

---
## ENGINE_setStroboscopeMode
set different stroboscope mode, recommended to use only in Init function

```cpp
void ENGINE_setStroboscopeMode(uint8_t aMode);
```

### Params
{: .no_toc }
- **Mode** - index of mode, 0 is basic lightning for 1s, 1 is 3 fast blinks, 2 is 5 fast blinks
