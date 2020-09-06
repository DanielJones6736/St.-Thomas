
#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*
for JV robot
motor Arm1 = motor(PORT1, ratio18_1, false);
motor Arm2 = motor(PORT10, ratio18_1, false);
motor lifter1 = motor(PORT2, ratio18_1, false);
motor lifter2 = motor(PORT7, ratio18_1, false);
motor Suck1 = motor(PORT3, ratio18_1, false);
motor Suck2 = motor(PORT4, ratio18_1, false);
motor Left = motor(PORT5, ratio18_1, false);
motor Right = motor(PORT6, ratio18_1, false);
*/
//for Varsity robot
motor Arm1 = motor(PORT10, ratio18_1, true);
motor Arm2 = motor(PORT9, ratio18_1, false);
motor lifter1 = motor(PORT1, ratio18_1, true);
motor lifter2 = motor(PORT15, ratio18_1, false);
motor Suck1 = motor(PORT4, ratio18_1, false);
motor Suck2 = motor(PORT5, ratio18_1, false);
motor Left = motor(PORT11, ratio18_1, false);
motor Right = motor(PORT20, ratio18_1, true);
controller Controller1 = controller();

// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool Controller1XBButtonsControlMotorsStopped = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_callback_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    // check the ButtonL1/ButtonL2 status to control Suck1
    Left.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
    Right.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
    
    
    
    
    if (Controller1.ButtonL1.pressing()) {
      Suck1.spin(fwd, 100, vex::velocityUnits::pct);
      Suck2.spin(fwd, 100, vex::velocityUnits::pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      Suck1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      Suck2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      Controller1LeftShoulderControlMotorsStopped = false;
    } else if (!Controller1LeftShoulderControlMotorsStopped) {
      Suck1.stop();
      Suck2.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1LeftShoulderControlMotorsStopped = true;
    }
    // check the ButtonR1/ButtonR2 status to control Arm1
    if (Controller1.ButtonR1.pressing()) {
      Arm1.spin(fwd, 100, vex::velocityUnits::pct);
      Arm2.spin(fwd, 100, vex::velocityUnits::pct);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      Arm1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      Arm2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      Controller1RightShoulderControlMotorsStopped = false;
    } else if (!Controller1RightShoulderControlMotorsStopped) {
      Arm1.spin(fwd, 100, vex::velocityUnits::pct);
      Arm2.spin(fwd, 100, vex::velocityUnits::pct);
      
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1RightShoulderControlMotorsStopped = true;
    }
    // check the X/B buttons status to control lifter
    if (Controller1.ButtonX.pressing()) {
      lifter1.spin(fwd, 100, vex::velocityUnits::pct);
      lifter2.spin(fwd, 100, vex::velocityUnits::pct);
      Controller1XBButtonsControlMotorsStopped = false;
    } else if (Controller1.ButtonB.pressing()) {
      lifter1.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      lifter2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      Controller1XBButtonsControlMotorsStopped = false;
    } else if (!Controller1XBButtonsControlMotorsStopped){
      lifter1.stop();
      lifter2.stop();
      Controller1XBButtonsControlMotorsStopped = true;
    }
    // wait before repeating the process
    vex::task::sleep(20);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_callback_Controller1);
}