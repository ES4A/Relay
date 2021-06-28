#include <Arduino.h>
#include "Relay.h"

Relay::Relay(){
    relayActivePin = NULL;
    Relaytype = none;
}

Relay::Relay(uint8_t activePin){
    relayActivePin = activePin;
    Relaytype = normal;
    pinMode(activePin, OUTPUT);
}

Relay::Relay(uint8_t changePin, bool initState){
    relayActivePin = changePin;
    currentState = initState;
    Relaytype = powerSurge;
    pinMode(changePin, OUTPUT);
}

Relay::Relay(uint8_t activePin, uint8_t resetPin, bool initState){
    relayActivePin = activePin;
    relayResetPin = resetPin;
    Relaytype = bistable;
    pinMode(activePin, OUTPUT);
    pinMode(resetPin, OUTPUT);
}

void Relay::tick(){
    if((millis() - startChange > switchTime) && currentState != newState){
        if(Relaytype == powerSurge){
            if(activeLow){
                digitalWrite(relayActivePin, HIGH);
            }
            else{
                digitalWrite(relayActivePin, LOW);
            }
            currentState = newState;
        }

        if(Relaytype == bistable){
            if(activeLow){
                if(newState){
                    digitalWrite(relayActivePin, HIGH);
                }
                else{
                    digitalWrite(relayResetPin, HIGH);
                }
            }
            else{
                if(newState){
                    digitalWrite(relayActivePin, LOW);
                }
                else{
                    digitalWrite(relayResetPin, LOW);
                }
            }
            currentState = newState;
        }
    }
}

void Relay::setState(bool setNewState){
    if(currentState != setNewState && newState == currentState){
        startChange = millis();
        newState = setNewState;
        if(Relaytype == normal){
            if(activeLow){
                digitalWrite(relayActivePin, !setNewState);
            }
            else{
                digitalWrite(relayActivePin, setNewState);
            }
            currentState = setNewState;
        }

        if(Relaytype == bistable){
            if(activeLow){
                if(newState){
                    digitalWrite(relayActivePin, LOW);
                }
                else{
                    digitalWrite(relayResetPin, LOW);
                }
            }
            else{
                if(newState){
                    digitalWrite(relayActivePin, HIGH);
                }
                else{
                    digitalWrite(relayResetPin, HIGH);
                }
            }
        }

        if(Relaytype == powerSurge){
            if(activeLow){
                digitalWrite(relayActivePin, LOW);
            }
            else{
                digitalWrite(relayActivePin, HIGH);
            }
        }
    }
}

bool Relay::getState(){
    return currentState;
}

void Relay::setActiveLow(bool newActiveLow){
    activeLow = newActiveLow;
    if(newState == currentState){
        if(Relaytype == normal){
            if(activeLow){
                digitalWrite(relayActivePin, !currentState);
            }
            else{
                digitalWrite(relayActivePin, currentState);
            }
        }

        if(Relaytype == bistable){
            if(activeLow){
                digitalWrite(relayActivePin, HIGH);
                digitalWrite(relayResetPin, HIGH);
            }
            else{
                digitalWrite(relayActivePin, LOW);
                digitalWrite(relayResetPin, LOW);
            }
        }

        if(Relaytype == powerSurge){
            if(activeLow){
                digitalWrite(relayActivePin, HIGH);
            }
            else{
                digitalWrite(relayActivePin, LOW);
            }
        }
    }
    else{
        if(Relaytype == normal){
            if(activeLow){
                digitalWrite(relayActivePin, !currentState);
            }
            else{
                digitalWrite(relayActivePin, currentState);
            }
        }

        if(Relaytype == bistable){
            if(activeLow){
                if(newState){
                    digitalWrite(relayActivePin, LOW);
                    digitalWrite(relayResetPin, HIGH);
                }
                else{
                    digitalWrite(relayActivePin, HIGH);
                    digitalWrite(relayResetPin, LOW);
                }
            }
            else{
                if(newState){
                    digitalWrite(relayActivePin, HIGH);
                    digitalWrite(relayResetPin, LOW);
                }
                else{
                    digitalWrite(relayActivePin, LOW);
                    digitalWrite(relayResetPin, HIGH);
                }
            }
        }

        if(Relaytype == powerSurge){
            if(activeLow){
                digitalWrite(relayActivePin, LOW);
            }
            else{
                digitalWrite(relayActivePin, HIGH);
            }
        }
    }
}

void Relay::setSwitchTime(uint16_t newTime){
    if(newTime > 0){
        switchTime = newTime;
    }
}