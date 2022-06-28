---
layout: default
title: Chest plugin event handlers
parent: Engine API
---

# Chest unit API plugin
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
## PLUGIN_mainLoop
Part in while loop in main

```cpp
void PLUGIN_mainLoop(void);
```

### Params
{: .no_toc }

---
## PLUGIN_timer10ms
Part in timer interrupt with periode 10 milliseconds

```cpp
void PLUGIN_timer10ms(void);
```

### Params
{: .no_toc }

---
## PLUGIN_timer1s
Part in timer interrupt with period 1 second, by using this the time countdown is disabled (also switching between game states and drawing time at display)

```cpp
void PLUGIN_timer1s(uint16_t aTimeDisplay);
```

### Params
{: .no_toc }
- **aTimeDisplay** - time in seconds which should be displayed (starting countdown or game time)

---
## PLUGIN_pressedTrigger
Part in external interrupt for trigger press

```cpp
void PLUGIN_pressedTrigger(void);
```

### Params
{: .no_toc }

---
## PLUGIN_releasedTrigger
Part in external interrupt for trigger release

```cpp
void PLUGIN_releasedTrigger(void);
```

### Params
{: .no_toc }

---
## PLUGIN_pressedUserButton
Part in external interrupt for user button press

```cpp
void PLUGIN_pressedUserButton(void);
```

### Params
{: .no_toc }

---
## PLUGIN_releasedUserButton
Part in external interrupt for user button release

```cpp
void PLUGIN_releasedUserButton(void);
```

### Params
{: .no_toc }

---
## PLUGIN_hitByEnemy
Part in while loop in main after detecting hit by enemy from slave module

```cpp
void PLUGIN_hitByEnemy(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
		uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth);
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
- **aHitStrength** - strength of received hit (received from shot message), <0; 100>
- **aHitCustomInfo** - custom info received in shot message, <0; 15>
- **aLife** - actual life value
- **aHealth** - actual health value

---
## PLUGIN_hitByTeam
Part in while loop in main after detecting hit by team from slave module

```cpp
void PLUGIN_hitByTeam(uint8_t aHitCode, uint8_t aHitFlag, uint8_t aHitStrength,
		uint8_t aHitCustomInfo, uint16_t aLife, uint8_t aHealth);
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
- **aHitStrength** - strength of received hit (received from shot message), <0; 100>
- **aHitCustomInfo** - custom info received in shot message, <0; 15>
- **aLife** - actual life value
- **aHealth** - actual health value

---
## PLUGIN_setModulesState
Part in while loop in main for selecting color and behavior of slave modules, triggered periodically every 20 milliseconds. Arrays contain actual values (apModulesState is send each periode to slave modules, the rest only vhen changed)

```cpp
void PLUGIN_setModulesState(uint8_t aState, uint8_t aGameState,
		uint8_t aHitFlag, uint8_t aHealth, volatile uint8_t* apModulesState,
		volatile uint8_t* apModulesDim1, volatile uint8_t* apModulesDim2,
		volatile colors_t* apModulesColor1, volatile colors_t* apModulesColor2);
```

### Params
{: .no_toc }
- **aState** - actial global state of chest, allowed values in plugin are

		 2 state_prepared - chest initialized for game, waiting to start
		 3 state_game - chest in game
		 4 state_ending - after game ended
- **aGameState** - actual state of game

		 0 game_state_ending - the end of game
		 1 game_state_alive - ingame playing
		 2 game_state_dead - after hit by another player, death
		 3 game_state_starting - game is starting, after state changed from prepared to game
		 4 game_state_revival - change from dead to alive
		 5 game_state_none - before game
- **aHitFlag** - specify which module was hit,

		 0 no hit received
		 1 front_1
		 2 front_2
		 3 left_1
		 4 left_2
		 5 right_1
		 6 right_2
		 7 back_1
		 8 back_2
		 9 weapon
- **aHealth** - actual health value
- **apModulesState** - pointer to array[NUM_OF_SLAVES] with state for each slave module, bits structure 0b000VBBAA

		 V - vibration flag, 1 means activate vibration for short time periode
		 BB - state of led2 circuit
		 AA - state of led1 circuit
		 0 turn off
		 1 basic color (color 1)
		 2 special color (color 2)
		 3 stroboscope - activate white blink
- **apModulesDim1** - pointer to array[NUM_OF_SLAVES] with dim value of led1 circuit for each slave module, <0; 100>, 0 - leds not lighting, 100 - full brightness
- **apModulesDim2** - pointer to array[NUM_OF_SLAVES] with dim value of led2 circuit for each slave module, <0; 100>, 0 - leds not lighting, 100 - full brightness
- **apModulesColor1** - pointer to array[NUM_OF_SLAVES] with basic color (color 1) structure (red, green, blue; each 8 bit) for each slave module
- **apModulesColor2** - pointer to array[NUM_OF_SLAVES] with special color (color 2) structure (red, green, blue; each 8 bit) for each slave module

---
## PLUGIN_changedGameStateToAlive
Part in while loop in main triggered by game_state change to Alive (normal playing state)

```cpp
void PLUGIN_changedGameStateToAlive(uint8_t aGameStateLast);
```

### Params
{: .no_toc }
- **aGameStateLast** - last game state

---
## PLUGIN_changedGameStateToDead
Part in while loop in main triggered by game_state change to Death (basically after loosing life)

```cpp
void PLUGIN_changedGameStateToDead(uint8_t aGameStateLast);
```

### Params
{: .no_toc }
- **aGameStateLast** - last game state

---
## PLUGIN_changedGameStateToRevival
Part in while loop in main triggered by game_state change to Revival (after death)

```cpp
void PLUGIN_changedGameStateToRevival(uint8_t aGameStateLast);
```

### Params
{: .no_toc }
- **aGameStateLast** - last game state

---
## PLUGIN_changedGameStateToStarting
Part in while loop in main triggered by game_state change to Starting (part before actual game)

```cpp
void PLUGIN_changedGameStateToStarting(uint8_t aGameStateLast);
```

### Params
{: .no_toc }
- **aGameStateLast** - last game state

---
## PLUGIN_changedGameStateToEnding
Part in while loop in main triggered by game_state change to Ending (game time is zero)

```cpp
void PLUGIN_changedGameStateToEnding(uint8_t aGameStateLast);
```

### Params
{: .no_toc }
- **aGameStateLast** - last game state

---
## PLUGIN_processCustomMessage
Part in data_process (main loop) for processing custom message

```cpp
void PLUGIN_processCustomMessage(uint8_t* apData, uint16_t aLength,
		uint8_t aDevice);
```

### Params
{: .no_toc }
- **apData** - pointer to array with data bytes
- **aLength** - length of valid bytes in apData array
- **aDevice** - chest (player) code, which send the message, equal to row in table, 0 means coordinator (main app)

---
## PLUGIN_customInit
Part of PLUGIN_init, for users part of initialization, for example global vars for timers (length_death,...)

```cpp
void PLUGIN_customInit(volatile colors_t* apModulesColor1,
		volatile colors_t* apModulesColor2, volatile uint8_t* apModulesDim1,
		volatile uint8_t* apModulesDim2, uint8_t* apModulesVibrationStrength,
		volatile uint8_t* apModulesState);
```

### Params
{: .no_toc }
- **apModulesColor1** - pointer to array[NUM_OF_SLAVES] with basic color (color 1) structure (red, green, blue; each 8 bit) for each slave module
- **apModulesColor2** - pointer to array[NUM_OF_SLAVES] with special color (color 2) structure (red, green, blue; each 8 bit) for each slave module
- **apModulesDim1** - pointer to array[NUM_OF_SLAVES] with dim value of led1 circuit for each slave module, <0; 100>, 0 - leds not lighting, 100 - full brightness
- **apModulesDim2** - pointer to array[NUM_OF_SLAVES] with dim value of led2 circuit for each slave module, <0; 100>, 0 - leds not lighting, 100 - full brightness
- **apModulesVibrationStrength** - pointer to array[NUM_OF_SLAVES] with vibration strength value of for each slave module, <0; 255>, 0 - vibration switched off, 255 - maximum vibration strength
- **apModulesState** - pointer to array[NUM_OF_SLAVES] with state for each slave module, bits structure 0b000VBBAA

		 V - vibration flag, 1 means activate vibration for short time periode
		 BB - state of led2 circuit
		 AA - state of led1 circuit
		 0 turn off
		 1 basic color (color 1)
		 2 special color (color 2)
		 3 stroboscope - activate white blink
