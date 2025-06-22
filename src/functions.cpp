#include "vex.h"
#include "functions.hpp"
#include <string>
#include <cmath>

using namespace vex;
using namespace std;
using namespace chrono;

double tkp = 0.5;
double tki = 0.7;
double tkd = 0.5;

double kp = 0.175;
double ki = 0;
double kd = 0;

#define INCHES_TO_DEGREES 90/5

void arcade() {
    float throttle = (controller(primary).Axis3.value());
    float turn = (controller(primary).Axis1.value());
    fl.spin(fwd, (throttle+turn), pct);
    ml.spin(fwd, (throttle+turn), pct);
    bl.spin(fwd, (throttle+turn), pct);
    fr.spin(fwd, (throttle-turn), pct);
    mr.spin(fwd, (throttle-turn), pct);
    br.spin(fwd, (throttle-turn), pct);
   }

void pidfb(double targetDistance, int timeout) {
  double error = targetDistance;
  double integral = 0;
  double lastError =  targetDistance;
  double prevDistanceError = fl.position(degrees);

  int previous = time(NULL);
  fl.setPosition(0, degrees);
  ml.setPosition(0, degrees);
  bl.setPosition(0, degrees);
  fr.setPosition(0, degrees);
  mr.setPosition(0, degrees);
  br.setPosition(0, degrees);
  while (true) {
    double measureDistance = (fl.position(degrees) + fr.position(degrees))/2;
    int current = time(NULL);
    if (current - previous > timeout) {
      return;
    }
    error = targetDistance - measureDistance;
    prevDistanceError = measureDistance;
    if (fabs(error)<30) {
      fl.stop(brake);
      ml.stop(brake);
      bl.stop(brake);
 
      fr.stop(brake);
      mr.stop(brake);
      br.stop(brake);
      return;
    }
   
    double speed = error * kp + integral * ki + (error - lastError) * kd;
    fl.spin(fwd, speed, percent);
    ml.spin(fwd, speed, percent);
    bl.spin(fwd, speed, percent);
 
    fr.spin(fwd, speed, percent);
    mr.spin(fwd, speed, percent);
    br.spin(fwd, speed, percent);
 
    lastError = error;
    wait(15, msec);
  }
 }

// PID to inches
void pidinches (double DistanceInInches) {
 double degrees = DistanceInInches * INCHES_TO_DEGREES;
 pidfb(degrees, 1);
}

void pidT(double targetAngle) {
 double error = targetAngle;
 double integral = 0;
 double lastError =  targetAngle;
//  double prevDistanceError = fl.position(degrees);
//  inertialSensor.setRotation(0, degrees);
 fl.setPosition(0, degrees);
 ml.setPosition(0, degrees);
 bl.setPosition(0, degrees);
 fr.setPosition(0, degrees);
 mr.setPosition(0, degrees);
 br.setPosition(0, degrees);
 while (true) {
  //  double measureDistance = (fl.position(degrees) + fr.position(degrees))/2;
   error = targetAngle - inertialSensor.rotation(deg);
  //  prevDistanceError = measureDistance;
  while (error > 180) error -= 360;
  while (error < -180) error += 360;
   if (fabs(error)<2) {
     fl.stop(brake);
     ml.stop(brake);
     bl.stop(brake);

     fr.stop(brake);
     mr.stop(brake);
     br.stop(brake);
     return;
   }
  
   double speed = error * tkp + integral * tki + (error - lastError) * tkd;
   fl.spin(fwd, speed, percent);
   ml.spin(fwd, speed, percent);
   bl.spin(fwd, speed, percent);

   fr.spin(vex::reverse, speed, percent);
   mr.spin(vex::reverse, speed, percent);
   br.spin(vex::reverse, speed, percent);

  //  Brain.Screen.print(inertialSensor.angle(degrees));

   lastError = error;
   wait(20, msec);
 }
}


   


   
