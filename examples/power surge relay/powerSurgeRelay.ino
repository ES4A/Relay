#include <Arduino.h>
#include <Relay.h>

Relay relay1(1, digitalRead(2)); //init power surge Relay

long lastChange;

void setup(){

}

void loop(){
    relay1.tick();
    if(millis() - lastChange > 1000){
        relay1.setState(!relay1.getState());
    }
}
