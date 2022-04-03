---
layout: default
title: Chest engine functions
parent: Engine API
---

# Chest unit API engine
{: .no_toc }
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
```c
uint8_t ENGINE_getGameState(void);
```
### Params
{: .no_toc }
---
## ENGINE_setGameState
```c
void ENGINE_setGameState(uint8_t aGameState);
```
### Params
{: .no_toc }
---
## ENGINE_getTouchPressed
```c
uint8_t ENGINE_getTouchPressed(void);
```
### Params
{: .no_toc }
---
## ENGINE_getOptionsTouchEnabled
```c
uint8_t ENGINE_getOptionsTouchEnabled(void);
```
### Params
{: .no_toc }
---
## ENGINE_getLife
```c
uint16_t ENGINE_getLife(void);
```
### Params
{: .no_toc }
---
## ENGINE_setLife
```c
void ENGINE_setLife(uint16_t aLife);
```
### Params
{: .no_toc }
---
## ENGINE_decrementLife
```c
void ENGINE_decrementLife(uint16_t aLifeDecrement);
```
### Params
{: .no_toc }
---
## ENGINE_getHealth
```c
uint8_t ENGINE_getHealth(void);
```
### Params
{: .no_toc }
---
## ENGINE_setHealth
```c
void ENGINE_setHealth(uint8_t aHealth);
```
### Params
{: .no_toc }
---
## ENGINE_decrementHealth
```c
void ENGINE_decrementHealth(uint8_t aHealthDecrement);
```
### Params
{: .no_toc }
---
## ENGINE_getAmmo
```c
uint16_t ENGINE_getAmmo(void);
```
### Params
{: .no_toc }
---
## ENGINE_setAmmo
```c
void ENGINE_setAmmo(uint16_t aAmmo);
```
### Params
{: .no_toc }
---
## ENGINE_decrementAmmo
```c
void ENGINE_decrementAmmo(uint16_t aAmmoDecrement);
```
### Params
{: .no_toc }
---
## ENGINE_getLengthDeath
```c
uint16_t ENGINE_getLengthDeath(void);
```
### Params
{: .no_toc }
---
## ENGINE_getLengthStarting
```c
uint8_t ENGINE_getLengthStarting(void);
```
### Params
{: .no_toc }
---
## ENGINE_getLengthRevival
```c
uint16_t ENGINE_getLengthRevival(void);
```
### Params
{: .no_toc }
---
## ENGINE_getLengthGame
```c
uint16_t ENGINE_getLengthGame(void);
```
### Params
{: .no_toc }
---
## ENGINE_makeShoot
```c
void ENGINE_makeShoot(uint8_t aShotStrength, uint8_t aShotCustomInfo);
```
### Params
{: .no_toc }
---
## ENGINE_playShoot
```c
void ENGINE_playShoot(uint8_t aShotType);
```
### Params
{: .no_toc }
---
## ENGINE_addTableHit
```c
void ENGINE_addTableHit(uint8_t aHitCode, uint8_t aHitFlag);
```
### Params
{: .no_toc }
---
## ENGINE_addTableKill
```c
void ENGINE_addTableKill(uint8_t aHitCode);
```
### Params
{: .no_toc }
---
## ENGINE_playSound
```c
void ENGINE_playSound(uint8_t aSoundType);
```
### Params
{: .no_toc }
---
## ENGINE_processDeath
```c
void ENGINE_processDeath(uint8_t aHitCode, uint8_t aHitFlag);
```
### Params
{: .no_toc }
---
## ENGINE_processHit
```c
void ENGINE_processHit(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength);
```
### Params
{: .no_toc }
---
## ENGINE_setModuleState
```c
void ENGINE_setModuleState(uint16_t aSlaveIndex, uint8_t aLed1, uint8_t aLed2,
uint8_t aVibration);
```
### Params
{: .no_toc }
---
## ENGINE_setAllModulesState
```c
void ENGINE_setAllModulesState(uint8_t aLed1, uint8_t aLed2, uint8_t aVibration);
```
### Params
{: .no_toc }
---
## ENGINE_setModuleDim
```c
void ENGINE_setModuleDim(uint16_t aSlaveIndex, uint8_t aDim1, uint8_t aDim2);
```
### Params
{: .no_toc }
---
## ENGINE_setAllModulesDim
```c
void ENGINE_setAllModulesDim(uint8_t aDim1, uint8_t aDim2);
```
### Params
{: .no_toc }
---
## ENGINE_setVibrationAccordingHitCode
```c
void ENGINE_setVibrationAccordingHitCode(uint8_t aHitCode);
```
### Params
{: .no_toc }
---
## ENGINE_setColorEffectFade
```c
void ENGINE_setColorEffectFade(uint8_t aValue);
```
### Params
{: .no_toc }
---
## ENGINE_getLightState
```c
uint8_t ENGINE_getLightState(void);
```
### Params
{: .no_toc }
---
## ENGINE_setLightState
```c
void ENGINE_setLightState(uint8_t aLightState);
```
### Params
{: .no_toc }
---
## ENGINE_toggleLightState
```c
void ENGINE_toggleLightState(void);
```
### Params
{: .no_toc }
---
## ENGINE_getDisplayTime
```c
uint16_t ENGINE_getDisplayTime(void);
```
### Params
{: .no_toc }
---
## ENGINE_setDisplayTime
```c
void ENGINE_setDisplayTime(uint16_t aDisplayTime);
```
### Params
{: .no_toc }
---
## ENGINE_decrementDisplayTime
```c
void ENGINE_decrementDisplayTime(uint16_t aDisplayTimeDecrement);
```
### Params
{: .no_toc }
---
## ENGINE_getShotStrength
```c
uint8_t ENGINE_getShotStrength(void);
```
### Params
{: .no_toc }
---
## ENGINE_setShotStrength
```c
void ENGINE_setShotStrength(uint8_t aShotStrength);
```
### Params
{: .no_toc }
---
## ENGINE_getShotRange
```c
uint8_t ENGINE_getShotRange(void);
```
### Params
{: .no_toc }
---
## ENGINE_setShotRange
```c
void ENGINE_setShotRange(uint8_t aShotRange);
```
### Params
{: .no_toc }
---
## ENGINE_setPeriodicInfoLength
```c

void ENGINE_setPeriodicInfoLength(uint8_t aPeriodicInfoLength);
```
### Params
{: .no_toc }
---
## ENGINE_setPeriodicInfo
```c
void ENGINE_setPeriodicInfo(uint8_t* aPeriodicInfo);
```
### Params
{: .no_toc }
---
## ENGINE_setPeriodicInfoByte
```c
void ENGINE_setPeriodicInfoByte(uint8_t aPeriodicInfo,
uint8_t aPeriodicInfoIndex);
```
### Params
{: .no_toc }
---
## ENGINE_sendCustomMessage
```c

uint8_t ENGINE_sendCustomMessage(uint8_t* apMessage, uint8_t aMessageLength,
uint8_t aTarget);
```
### Params
{: .no_toc }
---
## ENGINE_getCustomMessageState
```c
uint8_t ENGINE_getCustomMessageState(void);
```
### Params
{: .no_toc }
---
## ENGINE_setModuleColor
```c
void ENGINE_setModuleColor(uint16_t aSlaveIndex, uint8_t aColorType,
colors_t aColor);
```
### Params
{: .no_toc }
---
## ENGINE_setAllModulesColor
```c
void ENGINE_setAllModulesColor(uint8_t aColorType, colors_t aColor);
```
### Params
{: .no_toc }
---
## ENGINE_getModuleColors
```c
void ENGINE_getModuleColors(uint16_t aSlaveIndex, colors_t* apColor1,
colors_t* apColor2);
```
### Params
{: .no_toc }
---
## ENGINE_getTriggerState
```c
uint8_t ENGINE_getTriggerState(void);
```
### Params
{: .no_toc }
---
## ENGINE_getUserButtonState
```c
uint8_t ENGINE_getUserButtonState(void);
```
### Params
{: .no_toc }
---
## ENGINE_getSteps
```c
uint16_t ENGINE_getSteps(void);
```
### Params
{: .no_toc }
