# Arduino Relay Library
A Library to control different types of relays

## Relay types
- normal Relay
- bistable Relay
- power surge relay

## Getting Started

```CPP
#include <Arduino.h>
#include <relay.h>
```


### normal Relay

```CPP
Relay relay1(1); //(control Pin)
```

### bistable Relay

```CPP
Relay relay1(1, 2, false); //(aktiv Pin, reset Pin, init State)
```

### power Surge Relay

```CPP
Relay relay1(1, false); //(control Pin, init State)
```


### required in loop

```CPP
void loop(){
  relay1.tick();
}
```
## Functions

### set State

```CPP
  relay1.setState(true);
```

### get State

```CPP
  bool relayState = relay1.getState();
```

### Active Low

```CPP
  relay1.setActiveLow(true);
```

### set Time to Switch

```CPP
  relay1.setSwitchTime(100); // default 100ms
```
