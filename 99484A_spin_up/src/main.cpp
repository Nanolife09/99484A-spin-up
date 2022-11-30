#include "vex.h"
#include "user_control.h"
#include "auton.h"

using namespace vex;

void stopAll() {
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
  catapult.stop();
}

int main() {
  // Initializing Robot Configuration DO NOT REMOVE!
  vexcodeInit();
  Competition.drivercontrol(user_ctrl);
  Competition.autonomous(auton_ctrl);
  //Competition.drivercontrol(stopAll);
}