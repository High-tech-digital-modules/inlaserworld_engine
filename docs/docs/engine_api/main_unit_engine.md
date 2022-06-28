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
 void PLUGIN_setup() {
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

### Params
{: .no_toc }
- **return** - Return state of the running game

---
## ENGINE_getPreviousGameState
Get game previous state

```cpp
uint16_t ENGINE_getPreviousGameState();
```

### Params
{: .no_toc }
- **return** - Return previous state of the running game

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
- **return** - Elapsed time of the game

---
## ENGINE_sendCustomMessage
Send custom message to player

```cpp
void ENGINE_sendCustomMessage(const uint8_t *apData, uint8_t aLen, int16_t aPlayerIndexTo, int16_t aPlayerIndexFrom);
```

### Params
{: .no_toc }
- **apData** - data to be send
- **aLen** - Length of data
- **aPlayerIndexTo** - Index of player who will receive message, -1 reserved for coordinator
- **aPLayerIndexFrom** - Index of player who sent this message, -1 is default for coordinator

---
## ENGINE_getPLayers
get list of players

```cpp
Player * ENGINE_getPLayers();
```

### Params
{: .no_toc }
- **return** - list of players

---
## ENGINE_getPlayersLength
get length of player

```cpp
uint8_t ENGINE_getPlayersLength();
```

### Params
{: .no_toc }
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
