#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include <TB6612FNG.h>
#include "Adafruit_VL53L1X.h"

// Main Use
#define FORWARD 2
#define TURN_LEFT 1
#define TURN_RIGHT 0
#define FINISH 3
#define CAR_BODY 19.5
#define MAX_TURNS 20
#define SHORT_PRESS_TIME 3000


// Button and Main Use (buttons and leds pins)
#define BUTTON_PIN 34
#define FRONT_LED 16
#define RIGHT_LED 17
#define LEFT_LED 32


// Sensors Use
#define IRQ_PIN_FRONT_SENSOR 2
#define IRQ_PIN_LEFT_SENSOR 15
#define IRQ_PIN_RIGHT_SENSOR 5 

// Address we will assign (Sensors Use)
#define FRONT_SENSOR_ADDRESS 0x30
#define LEFT_SENSOR_ADDRESS 0x31
#define RIGHT_SENSOR_ADDRESS 0x32

// Set the pins to shutdown (Sensors Use)
#define XSHT_PIN_FRONT_SENSOR 23
#define XSHT_PIN_LEFT_SENSOR 19
#define XSHT_PIN_RIGHT_SENSOR 18


// Definning the sensors (Sensors Use)
Adafruit_VL53L1X frontSensor = Adafruit_VL53L1X(XSHT_PIN_FRONT_SENSOR, IRQ_PIN_FRONT_SENSOR);
Adafruit_VL53L1X leftSensor = Adafruit_VL53L1X(XSHT_PIN_LEFT_SENSOR, IRQ_PIN_LEFT_SENSOR);
Adafruit_VL53L1X rightSensor = Adafruit_VL53L1X(XSHT_PIN_RIGHT_SENSOR, IRQ_PIN_RIGHT_SENSOR);


// QR-Scanner Use
String QRcode;


// PID-Algorithm Use
double Kp = 0.007, Ki = 0 , Kd = 0;
double P, I, D;
double kiTotal = 0.0;
double priorError = 0.0;
const double desiredState = (double) 150;
const double maxSpeedA = 1;
const double maxSpeedB = 1;
const double baseSpeedA = 1;
const double baseSpeedB = 0.65;


// Main Use
int16_t frontDistance, leftDistance, rightDistance , previousLeftDistance, previousRightDistance;
int numOfTurns = 0 , currTurn = 0;
int turns[MAX_TURNS];
bool firstRun = true;
Tb6612fng motors(27, 12, 14, 13, 26, 25, 33); 
double motorSpeedA, motorSpeedB;

enum ButtonStatuses {RESET, START, STOP};
ButtonStatuses buttonStatus = STOP;

#endif //GLOBALVARS_H
