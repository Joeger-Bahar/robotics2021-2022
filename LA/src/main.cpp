/*---------------------------------------------------------------------------------*/
/*                                                                                 */
/*  Module:       main.cpp                                                         */
/*  Author:       Joshua Bahr                                                      */
/*  Created:      Thu Oct 27 2022                                                  */
/*  Description:  Code for a tank drive robot with customizations including aimbot */
/*                                                                                 */
/*---------------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial             inertial      3
// Controller1          controller
// FL                   motor         20
// FR                   motor         10
// BR                   motor         1
// BL                   motor         11
// ---- END VEXCODE CONFIGURED DEVICES ----

#include <iostream>
#include <string.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <cmath>
#include <map>
#include "Vision.h"
#include "vex.h"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

void Calibrate() {
  Inertial.calibrate();
  while (Inertial.isCalibrating()) {
    wait(20, msec);
  }
}

bool intakeAllowed = 1;

void idk() {
  Catapult.stop();
  intakeAllowed = 1;
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  LimitSwitch.pressed(idk);//[]() {
  //     // Catapult.stop();
      // Catapult.spinFor(fwd, 0.15, rev);
  //     intakeAllowed = 1;
//  });
  // Calibrate();
  Brain.Screen.setOrigin(240, 125);
  Catapult.setVelocity(100, pct);
  Controller1.Screen.clearScreen();
}

void redLight() {
  FL.setBrake(brake);
  FR.setBrake(brake);
  ML.setBrake(brake);
  MR.setBrake(brake);
  BL.setBrake(brake);
  BR.setBrake(brake);
}
void greenLight() {
  FL.setBrake(coast);
  FR.setBrake(coast);
  ML.setBrake(coast);
  MR.setBrake(coast);
  BL.setBrake(coast);
  BR.setBrake(coast);
}
void Brake() {
  redLight();
  greenLight();
}

void Forward(const double inches, const bool wait = true, const double speed = 60,
             const double timeOut = 100.0) {
  const double Distance = (360 / 12.56) * inches;

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  ML.setVelocity(speed, pct);
  MR.setVelocity(speed, pct);
  BL.setVelocity(speed, pct);
  BR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  ML.setTimeout(timeOut, sec);
  MR.setTimeout(timeOut, sec);
  BL.setTimeout(timeOut, sec);
  BR.setTimeout(timeOut, sec);

  if (!wait) {
    FL.spinFor(fwd, Distance, degrees, false);
    FR.spinFor(fwd, Distance, degrees, false);
    ML.spinFor(fwd, Distance, degrees, false);
    MR.spinFor(fwd, Distance, degrees, false);
    BL.spinFor(fwd, Distance, degrees, false);
    BR.spinFor(fwd, Distance, degrees, false);
  } else {
    FL.spinFor(fwd, Distance, degrees, false);
    FR.spinFor(fwd, Distance, degrees, false);
    ML.spinFor(fwd, Distance, degrees, false);
    MR.spinFor(fwd, Distance, degrees, false);
    BL.spinFor(fwd, Distance, degrees, false);
    BR.spinFor(fwd, Distance, degrees);
  }
}
void Back(const double inches, const bool wait = true, const double speed = 60,
             const double timeOut = 100.0) {
  const double Distance = (360 / 12.56) * inches;

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  ML.setVelocity(speed, pct);
  MR.setVelocity(speed, pct);
  BL.setVelocity(speed, pct);
  BR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  ML.setTimeout(timeOut, sec);
  MR.setTimeout(timeOut, sec);
  BL.setTimeout(timeOut, sec);
  BR.setTimeout(timeOut, sec);

  if (!wait) {
    FL.spinFor(vex::reverse, Distance, degrees, false);
    FR.spinFor(vex::reverse, Distance, degrees, false);
    ML.spinFor(vex::reverse, Distance, degrees, false);
    MR.spinFor(vex::reverse, Distance, degrees, false);
    BL.spinFor(vex::reverse, Distance, degrees, false);
    BR.spinFor(vex::reverse, Distance, degrees, false);
  } else {
    FL.spinFor(vex::reverse, Distance, degrees, false);
    FR.spinFor(vex::reverse, Distance, degrees, false);
    ML.spinFor(vex::reverse, Distance, degrees, false);
    MR.spinFor(vex::reverse, Distance, degrees, false);
    BL.spinFor(vex::reverse, Distance, degrees, false);
    BR.spinFor(vex::reverse, Distance, degrees);
  }
}
void Left(const double inches, const double speed = 20,
          const double timeOut = 100.0) {
  // double Distance = ((360 / 12.56) * inches) * 0.086;
  double x = Inertial.angle();
  double y = x - inches;
  if (y > 360) {
    y -= 360;
  }
  if (y < 0) {
    y += 360;
  }

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  ML.setVelocity(speed, pct);
  MR.setVelocity(speed, pct);
  BL.setVelocity(speed, pct);
  BR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  ML.setTimeout(timeOut, sec);
  MR.setTimeout(timeOut, sec);
  BL.setTimeout(timeOut, sec);
  BR.setTimeout(timeOut, sec);

  FL.spinFor(vex::reverse, 500, rev, false);
  FR.spinFor(fwd, 500, rev, false);
  ML.spinFor(vex::reverse, 500, rev, false);
  MR.spinFor(fwd, 500, rev, false);
  BL.spinFor(vex::reverse, 500, rev, false);
  BR.spinFor(fwd, 500, rev, false);

  while (1) {
    if (round(Inertial.angle()) == round(y)) {
      Brake();
      break;
    }
  }
}
void Right(const double inches, const double speed = 20,
           const double timeOut = 100.0) {
  double x = Inertial.angle();
  double y = x + inches;
  if (y > 360) {
    y -= 360;
  }
  if (y < 0) {
    y += 360;
  }

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  ML.setVelocity(speed, pct);
  MR.setVelocity(speed, pct);
  BL.setVelocity(speed, pct);
  BR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  ML.setTimeout(timeOut, sec);
  MR.setTimeout(timeOut, sec);
  BL.setTimeout(timeOut, sec);
  BR.setTimeout(timeOut, sec);

  FL.spinFor(fwd, 500, rev, false);
  FR.spinFor(vex::reverse, 500, rev, false);
  ML.spinFor(fwd, 500, rev, false);
  MR.spinFor(vex::reverse, 500, rev, false);
  BL.spinFor(fwd, 500, rev, false);
  BR.spinFor(vex::reverse, 500, rev, false);

  while (1) {
    if (round(Inertial.angle()) == round(y)) {
      Brake();
      break;
    }
  }
}

void ToLeft(const double degree, const double Speed, const double Timeout = 100.0) {
  FL.setVelocity(Speed, pct);
  FR.setVelocity(Speed, pct);
  ML.setVelocity(Speed, pct);
  MR.setVelocity(Speed, pct);
  BL.setVelocity(Speed, pct);
  BR.setVelocity(Speed, pct);
  FL.setTimeout(Timeout, sec);
  FR.setTimeout(Timeout, sec);
  ML.setTimeout(Timeout, sec);
  MR.setTimeout(Timeout, sec);
  BL.setTimeout(Timeout, sec);
  BR.setTimeout(Timeout, sec);

  FL.spinFor(vex::reverse, 500, rev, false);
  FR.spinFor(fwd, 500, rev, false);
  ML.spinFor(vex::reverse, 500, rev, false);
  MR.spinFor(fwd, 500, rev, false);
  BL.spinFor(vex::reverse, 500, rev, false);
  BR.spinFor(fwd, 500, rev, false);

  while (round(Inertial.angle()) < round(degree) - 1 || Inertial.angle() > round(degree) + 1) {}
  Brake();
}

void ToRight(const double degree, const double Speed, const double Timeout = 100.0) {
  FL.setVelocity(Speed, pct);
  FR.setVelocity(Speed, pct);
  ML.setVelocity(Speed, pct);
  MR.setVelocity(Speed, pct);
  BL.setVelocity(Speed, pct);
  BR.setVelocity(Speed, pct);
  FL.setTimeout(Timeout, sec);
  FR.setTimeout(Timeout, sec);
  ML.setTimeout(Timeout, sec);
  MR.setTimeout(Timeout, sec);
  BL.setTimeout(Timeout, sec);
  BR.setTimeout(Timeout, sec);

  FL.spinFor(fwd, 500, rev, false);
  FR.spinFor(vex::reverse, 500, rev, false);
  ML.spinFor(fwd, 500, rev, false);
  MR.spinFor(vex::reverse, 500, rev, false);
  BL.spinFor(fwd, 500, rev, false);
  BR.spinFor(vex::reverse, 500, rev, false);

  while (round(Inertial.angle()) < round(degree) - 1 || Inertial.angle() > round(degree) + 1) {}
  Brake();
}

int xCoordsIndex = 0;
vision::signature colors[2] = {BLUEY, REDY};
int xCoords[8] = {158, 158, 158, 158, 158, 158, 158, 158};
bool goalFound = 0;
bool aimbotOn = 1;
bool visionPID(const int xCoord) {
  double kp = 0.05, err, pidout;

  err = 158 - xCoord;
  Brain.Screen.clearScreen();
  Brain.Screen.clearLine();
  Brain.Screen.print(err);
  if (abs(err) <= 5) {
    return 1;
  } else {
    pidout = (err * DEGREES_TO_PIXELS) * kp;

    FL.spinFor(vex::reverse, pidout, deg, false);
    ML.spinFor(vex::reverse, pidout, deg, false);
    BL.spinFor(vex::reverse, pidout, deg, false);
    FR.spinFor(fwd, pidout, deg, false);
    MR.spinFor(fwd, pidout, deg, false);
    BR.spinFor(fwd, pidout, deg);

    Brake();
    return 0;
  }
}

int getAverage(const int (*list)[8]) {
  int sum = 0;
  for (int i : (*list)) { sum += i; }
  return sum / 8;
}
void GetVisionCoords() {
  for (vision::signature item : colors) {
    Vision.takeSnapshot(item);
    if (Vision.largestObject.exists) {
      xCoords[xCoordsIndex % 8] = Vision.largestObject.centerX;
      xCoordsIndex++;
      goalFound = 1;
      return;
    }
  }
  goalFound = 0;
  xCoords[xCoordsIndex % 8] = 158;
}
void aimbot() {
  while (goalFound && aimbotOn) {
    if (visionPID(getAverage(&xCoords))) {
      break;
    }
    for (int j = 0; j < 8; j++) {
      GetVisionCoords();
    }
    wait(10, msec);
  }
  wait(100, msec);
}
void Launch() {
  aimbot();
  Catapult.spinFor(fwd, 10, rev, false);
  intakeAllowed = 0;
  Intake.stop();
  wait(100, msec); 
}

bool intakeOverride = 0;

void autonomous(void) {
  // Start of roller
  Calibrate();
  if (!LimitSwitch.pressing())
    Launch();
  Forward(2);
  Intake.spinFor(vex::reverse, 0.6, rotationUnits::rev);
  // End of roller

  // Start of intake first disk
  Back(4);
  Left(80);
  Brake();
  Forward(26);
  Brake();

  // Right(30);
  // Back(20);
  // Left(13);
  // wait(1, sec);
  // Back(2);
  // Launch();
  // Launch();
  // Intake.spin(fwd, 2, volt);
  // Intake.stop();
  // Launch();
  // End of disk in high goal
}


/* ------------------------------------------------------------------------------ */
/* Functions that aren't functional for the robot, but I like to use for          */
/* fun/testing or functions that I don't use right now, but may have a            */
/* use in the future                                                              */
/* ------------------------------------------------------------------------------ */

// Aims the robot with the vision sensor. 95% accuracy
// Unused

void visionAim(const int visionCenter = 158, const int OKEBRor = 15) {
  double x;

  FL.setVelocity(100, pct);
  FR.setVelocity(100, pct);
  BL.setVelocity(100, pct);
  BR.setVelocity(100, pct);

  Vision.takeSnapshot(REDY);
  while (Vision.largestObject.exists && Controller1.ButtonX.pressing()) {
    Vision.takeSnapshot(REDY);
    x = Vision.largestObject.centerX; // Gets center x value of object
    if (x < (visionCenter - OKEBRor)) {
      FR.spin(fwd);
      BR.spin(fwd);
      FL.spin(vex::reverse);
      BL.spin(vex::reverse);
    }
    Brake();
    if (x > (visionCenter + OKEBRor)) {
      FR.spin(vex::reverse);
      BR.spin(vex::reverse);
      FL.spin(fwd);
      BL.spin(fwd);
    }
    Brake();
  }
}
// Fun
void brainVisionDisplay() { // int x, int y, int height, int width) {
  double xScale =
      480.0 /
      VISION_WIDTH; // Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0 / VISION_HEIGHT;
  int x = 0;
  int y = 0;
  int height = 0;
  int width = 0;
  while (true) {
    Brain.Screen.clearLine();
    Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(color::black);
    Vision.takeSnapshot(REDY);
    if (Vision.largestObject.exists) {
      x = Vision.largestObject.originX;
      y = Vision.largestObject.originY;
      width = Vision.largestObject.width;
      height = Vision.largestObject.height;
      Brain.Screen.print(" x: %d y: %d Width: %d Height: %d", x, y, width,
                         height);
      Brain.Screen.setFillColor(color::green);
      Brain.Screen.drawRectangle(x * xScale, y * yScale, width * xScale,
                                 height * yScale);
    } else {
      Brain.Screen.print("Vision Sensor: Color Signature Not Found!");
    }
    wait(100, msec);
  }
}
// Fun
void etchASketch() {
  const double xScale = 380 / 127;
  const double yScale = -(200 / 127);
  int x = Controller1.Axis1.position() * xScale;
  int y = Controller1.Axis2.position() * yScale;
  if (Brain.Screen.pressing()) {
    x = Brain.Screen.xPosition();
    y = Brain.Screen.yPosition();
  }
  Brain.Screen.setFillColor(white);
  Brain.Screen.drawRectangle(x, y, 5, 5, white);
}

/* ------------------------------------------------------------------------------- */
/* End of unused or fun code                                                       */
/* ------------------------------------------------------------------------------- */

// Variables to manage different togglable motors
int_fast8_t bools = 0b00;
// Variable to dictate how fast the robot moves
float MovementSpeed = 0.5f;
int axis2;
int axis3;

// Increases movement speed.
void MovementSpeedHigher() {
  if (MovementSpeed < 0.5) {
    MovementSpeed = 0.5f; // Makes the robot move faster.
  } else if (MovementSpeed < 1) {
    MovementSpeed = 1;
  }
  // Prints the robots speed on the controller screen.
  Controller2.Screen.clearScreen();
  Controller2.Screen.clearLine();
  Controller2.Screen.print("Speed: %.0f", MovementSpeed * 100);
}
// Decreases movement speed.
void MovementSpeedLower() {
  if (MovementSpeed > 0.5) {
    MovementSpeed = 0.5f; // Makes the robot move faster.
  } else if (MovementSpeed > 0.33) {
    MovementSpeed = 0.33f;
  }
  // Prints the robots speed on the controller screen.
  Controller2.Screen.clearScreen();
  Controller2.Screen.clearLine();
  Controller2.Screen.print("Speed: %.0f", MovementSpeed * 100);
}

// Launches expansion
inline void Expansion() { Expansion1.set(true); }

/*   The following 3 functions are used in usercontrol. I moved  */
/*   them out to make it more readable.                          */

// Checks if the intake's on, and which direction it's spinning.
inline void IntakeCheck() {
  if (intakeAllowed || intakeOverride)
    bools & 1 && (bools >> 1) & 1
            ? Intake.spin(vex::reverse, 12, volt)
            : bools & 1 && !((bools >> 1) & 1) ? Intake.spin(fwd, 12, volt)
                                               : Intake.stop();
}

// Code that lets the driver drive
void DriveTrain() {
  axis2 = 0.79 * Controller1.Axis2.value();
  axis3 = 0.79 * Controller1.Axis3.value();

  FL.spin(fwd, (MovementSpeed * axis3), velocityUnits::pct);
  FR.spin(fwd, (MovementSpeed * axis2), velocityUnits::pct);
  ML.spin(fwd, (MovementSpeed * axis3), velocityUnits::pct);
  MR.spin(fwd, (MovementSpeed * axis2), velocityUnits::pct);
  BL.spin(fwd, (MovementSpeed * axis3), velocityUnits::pct);
  BR.spin(fwd, (MovementSpeed * axis2), velocityUnits::pct);
}

void usercontrol(void) {
  intakeAllowed = 1;

  FL.setVelocity(100, pct);
  FR.setVelocity(100, pct);
  ML.setVelocity(100, pct);
  MR.setVelocity(100, pct);
  BL.setVelocity(100, pct);
  BR.setVelocity(100, pct);
  // Brake();

  // Controller1.Screen.clearScreen();
  Controller1.ButtonUp.pressed(MovementSpeedHigher);            // Increased robots speed
  Controller1.ButtonDown.pressed(MovementSpeedLower);           // Decreased robots speed
  Controller1.ButtonLeft.pressed([]() { bools ^= 1; });         // Toggles intake
  Controller1.ButtonRight.pressed([]() { bools ^= (1 << 1); }); // Toggles intake direction
  Controller1.ButtonY.pressed([]() { aimbotOn = !aimbotOn; });

  Controller2.ButtonUp.pressed(MovementSpeedHigher);            // Increased robots speed
  Controller2.ButtonDown.pressed(MovementSpeedLower);           // Decreased robots speed
  Controller2.ButtonY.pressed([]() { aimbotOn = !aimbotOn; });
  Controller2.ButtonR2.pressed([]() {intakeOverride = !intakeOverride; });

  time_t ExpansionReleaseTimer = time(NULL);       // Timer for expansion
  time_t CurrentTime = time(NULL);                 // Current time
  while (1) {
    // ...............................................................................
    // Brain.Screen.cleaBLine();
    // Brain.Screen.print(getAverage(&xCoords));

    CurrentTime = time(NULL); // Resets timer
    if (CurrentTime - ExpansionReleaseTimer >= 0) {
      Controller1.ButtonL1.pressed(Expansion);
      Controller2.ButtonL1.pressed(Expansion);
      ExpansionReleaseTimer = time(NULL);
    }
    vex::thread driverThread = vex::thread(DriveTrain);
    vex::thread intakeThread = vex::thread(IntakeCheck);
    vex::thread getCoordsThread = vex::thread(GetVisionCoords);

    // if (Rotation.angle(degrees) < 109.5 && Rotation.angle(degrees) > 108) {
    //   Catapult.stop();
    // }
    if (Controller1.ButtonB.pressing()) {
      Catapult.spinFor(fwd, 0.15, rev);
    }
    if (Controller1.ButtonL2.pressing()) { // Aims robot and lauches catapult
      Launch();
    }
    if (Controller1.ButtonX.pressing()) {
      aimbot();
    }
    driverThread.join();
    intakeThread.join();
    getCoordsThread.join();

    // if (!LimitSwitch.pressing()) {
    //   Intake.stop();
    // }
    // ...............................................................................
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

// Main will set up the competition functions and callbacks.
int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  while (1) { // Prevent main from exiting with an infinite loop.
    wait(100, msec);
  }
  return 0;
}