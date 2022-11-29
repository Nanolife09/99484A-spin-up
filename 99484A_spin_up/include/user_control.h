#include "vex.h"

#ifndef USER_CONTROL

#define User_CONTROL

extern void catapult_ctrl();
extern void user_ctrl();
extern void spin(motor name, int power = 100);
extern void spin(motor_group name, int power = 100);

#endif