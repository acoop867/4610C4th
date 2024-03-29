using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor l1;
extern motor l2;
extern motor l3;
extern motor r1;
extern motor r2;
extern motor r3;
extern motor cata2;
extern bumper selector;
extern inertial inert;


extern controller Controller1;
extern motor Intake;
extern motor cata;
extern optical di;

extern digital_out wingR;
extern digital_out wingL;
extern digital_out bwing;
extern digital_out bwingl;
extern digital_out release;
extern digital_out pto;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );