#pragma config(Motor,  port1,           Arm,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           LeftF,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LeftB,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RightF,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RightB,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          Spinner,          tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
        // All activities that occur before the competition starts
        // Example: clearing encoders, setting servo positions, ...
resetMotorEncoder(LeftF);
resetMotorEncoder(LeftB);
resetMotorEncoder(RightF);
resetMotorEncoder(RightB);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
const int direction = 7;
task autonomous()
{
  // .....................................................................................
  // Use command for no auton   AuonomousCodePlaceholderForTesting();
  // .....................................................................................

//change direction in accordance with notebook (1-4)





if(direction == 1){
	motor[LeftF]=motor[LeftB]=95;
	motor[RightF]=motor[RightB]=95;
	wait1Msec(700);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=0;
	wait1Msec(500);
	motor[LeftF]=motor[LeftB]=-95;
	motor[RightF]=motor[RightB]=95;
	motor[ArmL]=motor[ArmR]=15;
	wait1Msec(1000);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=127;
	wait1Msec(900);
	motor[LeftF]=motor[LeftB]=100;
	motor[RightF]=motor[RightB]=100;
	motor[ArmL]=motor[ArmR]=15;
	wait1Msec(1600);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=0;
	wait1Msec(500);
}
else if(direction == 2){
	motor[LeftF]=motor[LeftB]=95;
	motor[RightF]=motor[RightB]=95;
	wait1Msec(700);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=0;
	wait1Msec(500);
	motor[LeftF]=motor[LeftB]=95;
	motor[RightF]=motor[RightB]=-95;
	motor[ArmL]=motor[ArmR]=15;
	wait1Msec(1000);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=127;
	wait1Msec(900);
	motor[LeftF]=motor[LeftB]=100;
	motor[RightF]=motor[RightB]=100;
	motor[ArmL]=motor[ArmR]=15;
	wait1Msec(1600);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=0;
	wait1Msec(500);
}
else if(direction==3){
	motor[ArmL]=motor[ArmR]=127;
	wait1Msec(900);
	motor[LeftF]=motor[LeftB]=50;
	motor[RightF]=motor[RightB]=50;
	motor[ArmL]=motor[ArmR]=15;
	wait1Msec(7500);
	motor[LeftF]=motor[LeftB]=0;
	motor[RightF]=motor[RightB]=0;
	motor[ArmL]=motor[ArmR]=0;
	wait1Msec(500);
}
else{		//to account for user error in inputing the variable
	motor[LeftF]=motor[LeftB]=-95;
	motor[RightF]=motor[RightB]=95;
	wait1Msec(5000);
}






}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
        // User control code here, inside the loop

        while (true)
        {
          // This is the main execution loop for the user control program. Each time through the loop
          // your program should update motor + servo values based on feedback from the joysticks.

          // .....................................................................................
          // Insert user code here. This is where you use the joystick values to update your motors, etc.
          // Use UserControlCodePlaceholderForTesting(); for no control
          // .....................................................................................

//Driver Controls Heck Ya BOI


	  int leftside=vexRT[Ch3];		//sets respective buttons or joysticks to a variable for easier to read code
	  int rightside=vexRT[Ch2];
	  //int clawclose=vexRT[Btn6U];
	  //int clawopen=vexRT[Btn6D];
	  int armup=vexRT[Btn5U];
	  int armdown=vexRT[Btn5D];
	  int spinup=vexRT[Btn6U];
	  int spindown=vexRT[Btn6D];
	  
	  
	  //creates "deadspace" to prevent motor burnout when joystick not pressed
	  //can be changed to lower numbers like 5 to give driver more control but don't go much lower

	  //Left controls
		if (leftside >= 15)
		{
			motor[LeftF]=leftside;
			motor[LeftB]=leftside;			//sets front and back motors on left to joystick input 10 to 127
		}
		else if (leftside <= -15)			//-127 to -10
		{
			motor[LeftF]=leftside;
			motor[LeftB]=leftside;
		}
		else			//if between -10 and 10 set motors to 0
		{
			motor[LeftF]=0;
			motor[LeftB]=0;
		}

		//Right controls
		if (rightside >= 15)		//same comments apply from above
		{
			motor[RightF]=rightside;
			motor[RightB]=rightside;
		}
		else if (rightside <= -15)
		{
			motor[RightF]=rightside;
			motor[RightB]=rightside;
		}
		else
		{
			motor[RightF]=0;
			motor[RightB]=0;
		}
		//Arm controls
		if (armup == 1)		//same comments apply from above
		{											//if both buttons pressed claw will go up due to order of if statements
			motor[Arm]=127;
		}
		else if (armdown == 1)
		{
			motor[Arm]=-85;
		}
		else
		{
			motor[Arm]=20;
		}
		//Spin controls
		if (spinup == 1)		//same comments apply from above
		{											//if both buttons pressed claw will go up due to order of if statements
			motor[Spinner]=127;
		}
		else if (spindown == 1)
		{
			motor[Spinner]=-127;
		}
		else
		{
			motor[Spinner]=0;
		}


	}
}
