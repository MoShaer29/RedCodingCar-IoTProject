#include <TB6612FNG.h>

// 27 - Standby pin
// 14 - AIN1 pin
// 12 - AIN2 pin
// 13 - PWMA pin
// To reverse forward motor direction, switch the AIN1 and AIN2 pin numbers.
Tb6612fng motor(27, 14, 12, 13);
// Tb6612fng motor(27, 12, 14, 13); // Reversed forward motor direction.

void setup() {
  Serial.begin(115200);
  motor.begin();
}

void loop() {
  Serial.printf("Loop: %d\n", millis());
  // 500ms forwards
  motor.drive(1, 5000);
 
  motor.brake();
  delay(1000);
}
