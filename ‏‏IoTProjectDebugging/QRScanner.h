#include "GlobalVars.h"

void scanQR(int* turns, int& numOfTurns){
    while(QRcode[0] != (FINISH+'0')){
        while(Serial.available() > 0){
            QRcode = Serial.readString();
            turns[numOfTurns] = QRcode[0]-'0';
            if(turns[numOfTurns] == TURN_RIGHT){
                digitalWrite(RIGHT_LED, HIGH);
                delay(300);
                digitalWrite(RIGHT_LED, LOW);
            }
            else if(turns[numOfTurns] == FORWARD){
                digitalWrite(FRONT_LED, HIGH);
                delay(300);
                digitalWrite(FRONT_LED, LOW);
            }
            else if(turns[numOfTurns] == TURN_LEFT){
                digitalWrite(LEFT_LED, HIGH);
                delay(300);
                digitalWrite(LEFT_LED, LOW);
            }
            else{
                digitalWrite(LEFT_LED, HIGH);
                digitalWrite(FRONT_LED, HIGH);
                digitalWrite(RIGHT_LED, HIGH);
                delay(300);
                digitalWrite(RIGHT_LED, LOW);
                digitalWrite(FRONT_LED, LOW);
                digitalWrite(LEFT_LED, LOW);
            }
            numOfTurns++;
            Serial.println(QRcode);
        }
    }
}