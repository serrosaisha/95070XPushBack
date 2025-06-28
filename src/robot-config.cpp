#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
pneumatics mogo = pneumatics(Brain.ThreeWirePort.C);
rotation  rotationSensor = rotation (PORT21, false);
controller controller1 = controller(primary);

motor fl = motor(PORT1, ratio6_1, true);
motor tl = motor(PORT2, ratio6_1, false);
motor bl = motor(PORT3, ratio6_1, true);
motor fr = motor(PORT4, ratio6_1, false);
motor mr = motor(PORT5, ratio6_1, false);
motor br = motor(PORT6, ratio6_1, true);
motor intake = motor(PORT7, ratio6_1, true);
motor intake2 = motor(PORT8, ratio18_1, false);
motor intake3 = motor(PORT9, ratio18_1, false);
inertial inertialSensor = inertial(PORT18);
optical opticalSensor = optical(PORT16);
pneumatics matchload = pneumatics(Brain.ThreeWirePort.H);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
}