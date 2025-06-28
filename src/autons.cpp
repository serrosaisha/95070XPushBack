#include "vex.h"
#include "autons.hpp"
#include "functions.hpp"

#include <string>
#include <cmath>

using namespace vex;
using namespace std;
using namespace chrono;

void auton1() { 
    intakeForStorage();
    pidinches(27);
    wait(1, sec);
    pidT(-10);
    pidinches(2);
    wait(1, sec);
    stopIntaking();
    pidinches(-13);
    pidT(272);
    pidinches(15);
    pidT(3);
    pidinches(7);
    outakeForLongGoal();
}

