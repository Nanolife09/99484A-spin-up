#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen

brain Brain;

competition Competition;

controller ctrl;

triport ThreeWirePort (PORT22);
// motor     name          (PORT_number, reverse?);
motor chassis_left_middle  (PORT11, true);
motor chassis_left_front   (PORT12, true);
motor intake_roller        (PORT13, false);
motor chassis_left_back    (PORT15, false);
motor chassis_right_front  (PORT16, false);
motor chassis_right_back   (PORT18, true);
motor chassis_right_middle (PORT17, false);
motor catapult             (PORT20, true);
bumper catapult_limit      (ThreeWirePort.H);
pneumatics string_mech      (ThreeWirePort.A);

motor_group chassis_left (chassis_left_back, chassis_left_front, chassis_left_middle);
motor_group chassis_right (chassis_right_back, chassis_right_front, chassis_right_middle); 

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}