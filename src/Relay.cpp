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

Relay::Relay(uint8_t activePin, uint8_t resetPin){
    relayActivePin = activePin;
    relayResetPin = resetPin;
    Relaytype = bistable;
    pinMode(activePin, OUTPUT);
    pinMode(resetPin, OUTPUT);
}

void Relay::tick(){
    if((millis() - startChange < switchTime) && currentState != newState){
        if(Relaytype == powerSurge){
            digitalWrite(relayActivePin, LOW);
            currentState = newState;
        }

        if(Relaytype == bistable){
            if(newState){
                digitalWrite(relayActivePin, LOW);
            }
            else{
                digitalWrite(relayResetPin, LOW);
            }
            currentState = newState;
        }
    }
}

void Relay::setState(bool setNewState){
    startChange = millis();
    newState = setNewState;
    if(Relaytype == normal){
        digitalWrite(relayActivePin, setNewState);
        currentState = setNewState;
    }

    if(Relaytype == bistable){
        if(newState){
            digitalWrite(relayActivePin, HIGH);
        }
        else{
            digitalWrite(relayResetPin, HIGH);
        }
    }

    if(Relaytype == powerSurge){
        digitalWrite(relayActivePin, HIGH);
    }
}

void Relay::setSwitchTime(uint16_t newTime){
    if(newTime > 0){
        switchTime = newTime;
    }
}