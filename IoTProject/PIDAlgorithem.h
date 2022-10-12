#include "GlobalVars.h"

void PIDControl(double &motorSpeedA, double &motorSpeedB, int16_t rightDistance, int16_t leftDistance){
    int desiredDistance = (rightDistance + leftDistance)/2;
    int error = rightDistance - desiredDistance;

    P = Kp * error;
    kiTotal += error;
    I = Ki * kiTotal;
    D = Kd * (error - priorError);
    priorError = error;
    double pidResult = P + I + D;
//    Serial.println("error is: %d ----", error);

    motorSpeedB = baseSpeedB + pidResult;
    motorSpeedA = baseSpeedA - pidResult;
    if(motorSpeedB > maxSpeedB){
        motorSpeedB = maxSpeedB;
    }
    if(motorSpeedA > maxSpeedA){
        motorSpeedA = maxSpeedA;
    }
    if(motorSpeedB < -1){
        motorSpeedB = -1;
    }
    if(motorSpeedA < -1){
        motorSpeedA = -1;
    }
}
