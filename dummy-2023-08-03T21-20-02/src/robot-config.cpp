#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
 
// VEXcode device constructors
motor l1 = motor(PORT8, ratio6_1, true);
motor l2 = motor(PORT9, ratio6_1, true);
motor l3 = motor(PORT10, ratio6_1, true);
motor r1 = motor(PORT3, ratio6_1, false);
motor r2 = motor(PORT4, ratio6_1, false);
motor r3 = motor(PORT5, ratio6_1, false);
inertial inert = inertial(PORT11);


controller Controller1 = controller(primary);
motor Intake = motor(PORT7, ratio18_1, false);
motor cata = motor(PORT21, ratio18_1, true);


digital_out wingR = digital_out(Brain.ThreeWirePort.D);
digital_out wingL = digital_out(Brain.ThreeWirePort.E);
digital_out bwing = digital_out(Brain.ThreeWirePort.G);

digital_out endgame = digital_out(Brain.ThreeWirePort.C);
digital_out lift = digital_out(Brain.ThreeWirePort.F);



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