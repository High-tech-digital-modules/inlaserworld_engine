---
layout: default
title: Main concept
nav_order: 3
---

# Main concept
The goal is to create template user-friendly editable and strait forward. 
Plugin as we call it is set of source code which is interpreted by our engine during the game.
There is almost unlimited possibilities how the game will behave and how users will set up game.


## Plugin folder structure

| **Path**                            | **Description**                                                 |
|-------------------------------------|-----------------------------------------------------------------|
| arena/src/main.c                    | This file contains C/C++ code for main unit                     |
| chest/src/plugin/plugin_functions.c | This file contains C code for chest                             |
| pdf_result/main.js                  | Code for generating pdf results based on all features of pdfKit |
| webresult/main.js                   | React code for visualization of game                            |
| custom_data.json                    | Description of custom data for plugin                           |

## Main unit
Main unit is a brain of whole game. It is and set of functions that can be called from plugin while
engine is calling handlers implemented in code at certain events.

[Check engine functions](../engine_api/main_unit_engine.md){: .btn .btn-purple }
[Check plugin events](../engine_api/main_unit_plugin.md){: .btn .btn-blue }

### This part is responsible for:
- evaluating game
- custom setting of game
- control main music and sound effect in arena
- handling bonus and light device effects and actions

## Chest unit
Chest unit is controlling how whole chest and fazer behaves. Here could be written complete logic
in which situation should device react and how.

[Check engine functions](../engine_api/chest_engine.md){: .btn .btn-purple }
[Check plugin events](../engine_api/chest_plugin.md){: .btn .btn-blue }

### Chest unit is responsible for:
- full control of chest and fazer real time
- chest lights and fazer effects
- control of display
- control of sound effects

## Custom data
Custom data is json descriptor that is nicely displayed as editable table for ease of use in console.

| **Type** | **Description**    |
|:---------|:-------------------|
| uint32_t | Unsigned integer   |
| string   | Text               |
| int32_t  | Signed number      |
| double   | Float number       |
| boolean  | True false         |
| color    | Color of something |

example of one field of array

[Check discription](https://github.com/High-tech-digital-modules/inlaserworld_engine/tree/main/plugins/deathmatch/custom_data.json){: .btn .btn-purple }


```json
{
    "name":"<>",           // name of variable used anywhere in engine
    "type":"int32_t",      // type defined by table above
    "value":0,             // Value based on type
    "label":"<>",          // Label
    "inGameMenu": false    // Meaning not only in game template could be eddited but also during game creation
}
```
