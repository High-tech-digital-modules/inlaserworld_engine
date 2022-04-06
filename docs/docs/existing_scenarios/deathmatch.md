---
layout: default
title: Deathmatch scenario
parent: Existing scenarios
---

# Deathmatch

[Sources on github](https://github.com/High-tech-digital-modules/inlaserworld_engine/tree/main/plugins/deathmatch){: .btn }

This is the simplest game. The all players are against each other and the goal is to stay
alive as long as possible and take down as many players as possible. Once you are taken down
you get 5 second penalty when you are not able to use fazer, and then you got 1 second immortality
while you can use fazer but opponents can't hit you.

## Scoring

| **Name**                 | **Value** | **Comment**                                                     |
|:-------------------------|:---------:|:----------------------------------------------------------------|
| Take down points         |    100    | When you take down someone                                      |
| Taken down points        |    -50    | When someone take down you                                      |
| Hit points               |    20     | When you hit someone, only if shoot power is different than 100 |
| Points per ammo          |     0     | If ammo                                                         |
| Double take down points  |    25     | When you take down two players in short period of time          |
| Monster take down points |    50     | When you take down three players in short period of time        |

## Description
During the game player lights by their selected color on both light circuits. 
When the player got hit place on chest or gun while strobe by white color and
also hit place will vibrate. During penalty period chest light is switched off and then 
during immortality  first circuit will light on while second is blinking by same color. If 
additional setting **shoot power** used players can play on more hits before take down. The chest is 
visualizing it by fading intensity of its lights from bottom to top.

## Additional setting

| **Name**    | **Value** | **Desription**                                       |
|:------------|:---------:|:-----------------------------------------------------|
| Shoot power |    100    | The power of shot could be value from 0 (max) to 100 |
