#include "cmath"
#include "vex.h"
#include "motors.h"
#include "PID.h"

PID::PID() {
}

void PID::reset() {
    position = 0;
    error = 0;
    target = 0;
    i = 0;
    d = 0;
}

void PID::update() {
    prevError = error;
    position = (YTrackingWheel.position(deg) / 360) * M_PI * 2.75 /*REPLACE WITH CORRECT TRACKING WHEEL SIZE*/;
    error = target - position;
    Brain.Screen.clearLine();
    Brain.Screen.print(error);
    i += error;

    d = error - prevError;

    if (error <= 0 || fabs(error) >= 50) {
        i = 0;
    }
}

void PID::stopPID() {
    driveBase.stop(brake);
    driveBase.setStopping(coast);
    stop = true;
    // printToConsole("Stopped with stopPID");
}

void PID::runPID(double _target) {
    reset();
    Brain.Screen.clearScreen();
    Brain.Screen.print("PID started: ");
    Brain.Screen.print(_target);
    stop = false;
    target = _target;
    int speed;
    error = target;
    while (fabs(error) >= 0.2) {
        update();
        speed = (kp * error) + (ki * i) + (kd * d);
        if (!stop) driveBase.spin(fwd, ((kp * error) + (ki * i) + (kd * d)) * 0.8, pct);
        wait(20, msec);
        if (speed < 1) {
            Brain.Screen.print("Speed too low; stopping");
            // printToConsole("Speed too low; stopping");
            stopPID();
            break;
        }
    }
    stopPID();
    Brain.Screen.print("       PID STOPPED");
    
}