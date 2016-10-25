task main() {
  //motor[armBase1] = vexRT[Ch1]
slaveMotor(armBase2, armBase1);
  setMotorTarget( armBase1, 50, 64, true );

// Wait for motor to move
while(!getMotorTargetCompleted(armBase1))
    wait1Msec(10);
}
