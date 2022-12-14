#include "vex.h"
#include <cmath>

template <typename MOTOR>

void spin (MOTOR name, int power = 100) {
  name.spin(directionType::fwd, power, velocityUnits::pct);
}

void spinRoller(int power, int time) {
  spin(intake_roller, power);
  task::sleep(time);
  intake_roller.stop();
}

void lowerCatapult() {
  do {
    spin(catapult);
  } while(!catapult_limit.pressing());
  catapult.stop();
  catapult.setBrake(brakeType::hold);
}

void move(int power, int time, int roller_power = 0) {
  spin(chassis_left, power);
  spin(chassis_right, power);
  spin(intake_roller, roller_power);
  task::sleep(time);
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
}

void turn(int power, int time, int roller_power = 0) {
  spin(chassis_left, power);
  spin(chassis_right, -power);
  spin(intake_roller, roller_power);
  task::sleep(time);
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
}

void catapultShoot() {
  catapult.resetRotation();
  do {
    catapult.setBrake(brakeType::undefined);
    spin(catapult);
  } while (catapult.rotation(rotationUnits::deg) < 100 || !catapult_limit.pressing());
  catapult.stop();
  catapult.setBrake(brakeType::hold);
}

void stringMech() {
  string_mech.open();
}

void skill() {

}

void bottomAuton() {
  lowerCatapult();
  // roller
  move(30, 200, -100);
  move(-30, 150);
  // align to a disk
  turn(30, 650);
  // intake disk
  move(20, 350, 100);
  spinRoller(100, 500);
  // rough angle adjustment
  move(-20, 350, 100);
  turn(-30, 200);
  task::sleep(100);
  // precise angle adjustment
  move(-30, 200);
  turn(-30, 100);
  // shoot disk
  catapultShoot();
  spin(catapult, 90);
  // align for match load
  move(-30, 1100);
  task::sleep(100);
  turn(30, 450);
  move(-20, 550);
  task::sleep(100);
  lowerCatapult();
  // input match loads
  task::sleep(2000);
  // align to a goal (2nd)
  move(30, 300);
  turn(-30, 500);
  // shoot disk (2nd)
  catapultShoot();
  // align for match loads (2nd)
  turn(30, 400);
  move(-30, 500);
  lowerCatapult();
  spinRoller(100, 500);
  // align to goal
  move(30, 300);
  turn(-30, 500);
  task::sleep(200);
  // shoot disk (3rd)
  catapultShoot();
}

void winPointSideAuton() {
  // roller
  move(30, 200, -100);
  move(-30, 150);
  // move towards the center of the field
  turn(-30, 200);
  move(-40, 1900);
  // align to high goal
  turn(30, 415);
  move(-30, 340);
  task::sleep(500);
  catapultShoot();
  // align to the wall
  move(30, 150);
  turn(-30, 570);
  lowerCatapult();
  // hit the wall
  move(-50, 1000, 100);
  task::sleep(100); 
  turn(-30, 530, 100);
  task::sleep(100); 
  move(30, 1400, 100);
  task::sleep(100);  
  turn(-30, 420, 100);
  task::sleep(100); 
  move(30, 800, -100);
  task::sleep(100);
  move(-30, 300, -100);
  task::sleep(100);
}

void sideAuton() {

}

void preventError() {
  chassis_left.stop();
  chassis_right.stop();
  intake_roller.stop();
  catapult.stop();
}

int auton_counter = 3;

void auton_ctrl() {
  switch (auton_counter) {
    case 0: skill(); break;
    case 1: bottomAuton(); break;
    case 2: sideAuton(); break;
    case 3: winPointSideAuton(); break;
    default: preventError();
  }
}