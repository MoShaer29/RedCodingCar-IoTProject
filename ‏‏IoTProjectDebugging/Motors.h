void MoveFront(Tb6612fng &motors, double speedA, double speedB, int secs){
    motors.drive(speedB, speedA, secs, true);
}

void RotateRight(Tb6612fng &motors){
    motors.drive(baseSpeedA, -1*baseSpeedB, 1395, true);
    motors.brake();
}

void RotateLeft(Tb6612fng &motors){
    motors.drive(-0.5*baseSpeedB, baseSpeedA, 2100, true);
    motors.brake();
}