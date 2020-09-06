/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Daniel J                                         */
/*    Created:      Sat Feb 08 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include <string>

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here







//declaration (has no value a.k.a. null value)
int example1;

//initialization (has to be in some method or at the start)
void necessaryMethod1( void ) {
  example1 = 1;


  //assigning new data
  example1 = 2;

  //incrementing (value will be 3)
  example1++;
  //decrementing (value wil be 2)
  example1--;

}



//declaration and initialization in same step
int example2 = 4;




//data types (spacing for clarity)
int         exampInt     = -4;
bool        exmpBool     = true;
double      exampDouble  = 4.3478951478274;
std::string exampeString = "Thiny";
char        exampChar    = 'a';




//need to do loops inside of methods
void necessaryMethod(){

  //uses 3 steps as the condition
  //runs 63 times
  for(int i = 0; i<63; i++){
    Brain.Screen.print("Hello");
  }

  //nested for loops
  //loops over row and column
  for( int r = 0; r<10; r++){
    for( int c = 0; c<10; c++){
      Brain.Screen.print(r + c);
    }
  }
  

  //variable not necessary in some cases but very useful
  int i = 0;
/*while(       some condition  ){
    code;
}*/
//while print "loop still running" 41 times
  while(       i<=40     ){
    i++;
    Brain.Screen.print("loop still running");
  }

  //example without ints (will only run once)
  bool BtnPress = true;
  while(BtnPress==true){
    BtnPress=false;

  }


  //infinite loop
  //will always print "still stuck" until program is forcefully ended
  //generally avoided except for user_control
  while(1==1){
    Brain.Screen.print("Still stuck");
  }

}




































































/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    // sssshhhhhh... pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}