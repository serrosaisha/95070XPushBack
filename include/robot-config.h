using namespace vex;


// VEXcode devices
extern brain Brain;
extern controller controller1;
extern motor fr;
extern motor fl;
extern motor ml;
extern motor mr;
extern motor bl;
extern motor br;
extern motor intake;
extern motor intake2;
extern inertial inertialSensor;
extern rotation rotationSensor;
extern optical opticalSensor;


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );