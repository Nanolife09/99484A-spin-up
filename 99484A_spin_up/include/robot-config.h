using namespace vex;

extern brain Brain;

extern controller ctrl;

extern motor catapult;
extern motor chassis_left_front;
extern motor chassis_left_middle;
extern motor chassis_left_back;
extern motor chassis_right_front;
extern motor chassis_right_middle;
extern motor chassis_right_back;
extern motor intake_roller;
extern bumper catapult_limit;
extern pneumatics string_mech;

extern motor_group chassis_right;
extern motor_group chassis_left;

extern competition Competition;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
