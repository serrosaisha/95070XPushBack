#include "vex.h"
#include "autons.hpp"
#include "functions.hpp"

#include <string>
#include <cmath>

using namespace vex;
using namespace std;
using namespace chrono;

void auton1() { 
    pidinches(10);
    pidT(270);
    wait(2, sec);
    pidT(360);
}

