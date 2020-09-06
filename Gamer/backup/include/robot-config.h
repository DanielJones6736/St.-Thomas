using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Arm1;
extern motor Arm2;
extern motor lifter;
extern motor Suck1;
extern motor Suck2;
extern motor Left;
extern motor Right;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );