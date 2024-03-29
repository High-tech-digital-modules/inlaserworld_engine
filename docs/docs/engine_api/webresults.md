---
layout: default
title: Web results engine
parent: Engine API
---

# Web results engine
{: .no_toc}
This is set of functions, consts and global variables to get data from system that will be rendered

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
 <KillLog view={<ReactComponent/>} style={{ }}/>
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
## getPlayerByItsProp
get player from list by property and value


### Params
{: .no_toc }
- **key** - property of player like playerName
- **return** IEvPlayers data structure

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const player = useSelector(getPlayer("playerName", "Daniel"));
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
## getTeamName
Function to get team name by color or name


### Params
{: .no_toc }
- **team** - Team object

### Usage
{: .no_toc }
```javascript
 // this must be used with selector it is hook
 const teamName = getTeamName(team);
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

---
## GameResultsState
const game result state
		
		 RUNNING - Game is running
		 FRESH_FINISH - Game just finished
		 FINISHED - Game finished used for final results



---
## PlayerGameState
const player game state
		
		 END: 0,
		 ALIVE: 1,
		 DEAD: 2,
		 STARTING: 3,
		 REVIVAL: 4,



---
## getResultSnapshotsLength
get length of snapshots


- **return** length of snapshots

---
## getVisualizationColor
get color of visualization based on color selected


### Params
{: .no_toc }
- **color** - color of selection
- **return** color of visualization

---
## setSnapshotResultIndex
set result snapshot index


### Params
{: .no_toc }
- **index** - index of result snapshot

---
## getSnapshotResultIndex
get actual index of selected sub results


- **return** index

---
## tl
translate function for local template translations



---
## tg
translate function for global translations



---
## customData
extracted custom template data



---
## registerCustomDataListener
setup event listener when arena sends some custom data


### Params
{: .no_toc }
- **listener** listener like {listener}

---
## removeCustomDataListener
remove event listener when arena sens some custom data


### Params
{: .no_toc }
- **listener** listener like {listener}

---
## sendCustomMessage
sends message to arena plugin must be JSON


### Params
{: .no_toc }
- **message** must be JSON

---
## getMediaItem
get media item info by selected id


### Params
{: .no_toc }
- **media** item ID
