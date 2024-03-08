#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
 
// VEXcode device constructors
motor l1 = motor(PORT8, ratio6_1, true);
motor l2 = motor(PORT9, ratio6_1, true);
motor l3 = motor(PORT12, ratio6_1, true);
motor r1 = motor(PORT3, ratio6_1, false);
motor r2 = motor(PORT4, ratio6_1, false);
motor r3 = motor(PORT5, ratio6_1, false);
inertial inert = inertial(PORT15);
bumper selector = bumper(Brain.ThreeWirePort.A);

controller Controller1 = controller(primary);
motor Intake = motor(PORT20, ratio18_1, false);
motor cata = motor(PORT19, ratio18_1, true);
motor cata2 = motor(PORT16,ratio18_1);


digital_out wingR = digital_out(Brain.ThreeWirePort.D);
digital_out wingL = digital_out(Brain.ThreeWirePort.C);
digital_out bwing = digital_out(Brain.ThreeWirePort.F);
digital_out bwingl = digital_out(Brain.ThreeWirePort.G);
digital_out pto = digital_out(Brain.ThreeWirePort.E);
digital_out release = digital_out(Brain.ThreeWirePort.B);
optical di= optical(PORT21);


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