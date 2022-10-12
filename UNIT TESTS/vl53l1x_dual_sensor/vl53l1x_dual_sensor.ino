#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);
Adafruit_VL53L1X vl532 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Wire.begin();
  Wire1.begin(33,32);

  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor 1: "));
    Serial.println(vl53.vl_status);
    while (1){
        delay(10);   
    }
  }
  Serial.println(F("VL53L1X sensor 1 is OK!"));
  Serial.print(F("Sensor 1 ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl532.begin(0x29, &Wire1)) {
    Serial.print(F("Error on init of VL sensor 2: "));
    Serial.println(vl532.vl_status);
    while (1){
      delay(10);
    }
  }
  Serial.println(F("VL53L1X sensor 2 is OK!"));
  Serial.print(F("Sensor 2 ID: 0x"));
  Serial.println(vl532.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging on sensor 1: "));
    Serial.println(vl53.vl_status);
    while (1){
      delay(10);
    }
  }

  if (! vl532.startRanging()) {
    Serial.print(F("Couldn't start ranging on sensor 2: "));
    Serial.println(vl532.vl_status);
    while (1){
      delay(10);
    }
  }
  
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget 1 (ms): "));
  Serial.println(vl53.getTimingBudget());

  vl532.setTimingBudget(50);
  Serial.print(F("Timing budget 2 (ms): "));
  Serial.println(vl532.getTimingBudget());
}

void loop() {
  int16_t distance, distance2;

  if (vl53.dataReady() && vl532.dataReady()) {
    // new measurement for the taking!
    distance2 = vl532.distance();
    distance = vl53.distance();
    if (distance == -1 || distance2 == -1) {
      // something went wrong!
      //Serial.print(F("Couldn't get distance from sensor 1: "));
      //Serial.println(vl53.vl_status);
      return;
    }
    Serial.print(F("Distance: "));
    Serial.print(distance);
    Serial.print(" mm  |");
    Serial.print(distance2);
    Serial.println(" mm");
    // data is read out, time for another reading!
    vl53.clearInterrupt();
    vl532.clearInterrupt();

  }
}
