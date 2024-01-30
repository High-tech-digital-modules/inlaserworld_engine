---
layout: default
title: Virtual screens
parent: Tutorials
---

# Virtual screens
The idea about virtual screens is that in a space there are multiple TV & displays.
In those devices there is always browser which is able to render virtual screen.

Virtual screen is able to:
 - Be controlled by game by engine
 - Always show last game result until next game ended
 - Auto mode when it shows running game or last result if no running game available

## Control virtual screen by engine
from arena plugin this function should be used:
```cpp
ENGINE_useVirtualScreen(1, Engine::VirtualScreen::gameLoaded);
```

then on the web result site ```gameResultState``` variable hold this state e.g.
be inspired by following:

- Note: on the web result side gameLoaded = LOADED, gameRunning = RUNNING etc.

```jsx
function MainWrapper () {
  if(gameResultState === GameResultsState.LOADED) {
    return <div>Just loaded</div>
  }
  return <Main/>
}
```