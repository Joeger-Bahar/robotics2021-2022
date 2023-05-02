#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

limit LimitSwitch = limit(Brain.ThreeWirePort.A);

digital_out Expansion1 = digital_out(Brain.ThreeWirePort.B);

distance Distance = distance(PORT1);
inertial Inertial = inertial(PORT4);
rotation Rotation = rotation(PORT10);

motor Catapult = motor(PORT6, ratio18_1, true);
motor Intake = motor(PORT2, ratio18_1, false);

motor FL(PORT20, ratio18_1, true);  /*forward is forward*/
motor FR = motor(PORT16, ratio18_1, false);
motor ML = motor(PORT15, ratio18_1, true);
motor MR = motor(PORT12, ratio18_1, false);
motor BL = motor(PORT18, ratio18_1, true);
motor BR = motor(PORT17, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}