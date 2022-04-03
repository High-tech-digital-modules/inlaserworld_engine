---
layout: default
title: Chest plugin event handlers
parent: Engine API
---

# Chest unit API plugin
{: .no_toc }
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
## PLUGIN_mainLoop
part in while loop in main
```c
void PLUGIN_mainLoop(void);
```
### Params
{: .no_toc }

---
## PLUGIN_timer10ms
part in timer interrupt with periode 10 ms
```c
void PLUGIN_timer10ms(void);
```
### Params
{: .no_toc }

---
## PLUGIN_timer1s
part in timer interrupt with period 1 s
```c
void PLUGIN_timer1s(uint16_t aTimeDisplay);
```
### Params
{: .no_toc }

---
## PLUGIN_pressedTrigger
part in external interrupt for trigger press
```c
void PLUGIN_pressedTrigger(void);
```
### Params
{: .no_toc }

---
## PLUGIN_releasedTrigger
part in external interrupt for trigger release
```c
void PLUGIN_releasedTrigger(void);
```
### Params
{: .no_toc }

---
## PLUGIN_pressedUserButton
part in external interrupt for user button press
```c
void PLUGIN_pressedUserButton(void);
```
### Params
{: .no_toc }

---
## PLUGIN_releasedUserButton
part in external interrupt for user button release
```c
void PLUGIN_releasedUserButton(void);
```
### Params
{: .no_toc }

---
## PLUGIN_hitByEnemy
part in while loop in main after detecting hit from slave module
```c
void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
  uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth);
```
### Params
{: .no_toc }

---
## PLUGIN_hitByTeam
part in while loop in main after detecting hit from slave module
```c
void PLUGIN_hitByTeam(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
  uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth);
```
### Params
{: .no_toc }

---
## PLUGIN_setModulesState
part in while loop in main for selecting color and behavior of slave modules
```c
void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
  uint8_t aHitCode, uint8_t aHealth, volatile uint8_t apModulesState,
  volatile uint8_t apModulesDim1, volatile uint8_t apModulesDim2,
  volatile colors_t apModulesColor1, volatile colors_t apModulesColor2);
```
### Params
{: .no_toc }

---
## PLUGIN_changedGameStateToAlive
part in while loop in main triggered by game_state change
```c
void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast);
```
### Params
{: .no_toc }

---
## PLUGIN_changedGameStateToDead
part in while loop in main triggered by game_state change
```c
void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast);
```
### Params
{: .no_toc }

---
## PLUGIN_changedGameStateToRevival
part in while loop in main triggered by game_state change
```c
void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast);
```
### Params
{: .no_toc }

---
## PLUGIN_changedGameStateToStarting
part in while loop in main triggered by game_state change
```c
void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast);
```
### Params
{: .no_toc }

---
## PLUGIN_changedGameStateToEnding
part in while loop in main triggered by game_state change
```c
void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast);
```
### Params
{: .no_toc }

---
## PLUGIN_processCustomMessage
part in data_process for processing custom message
```c
void PLUGIN_processCustomMessage(uint8_t apData, uint16_t aLength,
  uint8_t aDevice);
```
### Params
{: .no_toc }

---
## PLUGIN_customInit
part of PLUGIN_init, for users part of initialization, for example global vars for timers (length_death,...)
```c
void PLUGIN_customInit(volatile colors_t apModulesColor1,
  volatile colors_t apModulesColor2, volatile uint8_t apModulesDim1,
  volatile uint8_t apModulesDim2, uint8_t apModulesVibrationStrength,
  volatile uint8_t apModulesState);
```
### Params
{: .no_toc }
