#include "GlobalVars.h"
#include "Blinks.h"

long getPressDuration(){
    long timeBegin = millis();
    while(digitalRead(BUTTON_PIN)){
        long timeEndTmp = millis();
        if((timeEndTmp - timeBegin) > 3000){
            blinkForReset();
        }
    }
    long timeEnd = millis();

    return timeEnd - timeBegin;
}