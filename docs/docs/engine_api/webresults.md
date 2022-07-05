---
layout: default
title: Functions for Web results
parent: Engine API
---

# Functions for Web results
{: .no_toc}
This is set of function to get data from system that will be rendered

<details markdown="block">
  <summary>
    Table of contents
  </summary>
{: .text-delta }
1. TOC
{:toc}
</details>

---
## useSelector
standard react-redux useSelector if it needs to be used



---
## gameResultState
state of game could be value of GameResultsState:
		 RUNNING - Game is running
		 FRESH_FINISH - Game just finished
		 FINISHED - Game finished used for final results



---
## styled
styled-components: 5.3.3 could be used



---
## KillLog
helper function to fetch kill logs, only view needs to be provided


### Params
{: .no_toc }
- **view** - React component for viewing
- **style** - React css style
- **log** - Automatically provided by system typeof IKillLog
- **opacity** - Automatically provided by system to do fading effect is not necessary to use it
- **gameTime** - Automatically provided by system actual game time
- **index** - Automatically provided by system index of log in list

### Usage
{: .no_toc }
```cpp
 <KillLog view={<ReactComponent>} style={{ }}}>
```

---
## CircularProgressbar
react-circular-progressbar: 1.0.0



---
## FontAwesomeIcon
TODO not sure how to handle icons



---
## FlipMove
react-flip-move: 3.0.4,



---
## minuteSecondsString
Convert game time to formatted mm:ss string


### Params
{: .no_toc }
- **num** - seconds attribute

---
## findExtremeByProp
find max or min from players data


### Params
{: .no_toc }
- **attr** - one of IEvPlayers or custom variables
- **gameResultState** - FRESH_FINISH or FINISHED letting system know where to look
- **findMin** - optionally parameter by default max is searched if min required use true

---
## getPlayer
get player from list by index


### Params
{: .no_toc }
- **index** - index of player in result list
- **return** IEvPlayers data structure

---
## getTeam
get team from list by index


### Params
{: .no_toc }
- **index** - index of team in result list
- **return** IEvTeam data structure

---
## getPlayersLength
get players length


- **return** number of players

---
## getTeamsLength
get teams length


- **return** number of teams

---
## getPlayerProp
get player prop


### Params
{: .no_toc }
- **index** - index of player,
- **prop** - keyof IEvPlayers or custom variables
- **return** value of property

---
## getEvaluationItem
get on of IEvaluation


### Params
{: .no_toc }
- **name** - keyof IEvaluation
- **return** value of property
