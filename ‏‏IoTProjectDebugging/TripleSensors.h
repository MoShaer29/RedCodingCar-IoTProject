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
        Serial.println(F("Failed to boot first VL53L0X"));
        while(1);
    }

    Serial.println(F("frontSensor sensor OK!"));
    Serial.print(F("frontSensor ID: 0x"));
    Serial.println(frontSensor.sensorID(), HEX);

    digitalWrite(XSHT_PIN_LEFT_SENSOR, HIGH);

    delay(10);

    // Setting the left sensor address
    if(!leftSensor.begin(LEFT_SENSOR_ADDRESS, &Wire)){
        Serial.println(F("Failed to boot second VL53L0X"));
        while(1);
    }

    Serial.println(F("leftSensor sensor OK!"));
    Serial.print(F("leftSensor ID: 0x"));
    Serial.println(leftSensor.sensorID(), HEX);

    digitalWrite(XSHT_PIN_RIGHT_SENSOR, HIGH);

    delay(10);

    // Setting the right sensor address
    if(!rightSensor.begin(RIGHT_SENSOR_ADDRESS, &Wire)){
        Serial.println(F("Failed to boot second VL53L0X"));
        while(1);
    }

    Serial.println(F("rightSensor sensor OK!"));
    Serial.print(F("rightSensor ID: 0x"));
    Serial.println(rightSensor.sensorID(), HEX);
}

void setupSensors(){
    pinMode(XSHT_PIN_FRONT_SENSOR, OUTPUT);
    pinMode(XSHT_PIN_LEFT_SENSOR, OUTPUT);
    pinMode(XSHT_PIN_RIGHT_SENSOR, OUTPUT);

    Serial.println(F("Shutdown pins inited..."));

    digitalWrite(XSHT_PIN_FRONT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_LEFT_SENSOR, LOW);
    digitalWrite(XSHT_PIN_RIGHT_SENSOR, LOW);

    Serial.println(F("Both in reset mode...(pins are low)"));

    Serial.println(F("Starting..."));

    setID();

    // Front sensor start measuring
    if(!frontSensor.startRanging()){
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(frontSensor.vl_status);
        while(1)
            delay(10);
    }
    Serial.println(F("Ranging started"));

    frontSensor.setTimingBudget(50);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(frontSensor.getTimingBudget());


    // Left sensor start measuring
    if(!leftSensor.startRanging()){
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(leftSensor.vl_status);
        while(1)
            delay(10);
    }
    Serial.println(F("Ranging started"));

    leftSensor.setTimingBudget(50);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(leftSensor.getTimingBudget());


    // Right seansor start measuring
    if(!rightSensor.startRanging()){
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(rightSensor.vl_status);
        while(1)
            delay(10);
    }
    Serial.println(F("Ranging started"));

    rightSensor.setTimingBudget(50);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(rightSensor.getTimingBudget());
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
            Serial.print(F("Couldn't get distance: "));
            Serial.println(frontSensor.vl_status);
            Serial.println(leftSensor.vl_status);
            Serial.println(rightSensor.vl_status);
            return;
        }
        Serial.print(F("Front Distance: "));
        Serial.print(frontDistance);
        Serial.println(" mm");

        Serial.print(F("Left Distance: "));
        Serial.print(leftDistance);
        Serial.println(" mm");

        Serial.print(F("Right Distance: "));
        Serial.print(rightDistance);
        Serial.println(" mm");

        frontSensor.clearInterrupt();
        leftSensor.clearInterrupt();
        rightSensor.clearInterrupt();
    }
}