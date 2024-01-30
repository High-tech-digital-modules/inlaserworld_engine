---
layout: default
title: Messaging
parent: Tutorials
---

# Messaging
This chapter is about custom messaging between selected components 

## Arena -> Webresults
If there is custom message which needs to be sent to visualization 
from arena use:
```cpp
// ...
rapidjson::Document d(rapidjson::kObjectType);
d.AddMember("test", rapidjson::Value(10), d.GetAllocator());
ENGINE_sendCustomMessageToVisualization(d);
// ...
```

Message on the webresult side can be handled by following:

- This can be handled in any component, so multiple listeners can exist

```javascript
// ...
    const receivedCustomData = (data) => {
      console.log({data, from: 1});
    }
    
    React.useEffect(() => {
        const listener = {
          listener: receivedCustomData
        };
        registerCustomDataListener(listener);
        return () => {
          removeCustomDataListener(listener);
        }
    }, []);
// ...
```

## Webresults -> Arena
check following code snippet.
```jsx
<button 
  onClick={() => sendCustomMessage({test: 11})}>
  Click me I will send message
</button>
```

In arena plugin following callback handles this event:
```cpp
void PLUGIN_customMessageFromVisualization(const rapidjson::Value &aValue){
    printf("received custom message from web %d\n", aValue["test"].GetUint());
}
```

## Arena -> Chest
 - To send check function ```ENGINE_sendCustomMessage``` in:
[Arena engine functions](../engine_api/main_unit_engine.md)

 - To receive message check ```PLUGIN_processCustomMessage``` in:
[Chest plugin events](../engine_api/chest_plugin.md)

## Chest -> Arena
 - To send check function ```ENGINE_sendCustomMessage``` in:
[Chest engine functions](../engine_api/chest_engine.md)
 - To receive message check ```PLUGIN_processCustomMessage``` in:
[Check plugin events](../engine_api/main_unit_plugin.md)