# RedCodingCar-IoTProject

By: Mohammad Shaer, Yosef Break, Seraj Srour.

# Description: 
This Project is about a robotic car that can solve a maze by the help of the user.
The car always drive forward until it is stuck with a junction, then it do the next move according to the data provided by the user.
The data contains directions that are encoded as a QR code, the car will scan all the directions before entering the maze and save them aside to use when getting stuck in a junction.
there is an option to rescan the directions in case there was an error with the scan order or the car isn't able to continue as the given data. 


# The Content:
  1. IoTProject: contains the code that is loaded into the ESP.
  2. IoTProjectDebugging: contains the same code in IoTProject but with changes that help to debug the code in case there was an error.
  3. UNIT TESTS: contains the base code that helped us reach the final one (tests to check if the hardware work correctly).
  4. User Manual: contains the connections diagram the user manual (how to use the car). 
  
  
# Libraries used in the code:
  1. Adafruit_VL53L1X (version 3.1)
  2. TB6612FNG (version 1.0.2): https://github.com/vincasmiliunas/ESP32-Arduino-TB6612FNG
