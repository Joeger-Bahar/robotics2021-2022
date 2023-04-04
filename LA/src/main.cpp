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

/*
Up arrow      Movement speed higher
Down arrow    Movement speed lower
Left arrow    Toggles intake on and off
Right arrow   Toggles intake direction
L1            Launches expansion 
L2            Launches catapult
R1            Turns roller forwards
R2            Turns roller backwards
X             Aimbot
Y             Gets goal width and height for aimbot
A             Stops robot
B             Moves catapult a tiny bit for testing
*/
// Vision sensor specs
// 50 fps
// 316w x 212h
#include "Vision.h"
#include "vex.h"
#include <string.h>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <map>

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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Expansion1.set(true);
  // Expansion2.set(true);

  // Calibrate();
  Brain.Screen.setOrigin(240, 125);
  Catapult.setVelocity(100, pct);
  Controller1.Screen.clearScreen();
}

void Forward(const double inches, const double speed = 60, const double timeOut = 100.0) {
  const double Distance = (360 / 12.56) * inches;

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  RL.setVelocity(speed, pct);
  RR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  RL.setTimeout(timeOut, sec);
  RR.setTimeout(timeOut, sec);

  FL.spinFor(fwd, Distance, degrees, false);
  FR.spinFor(fwd, Distance, degrees, false);
  RL.spinFor(fwd, Distance, degrees, false);
  RR.spinFor(fwd, Distance, degrees);
}
void Back(const double inches, const double speed = 60, const double timeOut = 100.0) {
  const double Distance = (360 / 12.56) * inches;

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  RL.setVelocity(speed, pct);
  RR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  RL.setTimeout(timeOut, sec);
  RR.setTimeout(timeOut, sec);

  FL.spinFor(vex::reverse, Distance, degrees, false);
  FR.spinFor(vex::reverse, Distance, degrees, false);
  RL.spinFor(vex::reverse, Distance, degrees, false);
  RR.spinFor(vex::reverse, Distance, degrees);
}
void Left(const double inches, const double speed = 20, const double timeOut = 100.0) {
  // double Distance = ((360 / 12.56) * inches) * 0.086;
  double x = Inertial.angle();
  double y = x - inches;
  if (y > 360) {y -= 360;}
  if (y < 0) {y += 360;}

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  RL.setVelocity(speed, pct);
  RR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  RL.setTimeout(timeOut, sec);
  RR.setTimeout(timeOut, sec);

  FL.spinFor(vex::reverse, 500, rev, false);
  FR.spinFor(fwd, 500, rev, false);
  RL.spinFor(vex::reverse, 500, rev, false);
  RR.spinFor(fwd, 500, rev, false);

  while (true) {
    if (round(Inertial.angle()) == round(y)) {
      FL.stop();
      FR.stop();
      RL.stop();
      RR.stop();
      break;
    }
  }
}
void Right(const double inches, const double speed = 20, const double timeOut = 100.0) {
  double x = Inertial.angle();
  double y = x + inches;
  if (y > 360) {y -= 360;}
  if (y < 0) {y += 360;}

  FL.setVelocity(speed, pct);
  FR.setVelocity(speed, pct);
  RL.setVelocity(speed, pct);
  RR.setVelocity(speed, pct);
  FL.setTimeout(timeOut, sec);
  FR.setTimeout(timeOut, sec);
  RL.setTimeout(timeOut, sec);
  RR.setTimeout(timeOut, sec);

  FL.spinFor(fwd, 500, rev, false);
  FR.spinFor(vex::reverse, 500, rev, false);
  RL.spinFor(fwd, 500, rev, false);
  RR.spinFor(vex::reverse, 500, rev, false);

  while (true) {
    if (round(Inertial.angle()) == round(y)) {
      FL.stop();
      FR.stop();
      RL.stop();
      RR.stop();
      break;
    }
  }
}

void redLight() {
  FL.setBrake(brake);
  FR.setBrake(brake);
  ML.setBrake(brake);
  MR.setBrake(brake);
  RL.setBrake(brake);
  RR.setBrake(brake);
}
void greenLight() {
  FL.setBrake(coast);
  FR.setBrake(coast);
  ML.setBrake(coast);
  MR.setBrake(coast);
  RL.setBrake(coast);
  RR.setBrake(coast);
}

void Brake() {
  redLight();
  greenLight();
}

void Launch() {
  Catapult.spinFor(fwd, 5.96, rev, false);
}

void autonomous(void) {
  Calibrate();
  Forward(1);
  RollerRoller.spinFor(vex::reverse, 0.35, rotationUnits::rev);
  Back(4);
  Left(135);
  Intake.spin(fwd, 10, volt);
  Forward(50);
  Left(100);
  Back(20);
  Launch();
  Intake.spinFor(vex::reverse, 5, rotationUnits::rev);
  Forward(7);
}




/* --------------------------------------------------------------------------------- */
/* Functions that aren't functional for the robot, but I like to use for fun/testing */
/* Or functions that I don't use right now, but may have a use in the future         */
/* --------------------------------------------------------------------------------- */




// Debugging
void clearRect(map<string, int>& visionRect, vector<int>& xCoords, vector<int>& yCoords) {
  visionRect.clear();
  xCoords.clear();
  yCoords.clear();
}
// Debugging
void getRectangle(vector<int>& x, vector<int>& y, map<string, int>& rect) {
  auto max_y = max_element(y.begin(), y.end());
  auto max_x = max_element(x.begin(), x.end());
  
  auto min_x = min_element(x.begin(), x.end());
  auto min_y = min_element(y.begin(), y.end());
  
  rect["topX"] = *max_x;
  rect["topY"] = *max_y;
  rect["midX"] = (*max_x + *min_x) / 2;
  rect["midY"] = (*max_y + *min_y) / 2;
  rect["bottomX"] = *min_x;
  rect["bottomY"] = *min_y;
  rect["height"] = *max_y - *min_y;
  rect["width"] = *max_x - *min_x;
}
// Aims the robot with the vision sensor. 95% accuracy
//Unused
void visionAim(const int visionCenter = 158, const int OKError = 15) {
  double x;

  FL.setVelocity(100, pct);
  FR.setVelocity(100, pct);
  RL.setVelocity(100, pct);
  RR.setVelocity(100, pct);
  // uint64_t aimbotTimer = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  // uint64_t aimbotTimer2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); 
  // for (vision::signature item : colors) {
  Vision.takeSnapshot(REDY);
  while (Vision.largestObject.exists && Controller1.ButtonX.pressing()) {
    Vision.takeSnapshot(REDY);
    x = Vision.largestObject.centerX;   // Gets center x value of object

    // xCoords.push_back(Vision.largestObject.centerX);
    // yCoords.push_back(Vision.largestObject.centerY);
    // getRectangle(xCoords, yCoords, visionRect);
    // brainVisionDisplay(visionRect["topX"], visionRect["topY"], visionRect["height"], visionRect["width"]);

    // aimbotTimer2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    // if ((aimbotTimer2 - aimbotTimer) > 200) {
    if (x < (visionCenter - OKError)) { // If the object is to the left of center
      // Brain.Screen.clearLine();
      // Brain.Screen.print("Middle X: %d If left: %b", visionRect["midX"], visionRect["midX"] < (center-OKError));
      FR.spin(fwd);
      RR.spin(fwd);
      FL.spin(vex::reverse);
      RL.spin(vex::reverse);
    }
    Brake();
    if (x > (visionCenter + OKError)) { // If the object is to the right of center
      FR.spin(vex::reverse);
      RR.spin(vex::reverse);
      FL.spin(fwd);
      RL.spin(fwd);
    }
    Brake();
  }
}
// Unused
void inertialAim() {
  double kp = 0.0;
  double kd = 0.0;
  double err = 0.0;
  double speed = 0.0;
  double target = 90;
  double lasterr = 0.0;
  double autoturn = 0.0;

  err = target - Inertial.heading(degrees);
  speed = err - lasterr;
  lasterr = err;
  autoturn = err * kp + speed * kd;
  FL.spin(fwd, autoturn*.12, volt);
  FR.spin(fwd, autoturn*.12, volt);
  RL.spin(fwd, autoturn*.12, volt);
  RR.spin(fwd, autoturn*.12, volt);
}
// Fun
void brainVisionDisplay() {//int x, int y, int height, int width) {
  double xScale = 480.0 / VISION_WIDTH; //Scaling the vision sensor range to the V5 Brain Screen
  double yScale = 240.0 / VISION_HEIGHT;
  int x = 0; int y= 0; int height = 0; int width = 0;
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
      Brain.Screen.print (" x: %d y: %d Width: %d Height: %d",x, y, width, height);
      Brain.Screen.setFillColor(color::green);
      Brain.Screen.drawRectangle(x * xScale, y * yScale, width * xScale, height * yScale);
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



/* --------------------------------------------------------------------------------- */
/* End of unused or fun code                                                         */
/* --------------------------------------------------------------------------------- */




// Variables to manage different togglable motors
int_fast8_t bools = 0b00;
// Variable to dictate how fast the robot moves
float MovementSpeed = 0.5f;
// Arrays and variables to always have an average x and y value for the 
// vision sensor
// Array to loop through vision sensor colors
vision::signature colors[2] = {BLUEY, REDY};

// Gets an average from a list of numbers
int getAverage(const int (*list)[8]) {
  int sum = 0;

  for (int i : (*list)) { sum += i; }

  return sum / 8;
}

// Turns the robot to the goal, relative to the robot
void visionPID(const int xCoord) {
  double kp = 0.16667, err, pidout; //kd = 0.12, err, speed, lasterr = 0, pidout;
  err = 158 - xCoord;
  Brain.Screen.clearLine();
  // speed = err - lasterr; lasterr = err;
  pidout = (err * DEGREES_TO_PIXELS) * kp; // + speed * kd;
  Brain.Screen.print(pidout);
  FL.spinFor(vex::reverse, pidout, deg, false);
  ML.spinFor(vex::reverse, pidout, deg, false);
  RL.spinFor(vex::reverse, pidout, deg, false);
  FR.spinFor(fwd, pidout, deg, false);
  MR.spinFor(fwd, pidout, deg, false);
  RR.spinFor(fwd, pidout, deg);
  Brake();
}

// Increases movement speed.
void MovementSpeedHigher() {
  if (MovementSpeed < 0.5) {
    MovementSpeed = 0.5f; // Makes the robot move faster.
  } else if (MovementSpeed < 1) {
    MovementSpeed = 1;
  } 
  // Prints the robots speed on the controller screen.
  Controller1.Screen.clearScreen(); 
  Controller1.Screen.clearLine();
  Controller1.Screen.print("Speed: %.0f", MovementSpeed * 100);
}
// Decreases movement speed.
void MovementSpeedLower() {
  if (MovementSpeed > 0.5) {
    MovementSpeed = 0.5f; // Makes the robot move faster.
  } else if (MovementSpeed > 0.33) {
    MovementSpeed = 0.33f;
  } 
  // Prints the robots speed on the controller screen.
  Controller1.Screen.clearScreen();
  Controller1.Screen.clearLine();
  Controller1.Screen.print("Speed: %.0f", MovementSpeed * 100);
}

// Launches expansion
inline void Expansion() {
  Expansion1.set(false);
}

/*   The following 3 functions are used in usercontrol. I moved  */
/*   them out to make it more readable.                          */

// Checks if the intake's on, and which direction it's spinning.
inline void IntakeCheck(const int_fast8_t& bools) {
  bools & 1 && (bools >> 1) & 1 ? Intake.spin(vex::reverse, 11.7, volt) : bools & 1 && !((bools >> 1) & 1) ? 
                                  Intake.spin(fwd, 11.7, volt) : Intake.stop();
}

// Gets, and keeps, an average of where the goal is relitive to the robot
void GetVisionCoords(int (&xCoords)[8], int &xCoordsIndex) {
  for (vision::signature item : colors) {
    Vision.takeSnapshot(item);
    xCoords[xCoordsIndex % 8] = Vision.largestObject.exists ? Vision.largestObject.centerX : 158;
    xCoordsIndex++;
  }
}

// Code that lets the driver drive
void DriveTrain(int *axis2, int *axis3) {
  *axis2 = 0.79 * Controller1.Axis2.value();
  *axis3 = 0.79 * Controller1.Axis3.value();

  FL.spin(fwd, (MovementSpeed * *axis3), velocityUnits::pct);
  FR.spin(fwd, (MovementSpeed * *axis2), velocityUnits::pct);
  ML.spin(fwd, (MovementSpeed * *axis3), velocityUnits::pct);
  MR.spin(fwd, (MovementSpeed * *axis2), velocityUnits::pct);
  RL.spin(fwd, (MovementSpeed * *axis3), velocityUnits::pct);
  RR.spin(fwd, (MovementSpeed * *axis2), velocityUnits::pct);
}

void usercontrol(void) {
  int axis2;
  int axis3;
  int xCoords[8] = {158, 158, 158, 158};
  int xCoordsIndex = 0;

  FL.setVelocity(100, pct);
  FR.setVelocity(100, pct);
  ML.setVelocity(100, pct);
  MR.setVelocity(100, pct);
  RL.setVelocity(100, pct);
  RR.setVelocity(100, pct);
  Brake();


  Controller1.Screen.clearScreen();
  Controller1.ButtonLeft.pressed([]() { bools ^= 1;});                // Toggles intake
  Controller1.ButtonRight.pressed([]() { bools ^= (1 << 1);});        // Toggles intake direction
  Controller1.ButtonUp.pressed(MovementSpeedHigher);                  // Increased robots speed
  Controller1.ButtonDown.pressed(MovementSpeedLower);                 // Decreased robots speed

  LimitSwitch.pressed([]() {Catapult.stop();});

  time_t ExpansionReleaseTimer = time(NULL); // Timer for expansion
  time_t RecentExpansionReleaseTimer = time(NULL); // Resets timer
  // Prevents drivetrain() from recreating these variables every time it's called
  while (1) {
    // ...............................................................................
    // Brain.Screen.clearLine();
    // Brain.Screen.print(getAverage(&xCoords));

    RecentExpansionReleaseTimer = time(NULL); // Resets timer

    if (RecentExpansionReleaseTimer - ExpansionReleaseTimer >= 94) { // If time is 10 seconds or less
      Controller1.ButtonL1.pressed(Expansion);
    }
    DriveTrain(&axis2, &axis3);
    IntakeCheck(bools);
    GetVisionCoords(xCoords, xCoordsIndex);
    
    // if (Rotation.angle(degrees) < 109.5 && Rotation.angle(degrees) > 108) {
    //   Catapult.stop();
    // }
    if (Controller1.ButtonB.pressing()) {  // Moves the catapult back a tiny bit for testing.
      Catapult.spinFor(fwd, 0.15, rev);
    }
    if (Controller1.ButtonL2.pressing()) {  // Aims robot and lauches catapult
      visionPID(getAverage(&xCoords));
      wait(100, msec);
      Catapult.spinFor(fwd, 10, rev, false);
      wait(100, msec);
    }
    if (Controller1.ButtonX.pressing()) {
      visionPID(getAverage(&xCoords));
    }
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