#include "vex.h"
#include "functions.hpp"
#include <string>
#include <cmath>

using namespace vex;
using namespace std;
using namespace chrono;

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


   
