/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       orang                                                     */
/*    Created:      3/3/2025, 4:41:39 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "motors.h"
#include "PID.h"
#include "turnPID.h"
#include "odom.h"

using namespace vex;

// A global instance of competition
competition Competition;
PID pid;
turnPID turnpid;

bool unclamp;
bool forceUnclamp = false;
double hue;
int redOrBlue = 0; //0 is none, -1 is red, 1 is blue
double startPos;

// define your global instances of motors and other devices here
void Unclamp() {
  piston2.set(false);
  unclamp = true;
  //Brain.Screen.print("unclamp");
  // forceUnclamp = true;
}

void Clamp() {
  piston2.set(true);
  unclamp = false;
  forceUnclamp = false;
  //Brain.Screen.print("clamp");
}

void disableForceUnclamp() {
  forceUnclamp = false;
}

void AutoClamp() {
  while (1) {
    if (forceUnclamp) {
      piston2.set(false);
      //wait(1,sec);
      //DistanceSensor1.changed(disableForceUnclamp);
      while (DistanceSensor1.objectDistance(inches) <= 1.5) {
        wait(50, msec);
      }
      disableForceUnclamp();
    } else {
      if (DistanceSensor1.objectDistance(inches) <= 1.5) {
        wait(80, msec);
        if (!forceUnclamp) {
          Clamp();
        }
      } else {
        Unclamp();
      }
    }
  }
}

void resetLadyBrown() {
  ladyBrown.spin(reverse, 70, pct);
  wait(0.1, sec);
  ladyBrown.stop(brake);
  ladyBrown.resetPosition();
}

bool checkForRed() { //Color sort
  hue = -1;
  while (!ColorSensor.isNearObject()){
    wait(10,msec);
    hue = -1;
    redOrBlue = 0;
  // if (ColorSensor.isNearObject()){
  }
  wait(10,msec);
  Brain.Screen.clearLine();
  Brain.Screen.print(ColorSensor.hue());
  if (hue == -1) hue = ColorSensor.hue();
  if ((hue >= 0 && hue <= 65) || (hue >= 280 && hue <= 360)) return false; //True if checking for/getting rid of red, false if checking for/getting rid of blue
  //else if (hue > 65 && hue < 180) return false;
  return true; //Use whichever one makes it keep spinning
}

void SpinWithColorSort(/*int seconds*/) {
  int seconds = 100;
  double time = 0;
  bool red;
  while (time <= seconds) {
    red = false;
    intake.spin(forward, 100, pct);
    ColorSensor.setLight(ledState::on);
    if (ColorSensor.isNearObject()) { red = checkForRed(); }
    if (red == true) {
      startPos = intake2.position(deg);
      while (intake2.position(deg) < startPos + 122) {
        wait(20, msec);
        time += 0.02;
      }
      intake.stop(brake);
      wait(200, msec);
      time += 0.2;
    }
    time += 0.05;
    wait(50,msec);
  }
  intake.stop(brake);
  ColorSensor.setLight(ledState::off);

}

void CalibrateInertial() {
  InertialSensor.calibrate();
  while (InertialSensor.isCalibrating()) {
    wait(10,msec);
  }
  InertialSensor.resetHeading();
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  thread autoClamp(AutoClamp);
  // thread colorSorting(checkForRed);
  // Brain.Screen.print("a");
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  thread calibrateInertial(CalibrateInertial);
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  resetLadyBrown();
  
  // pid.runPID(24);
  // wait(400, msec);
  // turnpid.runTurnPID(90);  
  
  
  InertialSensor.setHeading(-60, deg);
  ladyBrown.spin(forward, 70, pct);
  wait(1.5, sec);
  ladyBrown.spin(reverse, 70, pct);
  turnpid.runTurnPID(-90);
  pid.runPID(12);
  ladyBrown.stop(coast);
  thread spinWithColorSort(SpinWithColorSort); //Gets rid of blue
  turnpid.runTurnPID(180);
  pid.runPID(-36);
  turnpid.runTurnPID(-90);
  pid.runPID(24);
  turnpid.runTurnPID(0);
  pid.runPID(12);
  wait(1.5, sec);
  turnpid.runTurnPID(90);
  pid.runPID(24);
  ladyBrown.spin(forward, 70, pct);
  wait(0.5, sec);
  ladyBrown.stop(coast);

  //turnpid.runTurnPID(90);
  //pid.runPID(-32);

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //pid.runPID(24);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // Thread.ignore(spinWithColorSort);
  resetLadyBrown();
  // User control code here, inside the loop
  //bool clampBool = unclamp;
  bool ladyBrownReady = false;
  piston2.set(false);
  bool sweeperBool = true;
  while (1) {
    //AutoClamp();
    Left.spin(forward, Controller1.Axis3.position() + Controller1.Axis1.position(), pct);
    Right.spin(forward, Controller1.Axis3.position() - Controller1.Axis1.position(), pct);

    if (Controller1.ButtonL1.pressing()) {
      intake.spin(forward, 100, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      intake.spin(reverse, 100, pct);
    } else {
      intake.stop(brake);
    }

    if (Controller1.ButtonA.pressing()) {
      if (unclamp) {
        forceUnclamp = false;
        unclamp = false;
        Clamp();
      } else {
        for (int i = 0; i < 3; i++) {
          forceUnclamp = true;
          unclamp = true;
          Unclamp();
        }
        wait(30, msec);
      }
      Brain.Screen.clearLine();
      Brain.Screen.print(unclamp);
      // unclamp = !clampBool;
      wait(20, msec);
    }

    if (Controller1.ButtonR1.pressing()) {
      if (ladyBrownReady == false) {
        ladyBrown.spinToPosition(90,deg);
        ladyBrown.stop(hold);
        ladyBrownReady = true;
      } else {
        ladyBrown.spin(forward, 60, pct);
      }
    } else if (Controller1.ButtonR2.pressing()) {
      ladyBrown.spin(reverse, 60, pct);
    } else if (ladyBrown.position(deg) < 30) {
      ladyBrown.stop(coast);
      ladyBrownReady = false;
    } else {
      ladyBrown.stop(hold);
    }

    if (Controller1.ButtonY.pressing()) {
      piston4.set(sweeperBool);
      sweeperBool = !sweeperBool;
      wait(0.1, sec);
    }

    // if (Controller1.ButtonLeft.pressing()) {
    //   thread spinWithColorSort(SpinWithColorSort); //Gets rid of blue
    // }
    
    // if (Controller1.ButtonLeft.pressing()) {
    //   Thread.ignore(spinWithColorSort);
    // }
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
