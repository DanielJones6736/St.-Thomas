/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Daniel Jones                                              */
/*    Created:      11/12/19                                                  */
/*    Description:  V5 project                                                */
/*    Version:      01/11/20                                                  */   
/*                                                                            */
/*----------------------------------------------------------------------------*/
//needed to use non C++ standard functions like autonomous or competition
//#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "vex.h"

//easier than typing vex.h each time
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// global instances of motors/devices
//    name           port    ratio     reversed
motor Angler = motor(PORT1, ratio18_1, true );
motor Angler_2=motor(PORT15,ratio18_1, false);
motor LeftB  = motor(PORT3, ratio18_1, false);
motor Intk1  = motor(PORT4, ratio18_1, false);
motor Intk2  = motor(PORT5, ratio18_1, true );
motor RightB = motor(PORT7, ratio18_1, true );
motor Arm2   = motor(PORT9, ratio18_1, false);
motor Arm    = motor(PORT10,ratio18_1, true );
controller Controller1 = controller();

// auton selector sets which auton to use (supposed to be) chosen during pre-auton
//set to 3 b/c just goes straight forward to not mess up allies
int atnSel=3;


// wheelDiameter is the measurement of a wheel from edge to edge in centimeters.
const double wheelDiameterCM  = 10.16; 

// Calculate wheel circumference: circumference = (wheelDiameter)(PI)
// for moving a motor
const double circumference        = wheelDiameterCM * 3.141592654;  
const double Gear_to_wheel_ratio  = 1;
const double to_degrees           = 360*Gear_to_wheel_ratio/circumference;   //switches distance to go in CM to degrees to turn

//for turning drive train
//50.67 comes is approximated by the diagonal distance between the wheels (front left to back right)
const double turn_ratio   =  (50.67/wheelDiameterCM) * Gear_to_wheel_ratio;


//helper function  (calculations in a rotateFor command breaks the robot)
double disToDegrees(double dis){
  return dis*to_degrees;
}

//similar helper function for turning
//divided by 2 b/c one wheel needs to do half the work
double disToTurnDeg(double deg){
  return turn_ratio*deg/2;
}

//more streamlined way to move any given motor
void rotateForCM(double CM, int power, vex::motor Temp, bool end){
  Temp.rotateFor(disToDegrees(CM), vex::rotationUnits::deg, power, vex::velocityUnits::pct, end);
  return;

}

//helper streamlined function for turning a set degrees
//always favors turning right for pos and left for neg
//left motors move forward and right motors move backward for positive numbers (vice versa)
void turningDeg(double degrees){
  // Divide by two because each wheel provides half the rotation
  LeftB.rotateFor(vex::directionType::fwd, disToTurnDeg(degrees), vex::rotationUnits::deg, 30, vex::velocityUnits::pct, false);
  RightB.rotateFor(vex::directionType::rev, disToTurnDeg(degrees), vex::rotationUnits::deg, 30, vex::velocityUnits::pct, true);
}

//helper streamlined function for moving the robot easily
void moveForCM(double dis, int pow){
  LeftB.rotateFor(vex::directionType::fwd, disToDegrees(dis), vex::rotationUnits::deg, pow, vex::velocityUnits::pct, false);
  RightB.rotateFor(vex::directionType::fwd, disToDegrees(dis), vex::rotationUnits::deg, pow, vex::velocityUnits::pct, true);
}

//just want to stop everything after auton for safety
void OhNoStopEverything(){
  LeftB.stop();
  RightB.stop();
  Angler.stop();
  Arm.stop();
  Arm2.stop();
  Intk1.stop();
  Intk2.stop();
  vex::task::sleep(500);  //sleep at the end b/c want to make the robot chill to stabilize robot for a sec
}


//move arm to bottom position to be "default" or 0 position
void resetArm(){
  Arm. spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
  Arm2.spin(vex::directionType::rev, 10, vex::velocityUnits::pct);
  vex::task::sleep(500);
  OhNoStopEverything();
  Arm. resetRotation();  //resets internal encoder
  Arm2.resetRotation();
}






//Abandon hope all ye who enter here

void draw_grid(void) { 
    Brain.Screen.setPenColor(color::white);
    
    for (int i = 0; i < 2; i++) {
        //this draws vertical lines. The X stays the same but the Y changes:
        Brain.Screen.drawLine(160*(i+1),0,160*(i+1),240);
        //this draws horizontal lines. The X changes but the Y stays the same:
        Brain.Screen.drawLine(0,80*(i+1),480,80*(i+1));
    }
    //this weird order follows the same order below
    //                    x    y   output
    Brain.Screen.printAt( 80, 200, "7");
    Brain.Screen.printAt(400, 200, "9");
    Brain.Screen.printAt(240, 200, "8");
    Brain.Screen.printAt( 80,  40, "1");
    Brain.Screen.printAt(400,  40, "3");
    Brain.Screen.printAt(240,  40, "2");
    Brain.Screen.printAt( 80, 120, "4");
    Brain.Screen.printAt(400, 120, "6");
    Brain.Screen.printAt(240, 120, "5");
}

void draw_touch() {
    Brain.Screen.setPenColor(color::red);
    //this draws a circle around the place the user is touching or last touched the LCD
    Brain.Screen.drawCircle(Brain.Screen.xPosition(),Brain.Screen.yPosition(),30);
}


//hope restored



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//determines what atnSel is
//this should w/ a vex switch/competition
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
  //Here Be Dragons, ye have been forewarned

  Brain.Screen.render(true,false); //set VSync (vertical sync) on, automatic refresh to off
        //When we call Brain.Screen.render() with no arguments, it will force a redraw of the screen.
        //With the previous command here we turned off automatic redraws, so the LCD will only redraw
        //when we tell it to, which means we can guarantee it won't redraw in the middle of one of our
        //other drawing commands and give a partial picture. Getting partial pictures on redraws is
        //what causes flickering when drawing without this buffering scheme.
    while (true) {
        Brain.Screen.clearScreen(); //clears the back buffer for drawing, default clear color is black
        draw_grid(); //draws our grid to the back buffer
        Brain.Screen.render(); //flips the back buffer to the screen all at once, preventing flickering
        if (Brain.Screen.pressing()) { //if screen is touched...
            while (Brain.Screen.pressing()) { //wait until the user stops touching the screen
                Brain.Screen.clearScreen(); //while waiting, maintain the grid and draw
                draw_grid();                //a touch indicator around the user's finger
                draw_touch();
                Brain.Screen.render();
            }
            vex::task::sleep(1); //wait a second for their hand to get a little further away
            if (Brain.Screen.yPosition() > 160) {                   //released in bottom third of the screen
                if (Brain.Screen.xPosition() < 160) {                   //released in left third of the screen
                         atnSel=7;      //bottom left (no auton yet)
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                        atnSel=9;   //bottom right (no auton yet)
                } else {                                                //released in middle (left-to-right) third of the screen
                        atnSel=8;//bottom middle (no auton yet)
                }
            } else if (Brain.Screen.yPosition() < 80) {             //released in top third of the screen
                if (Brain.Screen.xPosition() < 160) {                   //released in left third of the screen
                    atnSel=1;     //top left
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                    atnSel=3;      //top right
                } else {                                                //released in middle (left-to-right) third of the screen
                    atnSel=2;    //top middle
                }
            } else {                                                //released in middle (top-to-bottom) of the screen
                if (Brain.Screen.xPosition() < 160) {                   //released in left third of the screen
                    atnSel=4;      //middle left
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                    atnSel=6;       //middle right
                } else {                                                //released in middle (left-to-right) third of the screen
                    atnSel=5;        //middle middle
                }
            }
            //dt.stop(brakeType::coast); this was a predefined function from the Author but I don't remember for what reason
        } else {
            vex::task::sleep(1);  //was originally 0.1 so might cause some problems
        }

  //return to charted territory
}
}
/*
 * various autonomous tasks to split up the functions
 * easier to find and debug one specific auton or choose the right one
 * auton GUI can support upto 9 so there are 9 functions
*/
//pick up four cubes, score, red side
void autonomous1(){
  //move to front of cubes
    moveForCM(69.5, 30);

    //rotate intakes for a lot & collect cubes
    rotateForCM(1000, 100, Intk1, false);
    rotateForCM(1000, 100, Intk2, false);
    moveForCM(41.5, 15);  //75 is arbitrary to keep from running over cubes

    Intk1.stop();
    Intk2.stop();

    vex::task::sleep(100);
    //Turn to score zones
    turningDeg(150);

    vex::task::sleep(100);
    //move to scoring zone
    moveForCM(117, 30);

    vex::task::sleep(100);
    //angle to deposit cubes
    rotateForCM(50, 100, Angler, true);

    vex::task::sleep(100);

    //move back a little
    moveForCM(-8, 50);

    OhNoStopEverything();
}
//pick up four cubes, score, blue side
void autonomous2(){
  //move to front of cubes
    moveForCM(69.5, 30);

    vex::task::sleep(100);
    //rotate intakes for a lot & collect cubes
    rotateForCM(1000, 100, Intk1, false);
    rotateForCM(1000, 100, Intk2, false);
    moveForCM(41.5, 15);  //75 is arbitrary to keep from running over cubes

    Intk1.stop();
    Intk2.stop();

    vex::task::sleep(100);
    //Turn to score zones
    turningDeg(-150);

    vex::task::sleep(100);
    //move to scoring zone
    moveForCM(117, 30);

    vex::task::sleep(100);
    //angle to deposit cubes
    rotateForCM(50, 100, Angler, true);

    vex::task::sleep(100);
    //move back a little
    moveForCM(-8, 50);

    OhNoStopEverything();
}
//start lined up with score zone, push preload into zone, back up
void autonomous3(){
  //push into zone
    rotateForCM(1000, 1, Arm, false);
    rotateForCM(1000, 1, Arm2, false);
    moveForCM(-50, -50);
    vex::task::sleep(500);
    //back up
    moveForCM(30, 70);
    OhNoStopEverything();
}
void autonomous4(){
    moveForCM(-10, -50);
    OhNoStopEverything();
}
//pick up cube in middle, turn LEFT, and score
void autonomous5(){
  //pick up cube
  rotateForCM(1000, 50, Intk1, false);
  rotateForCM(1000, 50, Intk2, false);
  moveForCM(10, 25);
  //turn left
  turningDeg(-90);
  //move to score zone
  moveForCM(83, 50);
  //deposit first cube (have to check values)
  rotateForCM(-1000, -50, Intk1, false);
  rotateForCM(-1000, -50, Intk2, true);
  //move arm up and score 2nd cube
  rotateForCM(100, 50, Arm, false);
  rotateForCM(100, 50, Arm2, true);
  rotateForCM(-1000, -50, Intk1, false);
  rotateForCM(-1000, -50, Intk2, true);
  //back up
  moveForCM(-10, -50);
   OhNoStopEverything();
}
void autonomous6(){
  
}
void autonomous7(){
  
}
void autonomous8(){
  
}
void autonomous9(){
  
}
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

  //auton switch, for given input it will execute a specific auton
  //autons are on the onenote
  //input distance(cm) to travel * to_degrees to convert to degrees needed to move wheel

  switch(atnSel){
  //pick up four cubes, score, red side
  case 1:
    autonomous1();
    break;
  //pick up four cubes, score, blue side
  case 2:
    autonomous2();
    break;
  //lined up with score zone, push preload into zone, back up
  case 3:
    autonomous3();
    break;
  //extra test auton
  case 4:
    autonomous4();
    break;
  case 5:
    autonomous5();
    break;
  case 6:
    autonomous6();
    break;
  case 7:
    autonomous7();
    break;
  case 8:
    autonomous8();
    break;
  case 9:
    autonomous9();
    break;
  default:
    //move forward a little
    moveForCM(10, 75);

    //spin like mad to indicate horrible failure
    rotateForCM(20, 100, LeftB, false);
    rotateForCM(-20, 100, RightB, true);
    //haha you made it unironically spin, you screwed up
    OhNoStopEverything();
    break;
  }
  /*
  resetArm(); //need to reset position for all autons
  */
  //put here to avoid conflict with driver control
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
  //declared variables here to prevent constant new variables being declared inside while loop
  int  Left;     //channel 3 to determine left side
  int  Right;    //channel 2 to determine right side
  bool Angler1; //Button A to straigten angler upwards
  bool Angler2; //Button B to move Angler back
  bool IntkO;   //Button L1 to Open the intake using both motors
  bool IntkC;   //Button L2 to Close the intake using both motors
  bool ArmU;    //Button R1 to move arm up
  bool ArmD;    //Button R2 to move arm down
  // User control code here, inside the loop

  //resetArm(); //JUST HERE TO SEE IF WORKS REMOVE LATER 
  //OhNoStopEverything();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    // update the motors based on the input values
    Left    = Controller1.Axis3.position();
    Right   = Controller1.Axis2.position();
    Angler1 = Controller1.ButtonA.pressing();
    Angler2 = Controller1.ButtonB.pressing();
    IntkO   = Controller1.ButtonR1.pressing();
    IntkC   = Controller1.ButtonR2.pressing();
    ArmU    = Controller1.ButtonL1.pressing();
    ArmD    = Controller1.ButtonL2.pressing();

    //move left side if outside of deadzone, else stop
    if(Left<-10 || Left>10){
      LeftB.spin(vex::directionType::fwd, Left/(100/65)   , vex::velocityUnits::pct);
    }
    else{
      LeftB.spin(vex::directionType::fwd, 0      , vex::velocityUnits::pct);
    }

    //move right side if outside of deadzone, else stop
    if(Right<-10 || Right>10){
      RightB.spin(vex::directionType::fwd, Right/(100/65)   , vex::velocityUnits::pct);
    }
    else{
      RightB.spin(vex::directionType::fwd, 0      , vex::velocityUnits::pct);
    }

    //Move the intake inwards or outwards given input
    //Prefers moving inwards over outwards if both buttons pressed
    if(IntkO){
      Intk1.spin(vex::directionType::fwd, 80   , vex::velocityUnits::pct);
      Intk2.spin(vex::directionType::fwd, 80   , vex::velocityUnits::pct);
    }
    else if(IntkC){
      Intk1.spin(vex::directionType::fwd, -80   , vex::velocityUnits::pct);
      Intk2.spin(vex::directionType::fwd, -80   , vex::velocityUnits::pct);
    }
    else{
      Intk1.spin(vex::directionType::fwd, 0      , vex::velocityUnits::pct);
      Intk2.spin(vex::directionType::fwd, 0      , vex::velocityUnits::pct);
    }
    
    /* different way to do arm. Also more efficient for not moving Arm all the time
    // check the ButtonL1/ButtonL2 status to control Angler
    if (Controller1.ButtonL1.pressing()) {
      Angler.spin(forward);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      Angler.spin(reverse);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      Angler.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1LeftShoulderControlMotorsStopped = true;
    }*/

    //Move the arm (for the intake) in certain direction
    //prefers moving up if both buttons pressed
    /*  //don't need this anymore but still useful
    if(Arm.position(vex::rotationUnits::deg)>=100000000000){ //check this arbitrary value to prevent tipping
      Arm.spin(vex::directionType::fwd, -5, vex::velocityUnits::pct);
      Arm2.spin(vex::directionType::fwd, -5, vex::velocityUnits::pct);
    }
        


    */
    //could implement something similar to prevent hurting bottom of robot
    //60 40
    if(ArmU){
      if(     Arm2.rotation(vex::rotationUnits::deg)<Arm.rotation(vex::rotationUnits::deg)){
        Arm.spin (vex::directionType::fwd, 90, vex::velocityUnits::pct);
        Arm2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      }
      else if(Arm2.rotation(vex::rotationUnits::deg)>Arm.rotation(vex::rotationUnits::deg)){
        Arm.spin (vex::directionType::fwd, 100, vex::velocityUnits::pct);
        Arm2.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
      }
      else{
      Arm.spin (vex::directionType::fwd, 100, vex::velocityUnits::pct);
      Arm2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      } 
    }
    else if(ArmD){
      Arm.spin (vex::directionType::fwd, -40, vex::velocityUnits::pct);
      Arm2.spin(vex::directionType::fwd, -40, vex::velocityUnits::pct);
    }
    else{
      if(     Arm2.rotation(vex::rotationUnits::deg)<Arm.rotation(vex::rotationUnits::deg)){
        Arm.spin (vex::directionType::fwd, 0.5, vex::velocityUnits::pct);
        Arm2.spin(vex::directionType::fwd, 1.0, vex::velocityUnits::pct);
      }
      else if(Arm2.rotation(vex::rotationUnits::deg)>Arm.rotation(vex::rotationUnits::deg)){
        Arm.spin (vex::directionType::fwd, 1.0, vex::velocityUnits::pct);
        Arm2.spin(vex::directionType::fwd, 0.5, vex::velocityUnits::pct);
      }
      else{
      Arm.spin (vex::directionType::fwd, 0.5   , vex::velocityUnits::pct);    //arbitrary value to keep arm up when no press
      Arm2.spin(vex::directionType::fwd, 0.5, vex::velocityUnits::pct);
      }
    }
    
    //Moves Large anglers thing that hold cube stack (either more angeled or more perpendicular to floor)
    //Prefers perp. to floor
    if(Angler1){
      Angler.spin  (vex::directionType::fwd, 100, vex::velocityUnits::pct);
      Angler_2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Angler2){
      Angler.spin  (vex::directionType::fwd, -100, vex::velocityUnits::pct);
      Angler_2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    }
    else{
      Angler.spin  (vex::directionType::fwd, 0, vex::velocityUnits::pct);    //Use near 0 if it holds when no button pressed
      Angler_2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
    }


    // wait before repeating the process
    vex::task::sleep(20);
    //can lower this to increase update speed for motors. Not needed though because 20 msec is not a lot of time to react.
  }
 
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    //Run the pre-autonomous function. 
    pre_auton();
       
    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
}