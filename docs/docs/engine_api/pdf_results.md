---
layout: default
title: PDF results engine
parent: Engine API
---

# PDF results engine
{: .no_toc}
This is set of functions, consts and global variables to get data from system that can be printed out using pdf

<details markdown="block">
  <summary>
    Table of contents
  </summary>
{: .text-delta }
1. TOC
{:toc}
</details>

---
## doc
pdfkit document



---
## regularText
font of regular text



---
## boldText
font of bold text



---
## findExtremeByProp
find max or min from players data


### Params
{: .no_toc }
- **players** - IEvPlayers[] list of players game.result.evaluationPlayers
- **attr** - key of IEvPlayers
- **findMin** - optionally parameter by default max is searched if min required use true

### Usage
{: .no_toc }
```javascript
 const {extreme: playerPrecision, playerName, playerIndex} = findExtremeByProp(
   game.result.evaluationPlayers, "playerPrecision")
```

---
## Table
class for helping generate table TODO: document class



---
## fileName
random generated filename



---
## moment
moment package



---
## game
whole QueueGame object selected from database



---
## customData
extracted template customData



---
## tl
translate function for local template translations



---
## tg
translate function for global translations


