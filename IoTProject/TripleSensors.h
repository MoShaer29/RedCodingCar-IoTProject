#include "Adafruit_VL53L1X.h"
#include "GlobalVars.h"

//// Setting the sensors addresses.
//// The following function change the adresses of Destinations sensors in order to use same pins.(Input)
void setID(){
    Wire.begin();

    // Reseting the xshut pins
    digitalWrite(XSHT_PIN_FRONT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_LEFT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_RIGHT_SENSOR, LOW);
    delay(10);

    digitalWrite(XSHT_PIN_FRONT_SENSOR, HIGH);
    digitalWrite(XSHT_PIN_LEFT_SENSOR, HIGH);
    digitalWrite(XSHT_PIN_RIGHT_SENSOR, HIGH);
    delay(10);

    digitalWrite(XSHT_PIN_FRONT_SENSOR, HIGH);
    digitalWrite(XSHT_PIN_LEFT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_RIGHT_SENSOR, LOW);

    // Setting the front sensor address
    if(!frontSensor.begin(FRONT_SENSOR_ADDRESS, &Wire)){
        while(1);
    }

    digitalWrite(XSHT_PIN_LEFT_SENSOR, HIGH);

    delay(10);

    // Setting the left sensor address
    if(!leftSensor.begin(LEFT_SENSOR_ADDRESS, &Wire)){
        while(1);
    }

    digitalWrite(XSHT_PIN_RIGHT_SENSOR, HIGH);

    delay(10);

    // Setting the right sensor address
    if(!rightSensor.begin(RIGHT_SENSOR_ADDRESS, &Wire)){
        while(1);
    }
}

void setupSensors(){
    pinMode(XSHT_PIN_FRONT_SENSOR, OUTPUT);
    pinMode(XSHT_PIN_LEFT_SENSOR, OUTPUT);
    pinMode(XSHT_PIN_RIGHT_SENSOR, OUTPUT);

    digitalWrite(XSHT_PIN_FRONT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_LEFT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_RIGHT_SENSOR, LOW);

    setID();

    // Front sensor start measuring
    if(!frontSensor.startRanging()){
        while(1)
            delay(10);
    }

    frontSensor.setTimingBudget(50);

    // Left sensor start measuring
    if(!leftSensor.startRanging()){
        while(1)
            delay(10);
    }

    leftSensor.setTimingBudget(50);

    // Right seansor start measuring
    if(!rightSensor.startRanging()){
        while(1)
            delay(10);
    }

    rightSensor.setTimingBudget(50);
}


//// Reduce the noises from the sensors readings.
bool IsSafe(int16_t x, int16_t y){
    return (((x - y) > -10) && ((x - y) < 10));
}

//// Get the distances that the sensors read.
void getMeasurings(int16_t &frontDistance, int16_t &leftDistance, int16_t &rightDistance){

    if(frontSensor.dataReady() && leftSensor.dataReady() && rightSensor.dataReady()){

        int16_t temp_frontDistance , temp_leftDistance , temp_rightDistance;

        temp_frontDistance = frontSensor.distance();

        temp_leftDistance = leftSensor.distance();

        temp_rightDistance = rightSensor.distance();


        if((IsSafe(temp_frontDistance, frontDistance)) && (IsSafe(leftDistance, temp_leftDistance)) && (IsSafe(rightDistance, temp_rightDistance))){

        }

        else{
            while(((IsSafe(temp_frontDistance, frontDistance)) && (IsSafe(leftDistance, temp_leftDistance)) && (IsSafe(rightDistance, temp_rightDistance))) == false){
                rightDistance = temp_rightDistance;
                leftDistance = temp_leftDistance;
                frontDistance = temp_frontDistance;

                temp_frontDistance = frontSensor.distance();
                temp_leftDistance = leftSensor.distance();
                temp_rightDistance = rightSensor.distance();
            }
        }
        if((frontDistance == -1) || (leftDistance == -1) || (rightDistance == -1)){
            return;
        }
        frontSensor.clearInterrupt();
        leftSensor.clearInterrupt();
        rightSensor.clearInterrupt();
    }
}
