#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           right,         tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port10,          left,          tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int val = 0;

task main() {
	resetMotorEncoder(left);
	slaveMotor(right, left);
	while(true) {
		//motor[armBase1] = vexRT[Ch1]
		//mapEncoderToMotor(port1, I2C_1);
		//mapEncoderToMotor(right, I2C_1);


		while(!vexRT[Btn7R]) {
			wait1Msec(10);
		}
		val = 1;


		//	motor[right]=127;
		setMotorTarget( left, 200, 127, true );

		while(!getMotorTargetCompleted(left)){
			wait1Msec(10);
			val=getMotorEncoder(left);
			if(vexRT[Btn8U]) {
				motor[left]=0;
				motor[right]=0;
				//setMotorTarget( left, 0, 127, false );
				break;
			}
		}

		while(true) {
			wait1Msec(10);
		if(vexRT[Btn8U]) {
				motor[left]=0;
				motor[right]=0;
				//setMotorTarget( left, 0, 127, false );


			}
		}

		// Add the value 27 to datalog series 1

		// Wait for motor to move
		//while(!getMotorTargetCompleted(right))
		//    wait1Msec(10);

		while(false) {
			datalogAddValue(1, getMotorEncoder(left) );
			if(vexRT[Btn8D]) {
				motor[left]=0;
				motor[right]=0;
				setMotorTarget( left, 0, 127, false );
			}
			if(vexRT[Btn8D]) {
				//motor[right]=-127;
			}
			if(vexRT[Btn8R]) {
				//motor[right]=127;
			}
		}
	}
}
