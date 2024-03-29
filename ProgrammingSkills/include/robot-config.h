using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;

extern limit LimitSwitch;

extern inertial Inertial;
extern distance Distance;
extern rotation Rotation;

extern digital_out Expansion1;

extern motor Catapult;
extern motor Intake;
extern motor FL;
extern motor FR;
extern motor ML;
extern motor MR;
extern motor BL;
extern motor BR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );