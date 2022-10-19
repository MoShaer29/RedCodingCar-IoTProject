
/*
 * The following code was written by Red Coding Car Team.
 * <TB6612FNG.h> GitHub Link : https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG/blob/master/TB6612FNG.h
 * PID GitHub Link: https://github.com/br3ttb/Arduino-PID-Library/
 * Last Update : 04/10/2022. By: Yosef Br & Mohammad Sh
 * Sensor Guide: https://learn.sparkfun.com/tutorials/tb6612fng-hookup-guide/all
 * Pins & motos:
 *      MotorA (red & white cables colors), Pins: 14 - AIN1 pin (red white), 12 - AIN2 pin (red white), 13 - PWMA pin (red white)
 *      MotorB (White & orange cables colors), Pins: 26 - AIN1 pin (blue orange), 25 - AIN2 pin (blue orange) , 33 - PWMA pin (blue orange)
 *      27 - Standby pin
 */


#include <TB6612FNG.h>
#include "Adafruit_VL53L1X.h"
#include "TripleSensors.h"
#include "PIDAlgorithem.h"
#include "QRScanner.h"
#include "Motors.h"
#include "Button.h"
#include "GlobalVars.h"
#include "Blinks.h"

/* Functions */

void TurnLedsAndPins(){
    pinMode(FRONT_LED, OUTPUT);
    pinMode(LEFT_LED, OUTPUT);
    pinMode(RIGHT_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

//// Calculate the time needed for the car to move half of the given distance.
int timeCalucate(int16_t distance){
    double speedRun = 0.09, distanceToMove = 0.60 * distance;

    return ((distanceToMove / speedRun) + 20);
}

//// Checks if the car got stucked in a junction and can't move as the given direction.
bool canContinue(int curTurn){
    if((curTurn == TURN_LEFT) && (leftDistance < 240)) {
        return false;
    }
    else if((curTurn == TURN_RIGHT) && (rightDistance < 240)) {
        return false;
    }
    else if((curTurn == FORWARD) && (frontDistance < 240)) {
        return false;
    }
    return true;
}

//// Make the leds blink in specific pattern until long press occur.
void askForReset(){
    while(buttonStatus != RESET){
        blinkForReset();
        long pressDuration = getPressDuration();
        if(pressDuration > SHORT_PRESS_TIME){
            ESP.restart();
        }
    }
}

//// Make the leds blink in specific pattern when the car finish all the given direction until long press occur. 
void finishedTurns(){
    while(buttonStatus != RESET){
        finishBlink();
        long pressDuration = getPressDuration();
        if(pressDuration > SHORT_PRESS_TIME){
            ESP.restart();
        }
    }
}

void setup(){
    Serial.begin(115200);
    while(!Serial){ delay(1000); }
    TurnLedsAndPins();
    scanQR(turns, numOfTurns);
    motors.begin();
    setupSensors();
}

void loop(){
    if(buttonStatus != START){
        long pressDuration = getPressDuration();
        if(pressDuration > SHORT_PRESS_TIME){
            ESP.restart();
        }
        else if(pressDuration > 10){
            buttonStatus = START;
            firstRun = true;
        }
    }
    else {
        long pressDuration = getPressDuration();
        if(pressDuration > 10){
            buttonStatus = STOP;
            digitalWrite(FRONT_LED, LOW);
            return;
        }
        getMeasurings(frontDistance, leftDistance, rightDistance);
        if(firstRun){
            previousLeftDistance = leftDistance;
            previousRightDistance = rightDistance;
            firstRun = false;
        }

        //// Checks if the car have reached a junction.
        if(((rightDistance > (previousRightDistance + 48)) || (rightDistance > 250)) ||
            ((leftDistance > (previousLeftDistance + 48)) || (leftDistance > 250)) ||
            ((frontDistance < 175) && (frontDistance > 0))) {

            digitalWrite(FRONT_LED, LOW);
            if(currTurn >= (numOfTurns-1)){
                finishedTurns();
            }

            getMeasurings(frontDistance, leftDistance, rightDistance);

            int distanceForward = ((frontDistance) < 300) ? (frontDistance) : 300;

            int timeTomove = timeCalucate(distanceForward);

            //// Checks if it is a small junction.
            if((previousRightDistance < 250) && (previousLeftDistance < 250)){
                digitalWrite(FRONT_LED, HIGH);
                MoveFront(motors, baseSpeedA, baseSpeedB, timeTomove);
                digitalWrite(FRONT_LED, LOW);
            }
            else{
                digitalWrite(FRONT_LED, HIGH);
                if(frontDistance < 500){
                    MoveFront(motors, baseSpeedA, baseSpeedB, timeCalucate((frontDistance-50)/0.6));
                }
                else{
                    MoveFront(motors, baseSpeedA, baseSpeedB, timeCalucate(134));
                }
                digitalWrite(FRONT_LED, LOW);
            }
              
            getMeasurings(frontDistance, leftDistance, rightDistance);

            if(turns[currTurn] == TURN_RIGHT){
                if(canContinue(turns[currTurn])){
                    digitalWrite(RIGHT_LED, HIGH);
                    RotateRight(motors);
                    timeTomove = timeCalucate(2 * (previousRightDistance+50));
                    digitalWrite(RIGHT_LED, LOW);
                }
                else{
                    askForReset();
                    return;
                }
            }
            else if(turns[currTurn] == TURN_LEFT){
                if(canContinue(turns[currTurn])){
                    digitalWrite(LEFT_LED, HIGH);
                    RotateLeft(motors);
                    timeTomove = timeCalucate(2 * (previousLeftDistance+50));
                    digitalWrite(LEFT_LED, LOW);
                }
                else{
                    askForReset();
                    return;
                }
            }
            else{
                if(frontDistance < 200
                ){
                    askForReset();
                    return;
                }
                else{
                    distanceForward = 250;
                    timeTomove = timeCalucate(distanceForward);
                    digitalWrite(FRONT_LED, HIGH);
                    MoveFront(motors, baseSpeedA, baseSpeedB, timeTomove);
                    digitalWrite(FRONT_LED, LOW);
                }
            }
            if((previousRightDistance > 250) || (previousLeftDistance > 250)){
                timeTomove = timeCalucate(2 * 77);
            }

            digitalWrite(FRONT_LED, HIGH);
            MoveFront(motors, baseSpeedA, baseSpeedB, timeTomove);
            motors.brake();
            getMeasurings(frontDistance, leftDistance, rightDistance);
            currTurn++;
        }
        else{
            digitalWrite(FRONT_LED, HIGH);
            PIDControl(motorSpeedA, motorSpeedB, rightDistance, leftDistance);
            MoveFront(motors, motorSpeedA, motorSpeedB, 200);
        }

        previousLeftDistance = leftDistance;
        previousRightDistance = rightDistance;
    }
}
