#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
pneumatics mogo = pneumatics(Brain.ThreeWirePort.C);
rotation  rotationSensor = rotation (PORT21, false);
controller controller1 = controller(primary);

motor fl = motor(PORT6, ratio6_1, true);
motor tl = motor(PORT5, ratio6_1, false);
motor bl = motor(PORT8, ratio6_1, true);
motor fr = motor(PORT12, ratio6_1, false);
motor mr = motor(PORT2, ratio6_1, true);
motor br = motor(PORT1, ratio6_1, false);
motor intake = motor(PORT11, ratio6_1, true);
motor intake2 = motor(PORT4, ratio18_1, false);
motor intake3 = motor(PORT7, ratio18_1, true);
motor intake4 = motor(PORT13, ratio18_1, false);
inertial inertialSensor = inertial(PORT3);
optical opticalSensor = optical(PORT16);
pneumatics matchload = pneumatics(Brain.ThreeWirePort.A);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
}