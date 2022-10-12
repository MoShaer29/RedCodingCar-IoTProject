#ifndef BLINKS_H
#define BLINKS_H
#include "GlobalVars.h"

//// Blinking pattern when asking for a reset.
void blinkForReset(){
    for(int i=0; i<3; i++){
        digitalWrite(FRONT_LED, HIGH);
        digitalWrite(RIGHT_LED, HIGH);
        digitalWrite(LEFT_LED, HIGH);

        delay(300);

        digitalWrite(FRONT_LED, LOW);
        digitalWrite(RIGHT_LED, LOW);
        digitalWrite(LEFT_LED, LOW);

        delay(300);
    }
}

//// Blinking pattern when the car finish all the given turns.
void finishBlink(){
    for(int i=0; i<3; i++){
        digitalWrite(FRONT_LED, HIGH);
        delay(300);
        digitalWrite(FRONT_LED, LOW);

        delay(300);

        digitalWrite(RIGHT_LED, HIGH);
        delay(300);
        digitalWrite(RIGHT_LED, LOW);

        delay(300);

        digitalWrite(LEFT_LED, HIGH);
        delay(300);
        digitalWrite(LEFT_LED, LOW);

        delay(300);
    }
}

#endif //BLINKS_H