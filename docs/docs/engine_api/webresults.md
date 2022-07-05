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
```javascript
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
- **return** formatted string

### Usage
{: .no_toc }
```javascript
 const s = minuteSecondsString(70); // 01:10
```

---
## findExtremeByProp
find max or min from players data


### Params
{: .no_toc }
- **attr** - one of IEvPlayers or custom variables
- **gameResultState** - FRESH_FINISH or FINISHED letting system know where to look
- **findMin** - optionally parameter by default max is searched if min required use true
- **return** extreme value, playerName and playerIndex

### Usage
{: .no_toc }
```javascript
 const {extreme: maxFootSteps, playerName, playerIndex}
   = findExtremeByProp('playerFootSteps', GameResultsState.FRESH_FINISH);
```

---
## getPlayer
get player from list by index selector hook


### Params
{: .no_toc }
- **index** - index of player in result list
- **return** IEvPlayers data structure

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const player = useSelector(getPlayer(index));
```

---
## getTeam
get team from list by index selector hook


### Params
{: .no_toc }
- **index** - index of team in result list
- **return** IEvTeam data structure

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const team = useSelector(getTeam(index));
```

---
## getPlayersLength
get players length selector hook


- **return** number of players

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const playerNumber = useSelector(getPlayersLength());
```

---
## getTeamsLength
get teams length selector hook


- **return** number of teams

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const teamNumber = useSelector(getTeamsLength());
```

---
## getPlayerProp
get player prop selector hook


### Params
{: .no_toc }
- **index** - index of player,
- **prop** - keyof IEvPlayers or custom variables
- **return** value of property

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const playerName = useSelector(getPlayerProp(index, 'playerName'));
```

---
## getEvaluationItem
get on of IEvaluation selector hook


### Params
{: .no_toc }
- **name** - keyof IEvaluation
- **return** value of property

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const evaluationGameTime = useSelector(getEvaluationItem('evaluationGameTime'));
```
