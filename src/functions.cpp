#include "vex.h"
#include "functions.hpp"
#include <string>
#include <cmath>
#include "autons.hpp"

using namespace vex;
using namespace std;
using namespace chrono;

bool loadingtrue = false;
bool prevloading = false;


steady_clock::time_point lastloading;

double tkp = 0.36; //0.5
double tki = 0.0; //.7
double tkd = 0.0; //0.5x

// #define INCHES_TO_DEGREES 90/5

void arcade() {
    float throttle = 0.9*(controller(primary).Axis3.value());
    float turn = 0.5*(controller(primary).Axis1.value());
    controller1.Screen.setCursor(1,1);
    controller1.Screen.print(throttle);
    controller1.Screen.setCursor(2,1);
    controller1.Screen.print(turn);
    fl.spin(fwd, (throttle+turn), pct);
    tl.spin(fwd, (throttle+turn), pct);
    bl.spin(fwd, (throttle+turn), pct);
    fr.spin(fwd, (throttle-turn), pct);
    mr.spin(fwd, (throttle-turn), pct);
    br.spin(fwd, (throttle-turn), pct);
   }

void pidfb(double targetDistance, int timeout) {
  double kp = 0.09; //0.09
  double ki = 0;//0
  double kd = 0.15;//0.15

  fl.setPosition(0, degrees);
  tl.setPosition(0, degrees);
  bl.setPosition(0, degrees);
  fr.setPosition(0, degrees);
  mr.setPosition(0, degrees);
  br.setPosition(0, degrees);

  double error = targetDistance;
  double integral = 0;
  double lastError =  targetDistance;
  double prevDistanceError = fl.position(degrees);
  int exitCount = 0;

  int previous = time(NULL);

  while (true) {
    //double measureDistance = (fl.position(degrees) + fr.position(degrees))/2;
    double measureDistance = (fl.position(degrees) + tl.position(degrees) + bl.position(degrees) + fr.position(degrees) + mr.position(degrees) + br.position(degrees)) / 6.0;
    
    //int current = Brain.timer(msec);
    //if (Brain.timer(msec) - current > timeout)
    int current = time(NULL); 
    if (current - previous > timeout) {
      break;
    }
    error = targetDistance - measureDistance;
    prevDistanceError = measureDistance;
    if (fabs(error)<5) exitCount++; // used to be 10
    else exitCount = 0;

    if(exitCount > 10) { // braking used to be commented out
      break;
    }

    if (fabs(error) < 100) integral += error;

    double speed = error * kp + integral * ki + (error - lastError) * kd; // the error - lastError is derivative
    fl.spin(fwd, speed, percent);
    tl.spin(fwd, speed, percent);
    bl.spin(fwd, speed, percent);
 
    fr.spin(fwd, speed, percent);
    mr.spin(fwd, speed, percent);
    br.spin(fwd, speed, percent);
 
    lastError = error;
    wait(15, msec);
  }
  fl.stop(brake);
  tl.stop(brake);
  bl.stop(brake);
  fr.stop(brake);
  mr.stop(brake);
  br.stop(brake);
 }

 #define INCHES_TO_DEGREES (4.0/3.0)*360.0/(M_PI * 3.25)
 void pidinches (double DistanceInInches) {
  double degrees = DistanceInInches * INCHES_TO_DEGREES;
  pidfb(degrees, 5);
 }

void pidT(double targetAngle) {
 double error = targetAngle;
 double integral = 0;
 double lastError =  targetAngle;
//  double prevDistanceError = fl.position(degrees);
//  inertialSensor.setRotation(0, degrees);

 while (true) {
  //  double measureDistance = (fl.position(degrees) + fr.position(degrees))/2;
   error = targetAngle - inertialSensor.rotation(deg);
  //  prevDistanceError = measureDistance;
  while (error > 180) error -= 360;
  while (error < -180) error += 360;
   if (fabs(error)<2) {
     fl.stop(brake);
     tl.stop(brake);
     bl.stop(brake);

     fr.stop(brake);
     mr.stop(brake);
     br.stop(brake);
     return;
   }

   if(error < 2) integral += error;
  
   double speed = error * tkp + integral * tki + (error - lastError) * tkd;
   fl.spin(fwd, speed, percent);
   tl.spin(fwd, speed, percent);
   bl.spin(fwd, speed, percent);

   fr.spin(vex::reverse, speed, percent); 
   mr.spin(vex::reverse, speed, percent);
   br.spin(vex::reverse, speed, percent);

   controller1.Screen.setCursor(1,1);
   controller1.Screen.print(error);

   lastError = error;
   wait(20, msec);
 }
}

void old_arcade() {
    //Slower
    // int speedleft = controller1.Axis1.value()/2;
    // int speedright = controller1.Axis3.value()/2;
    // search up the ebot pilons turning curves(or something like that) desmos
    
    std::cout << "confirm" << std::endl;
    
    double speedleft = controller1.Axis1.value() * 0.7 + controller1.Axis3.value();
    double speedright = controller1.Axis1.value() * 0.62 - controller1.Axis3.value();
    
    fl.spin(vex::forward, speedleft, percent);
    tl.spin(vex::forward, speedleft, percent);
    bl.spin(vex::forward, speedleft, percent);
    
    // RIGHT MOTORS ARE vex::reverseD SO vex::forward = vex::reverse!!!!!!!!!
    fr.spin(vex::reverse, speedright, percent);
    mr.spin(vex::reverse, speedright, percent);
    br.spin(vex::reverse, speedright, percent);
    }

void intaking() {
 if (controller1.ButtonR1.pressing()) { //storage area
  intake.spin(vex::reverse, 80, pct);
  intake2.spin(vex::reverse, 80, pct);
  intake3.spin(vex::reverse, 80, pct);
 //  intake2.spin(vex::reverse, 90, percent);
} else if (controller1.ButtonR2.pressing()) { //scoring high goal
  intake.spin(vex::reverse, 80, pct);
  intake2.spin(vex::forward, 80, pct);
  intake3.spin(vex::forward, 40, pct);
  intake4.spin(vex::forward, 80, pct);
} else if (controller1.ButtonL1.pressing()) { //low middle goal scoring
  intake.spin(vex::forward, 80, pct);
  intake2.spin(vex::forward, 80, pct);
  intake3.spin(vex::forward, 80, pct);
} else if (controller1.ButtonL2.pressing()) { //low middle goal scoring
  intake.spin(vex::reverse, 70, pct);
  intake2.spin(vex::forward, 80, pct);
  intake3.spin(vex::forward, 80, pct);
  intake4.spin(vex::reverse, 70, pct);
}
else {
  intake.stop(coast);
  intake2.stop(coast);
  intake3.stop(coast);
  intake4.stop(coast);
 //  intake2.stop(coast);
}
} 

void intakeForStorage() { // storage
  intake.spin(vex::reverse, 80, pct);
  intake2.spin(vex::reverse, 80, pct);
  intake3.spin(vex::reverse, 80, pct);
 }

 void outakeForLongGoal() { //long goal
  intake.spin(vex::reverse, 80, pct);
  intake2.spin(vex::forward, 80, pct);
  intake3.spin(vex::forward, 80, pct);
 }
 
 void outtakeForShortMiddle() { //lowest middle goal
  intake.spin(vex::forward, 80, pct);
  intake2.spin(vex::forward, 80, pct);
  intake3.spin(vex::forward, 80, pct);
 }

 void loadingcontrol() {
  if (loadingtrue) {
   matchload.set(false);
  } else {
   matchload.set(true);
  }
 }

 void loading() {
  auto now = steady_clock::now();
  auto durLastClamp = duration_cast<milliseconds>(now-lastloading).count();
  if (durLastClamp > 200) {
    loadingcontrol();
    loadingtrue = !loadingtrue;
    lastloading = now;
  }
 }
 
int auton = 1;

 void autonselector() {
  int numofautons = 1;
  if (controller1.ButtonA.pressing()) {
    auton++;
    wait(200,msec);
  } else if (controller1.ButtonY.pressing()) {
    auton--;
    wait(200,msec);
  }
  if (auton > numofautons) {
    auton = 1;
  } else if (auton < 1) {
    auton = numofautons;
  }
 
  if (auton == 1) {
    controller1.Screen.clearScreen();
    controller1.Screen.setCursor(2,9);
    controller1.Screen.print("Left");
  } 
 }

 void autonomous() {
  if (auton == 1) {
    auton1();
  }
 }

 void stopIntaking() {
  intake.stop(coast);
  intake2.stop(coast);
  intake3.stop(coast);
  //intake2.stop(coast);
 }
 
 // auton
 
 

   


   
