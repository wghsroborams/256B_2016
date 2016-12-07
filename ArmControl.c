#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           baseleft,      tmotorVex393_HBridge, PIDControl, encoderPort, I2C_1)
#pragma config(Motor,  port2,           midleft,       tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port3,           backright,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backleft,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           frontleft,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           frontright,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           wrist,         tmotorVex393_MC29, PIDControl, encoderPort, I2C_3)
#pragma config(Motor,  port9,           midright,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          baseright,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(OFF) // "Competition" or "OFF"
#pragma autonomousDuration(15) // 15 sec
#pragma userControlDuration(105) // 1 min 45 sec

#include "Vex_Competition_Includes.c"

/***** Settings *****/

int deadzonesize = 15;

int valb=0;
int valm=0;
int valw=0;

float speedb = 0.3;
float speedm = 1.0;
float speedw = 0.7;

bool measureMode = true;

/***** Utility *****/

void moveTo(tMotor mot, int target) {
	setMotorTarget(mot, target, 127, true);
}

void moveToSpeed(tMotor mot, int target, int speed) {
	setMotorTarget(mot, target, speed, true);
}

void moveToWait(tMotor mot, int target) {
	moveTo(mot, target);

	// Wait for motor to move
	while(!getMotorTargetCompleted(mot)) {
		wait1Msec(5);
	}
}

float deadzone(int input) {
	if (abs(input)<deadzonesize) {
		return 0;
	}

	float out = input - deadzonesize; // Adjust so that the values come out of the deadzone at 0
	out = out * 128/(128-deadzonesize); // Rescale so that the max value can still be reached


	return out;
	//return abs(input) > deadzonesize ? ((input - deadzonesize)) : 0; // * 1/(1/deadzonesize)
}

int improveInput(int input) {
	return round(pow(deadzone(input)/128, 3) * 128);
}

//A 91, -105, -471
//B -181, -153, -72
//C -1084, -301, -518
//D -745, -303, -427

void toD() {
	moveToSpeed(baseleft, -745, round(127*speedb));
	moveToSpeed(midleft, -303, round(127*speedm));
	moveToSpeed(wrist, -427, round(127*speedw));
}

void toC() {
	moveToSpeed(baseleft, -724, round(127*speedb));
	moveToSpeed(midleft, -703, round(127*speedm));
	moveToSpeed(wrist, -2885, round(127*speedw));
}

void toB() {

	moveToSpeed(baseleft, -1680, round(127*speedb));
	moveToSpeed(midleft, -324, round(127*speedm));
	moveToSpeed(wrist, -1372, round(127*speedw));
}

void toA() {
	moveToSpeed(baseleft, 20, round(127*speedb));
	moveToSpeed(midleft, -323, round(127*speedm));
	moveToSpeed(wrist, -2422, round(127*speedw));
}

void moveArmTo(int a, int b, int c) {
	moveToSpeed(baseleft, a, round(127*speedb));
	moveToSpeed(midleft, b, round(127*speedm));
	moveToSpeed(wrist, c, round(127*speedw));
}

/*********** Main Control ***************/

void pre_auton()
{
	//Place pre-autonomous code here

	slaveMotor(baseright, baseleft);
	slaveMotor(midright, midleft);

	resetMotorEncoder(baseleft);
	resetMotorEncoder(midleft);
	resetMotorEncoder(wrist);
}

task autonomous()
{
	//Place autonomous code here



}

/*
Controls:
7U Btn: open arm
8 Btns: change arm presets (btn pos is related to resulting robot pos)
joysticks: control movement of body (wheels)
*/

task usercontrol()
{
	// configure slave motorss
	slaveMotor(baseright, baseleft);
	slaveMotor(midright, midleft);

	// reset all encoders
	resetMotorEncoder(baseleft);
	resetMotorEncoder(midleft);
	resetMotorEncoder(wrist);

	// Wait for command to unfold
	while(!measureMode) {
		if(vexRT[Btn7U]) {
			// Get arm unstuck and ready to be pulled out of position
			//moveToWait(baseleft, -20);
			//moveToWait(midleft, 37);
			//moveToWait(baseleft, -341);
			//moveToWait(midleft, 50);


			moveToWait(baseleft, -44);
			moveToWait(midleft, 94);
			moveToWait(baseleft, -587);
			moveToWait(midleft, 94);
			//moveArmTo(-44, 94, 0);
			//moveArmTo(-587, 94, 0);
			// open claw
			motor[claw]=127;
			wait1Msec(120);
			motor[claw]=0;

			moveArmTo(-595, 20, -1950);

			// -44, 94, 0
			//-587, "", ""
			// open claw
			// -595, 20, -307



			// pull arm out of position
			//moveToWait(baseleft, -800);



			// rotate wrist into position
			//moveToWait(wrist, -440);

			// move on to the rest of the code
			break;
		}
	}

	while(measureMode) {
		// debug code to read encoder values
		valb=getMotorEncoder(baseleft);
		valm=getMotorEncoder(midleft);
		valw=getMotorEncoder(wrist);
	}
	// For free movement change statements to their reverse
	// for the rest of the program, listen to preset and driving commands
	int X2 = 0, Y1 = 0, X1 = 0;
	while(!measureMode) {
		if(vexRT[Btn8L]) {
			toA();
		}
		//if(vexRT[Btn8D]) {
		//	toB();
		//}
		if(vexRT[Btn8R]) {
			toB();
		}
		if(vexRT[Btn8U]) {
			toC();
		}

		if(vexRT[Btn5U]) { // open
			motor[claw]=127;
			} else {
			if(vexRT[Btn6U]) { // open
				motor[claw]=-127;
				} else {
				motor[claw]=0;
			}
		}

		// clean up joystick readings
		Y1 = improveInput(vexRT[Ch3]);
		X1 = improveInput(vexRT[Ch4]);
		X2 = improveInput(vexRT[Ch1]);

		// map inputs to mecanum wheels
		motor[frontright] = Y1 - X2 - X1;
		motor[backright] =  Y1 - X2 + X1;
		motor[frontleft] = Y1 + X2 + X1;
		motor[backleft] =  Y1 + X2 - X1;
	}
}
