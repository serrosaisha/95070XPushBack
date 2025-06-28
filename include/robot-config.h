using namespace vex;


// VEXcode devices
extern brain Brain;
extern controller controller1;
extern motor fr;
extern motor fl;
extern motor tl;
extern motor mr;
extern motor bl;
extern motor br;
extern motor intake;
extern motor intake2;
extern motor intake3;
extern inertial inertialSensor;
extern rotation rotationSensor;
extern optical opticalSensor;
extern pneumatics matchload;




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );