/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Mon Mar 25 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// Drive Forward
// This program instructs your robot to move forward at half power for three
// seconds. There is a two second pause at the beginning of the program.
//
// Robot Configuration: 
// [Smart Port]    [Name]        [Type]           [Description]       [Reversed]
// Motor Port 1    LeftMotor     V5 Smart Motor    Left side motor     false
// Motor Port 10   RightMotor    V5 Smart Motor    Right side motor    true
//

#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here
motor Angler = motor(PORT1, ratio18_1, true);
motor LeftB = motor(PORT3, ratio18_1, false);
motor Intk1 = motor(PORT4, ratio18_1, false);
motor Intk2 = motor(PORT5, ratio18_1, true);
motor RightB = motor(PORT7, ratio18_1, true);
motor Arm2  = motor(PORT9, ratio18_1, false);
motor Arm = motor(PORT10, ratio18_1, true);

// auton selector chosen during pre-auton
int atnSel=4;
//4 as default for testing pre-auton switch

// wheelDiameter is the measurement of a wheel from edge to edge in centimeters.
const double wheelDiameterCM  = 10.16; 

// Calculate wheel circumference: circumference = (wheelDiameter)(PI)
//for moving a motor
const double circumference        = wheelDiameterCM * 3.141592654;  
const double Gear_to_wheel_ratio  = 1;
const double to_degrees           = 360*Gear_to_wheel_ratio/circumference;

//for turning drive train
//37.67 comes is approximated by the diagonal distance between the wheels (front left back right)
//50.67 works better though (friction?)
const double turn_ratio   =  (50.67/wheelDiameterCM) * Gear_to_wheel_ratio;

double disToDegrees(double dis){
  return dis*to_degrees;
}

//similar helper function for turning
//divided by 2 b/c one wheel needs to do half the work
double disToTurnDeg(double deg){
  return turn_ratio*deg/2;
}


void rotateForCM(double CM, double power, vex::motor Temp, bool end){
  Temp.rotateFor(CM*to_degrees, vex::rotationUnits::deg, power, vex::velocityUnits::pct, end);
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

void moveForCM(double dis, double pow){
  LeftB.rotateFor(disToDegrees(dis), vex::rotationUnits::deg, pow, vex::velocityUnits::pct, false);
  RightB.rotateFor(disToDegrees(dis), vex::rotationUnits::deg, pow, vex::velocityUnits::pct, true);
}

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
//Abandon hope all ye who enter here

void draw_grid(void) { 
    Brain.Screen.setPenColor(color::white);
    
    for (int i = 0; i < 2; i ++) {
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


//I'm too lazy to split up the autonomous into seperate functions
//look at Robot_Code_2.0 for more clarity
void autonomous() {
    // Wait 2 seconds or 2000 milliseconds before starting the program.
    vex::task::sleep( 2000 );
    // Print to the screen that the program has started.
    Brain.Screen.print("User Program has Started.");
  
  switch(atnSel){
  //pick up four cubes, score, red side
  case 1:
    //move to front of cubes
    moveForCM(69.5, 30);

    //rotate intakes for a lot & collect cubes
    rotateForCM(1000, 100, Intk1, false);
    rotateForCM(1000, 100, Intk2, false);
    moveForCM(41.5, 15);  //75 is arbitrary to keep from running over cubes

    Intk1.stop();
    Intk2.stop();

    //Turn to score zones
    turningDeg(150);

    //move to scoring zone
    moveForCM(117, 30);

    //angle to deposit cubes
    rotateForCM(50, 100, Angler, true);

    //move back a little
    moveForCM(-8, 50);

    OhNoStopEverything();
    break;
  //pick up four cubes, score, blue side
  case 2:
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
    moveForCM(117, 100);

    vex::task::sleep(100);
    //angle to deposit cubes
    rotateForCM(50, 100, Angler, true);

    vex::task::sleep(100);
    //move back a little
    moveForCM(-8, 50);

    OhNoStopEverything();
    break;
  //lined up with score zone, push preload into zone, back up
  case 3:
    //push into zone
    rotateForCM(1000, 1, Arm, false);
    rotateForCM(1000, 1, Arm2, false);
    moveForCM(-50, -50);
    vex::task::sleep(500);
    //back up
    moveForCM(30, 70);
    //test below code w/ measurements
    //turn to the right/left (right)
    turningDeg(90);
    //forward and pick up cube
    rotateForCM(1000, 80, Intk1, false);
    rotateForCM(1000, 80, Intk2, false);
    moveForCM(20, 15);
    //turn back towards score (135 deg?)
    turningDeg(135);
    //drive forward a life arms enough
    rotateForCM(1000, 5, Arm, false);
    rotateForCM(1000, 5, Arm2, false);
    moveForCM(100, 50);
    //throw cube and pray that works
    rotateForCM(1000, 0.3, Arm, false); //keep arms relatively stable
    rotateForCM(1000, 0.3, Arm2, false);
    rotateForCM(-1000, -80, Intk1, false);
    rotateForCM(-1000, -80, Intk2, true);
    //move back a little
    moveForCM(-20, -50);
    
    OhNoStopEverything();
    break;
  case 4:
    moveForCM(-10, -50);
    OhNoStopEverything();
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
      //auton switch, for given input it will execute a specific auton
  //autons are on the onenote
  //input distance(cm) to travel * to_degrees to convert to degrees needed to move wheel


    // Print to the brain's screen that the program has ended.
    Brain.Screen.newLine();//Move the cursor to a new line on the screen.
    Brain.Screen.print( "User Program has Ended." );

    // Prevent main from exiting with an infinite loop.                        
    while(1) {
      // Sleep the task for a short amount of time to prevent wasted resources.
    }
}


//this pre auton should almost auto run the auton when selected vs. competition which has to wait for judge
void pre_auton(){
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
                         atnSel=7;                                               //bottom left (no auton yet)
                         break;
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                        atnSel=9;   //bottom right (no auton yet)
                        break;
                } else {                                                //released in middle (left-to-right) third of the screen
                        atnSel=8;//bottom middle (no auton yet)
                        break;
                }
            } else if (Brain.Screen.yPosition() < 80) {             //released in top third of the screen
                if (Brain.Screen.xPosition() < 160) {                   //released in left third of the screen
                    atnSel=1;     //top left
                    break;
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                    atnSel=3;      //top right
                    break;
                } else {                                                //released in middle (left-to-right) third of the screen
                    atnSel=2;    //top middle
                    break;
                }
            } else {                                                //released in middle (top-to-bottom) of the screen
                if (Brain.Screen.xPosition() < 160) {                   //released in left third of the screen
                    atnSel=4;      //middle left
                    break;
                } else if (Brain.Screen.xPosition() > 320) {            //released in right third of the screen
                    atnSel=6;       //middle right
                    break;
                } else {                                                //released in middle (left-to-right) third of the screen
                    atnSel=5;                                            //middle middle
                    break;
                }
            }
            //dt.stop(brakeType::coast); this was a predefined function from the Author but I don't remember for what reason
        } else {
            vex::task::sleep(1);  //was originally 0.1 so might cause some problems
        }

  //return to charted territory
  }
  vex::task::sleep(1000); //after clicking auton wait 1 second to move hand away
  autonomous();
}


int main(){
  pre_auton();

}
