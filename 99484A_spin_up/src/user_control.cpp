#include "vex.h"
#include <cmath>
#include <iostream>
#include <chrono>

/* CONTROLS
  Axis1 - turn chassis
  Axis3 - chassis forward / backward
  L1 - Catapult
  X - reverse drive
  R1 - intake
  A - catapult adjust
  Down - outtake
  B - string mech
*/

int intake_power_intake = 100; // intake power
int intake_power_roller = 50; // roller power
int catapult_power = 100;
double forward_power = 0.5; // power multiplier when chassis moving forward / backward
double turn_power = 0.5; // power multiplier when chassis turning / spinning

// ignore from here
int power_sign = 1;
int left_power = 0;
int right_power = 0;
int intake_power = 0;
bool flip_control = false;
bool catapult_activated = false;
bool double_check_catapult = false;
int catapult_pressed_count = 0;

auto start = std::chrono::high_resolution_clock::now();
auto end = std::chrono::high_resolution_clock::now();

template <typename MOTOR>

void spin (MOTOR name, int power = 100) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

void bumper_based_catapult_ctrl() {
  if (ctrl.ButtonL1.pressing() && !catapult_activated) {
    catapult.resetRotation();
    catapult_activated = true;
    power_sign = 1;
  }
  if (catapult_activated) {
    if (!double_check_catapult) {
      spin(catapult);
      start = std::chrono::high_resolution_clock::now();
      double_check_catapult = true;
    }
    else end = std::chrono::high_resolution_clock::now();
  }
  int duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  if (duration > 100 && catapult_limit.pressing() && double_check_catapult) {
    catapult.stop();
    catapult.setBrake(brakeType::hold); 
    catapult_activated = false;
    double_check_catapult = false;
  }
}

void catapult_manual(){
  if (ctrl.ButtonA.pressing() || catapult_activated) spin(catapult);
  else catapult.stop();
}

void intake_roller_ctrl() {
  //intake
  if (ctrl.ButtonR1.pressing()) spin(intake_roller, 90);
  //outtake
  else if (ctrl.ButtonDown.pressing()) spin(intake_roller, -100);
  else intake_roller.stop();
}

void reverse_driver_ctrl() {
  if (ctrl.ButtonL2.pressing() && !flip_control) {
    flip_control = true;
    power_sign *= -1;
  }
  if (!ctrl.ButtonL2.pressing()) flip_control = false;
}

bool toggleRoller = false;
int rollerPower = 100;

void skillRoller() {
  if (ctrl.ButtonR1.pressing() || ctrl.ButtonDown.pressing()) return;
  if (!toggleRoller && (ctrl.ButtonR2.pressing() || ctrl.ButtonL2.pressing())) {
    intake_roller.resetRotation();
    toggleRoller = true;
  }
  else if (std::abs(intake_roller.rotation(rotationUnits::raw)) < 300 && toggleRoller) spin(intake_roller, 100);
  else if (!ctrl.ButtonR2.pressing() && !ctrl.ButtonL2.pressing()){
    toggleRoller = false;
    intake_roller.stop();
  }
}

void split_arcade_ctrl() {
  left_power = (ctrl.Axis3.value() * forward_power * power_sign) + ctrl.Axis1.value() * turn_power;
  right_power = (ctrl.Axis3.value() * forward_power * power_sign) - ctrl.Axis1.value() * turn_power;
  spin(chassis_left, left_power);
  spin(chassis_right, right_power);
}

void rope_shooting_stuff() {
  if (ctrl.ButtonB.pressing()) string_mech.open();
  else string_mech.close();
}

void user_ctrl() {
  while (true) {
    reverse_driver_ctrl();
    bumper_based_catapult_ctrl();
    catapult_manual();
    split_arcade_ctrl();
    intake_roller_ctrl();
    rope_shooting_stuff();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(catapult_limit.pressing());
    vex::task::sleep(20); // break for the bot
  }
}