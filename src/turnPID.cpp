#include "cmath"
#include "vex.h"
#include "motors.h"
#include "turnPID.h"

turnPID::turnPID() {
}

void turnPID::reset() {
    position = 0;
    error = 0;
    target = 0;
    i = 0;
    d = 0;
}

void turnPID::update() {
    prevError = error;
    position = InertialSensor.heading();
    error = target - position;
    i += error;

    d = error - prevError;

    if (error <= 0 || fabs(error) >= 50) {
        i = 0;
    }
}

void turnPID::stopTurnPID() {
    driveBase.stop(brake);
    driveBase.setStopping(coast);
    stop = true;
    // printToConsole("Stopped with stopTurnPID");
}

void turnPID::runTurnPID(double _target) { // CURRENTLY BROKEN, MAY NOT BE FIXED AT TIME OF READING THIS (man everything just broke 😭)
    reset();
    // for (int i = 0; i < 2; i++) {
        Brain.Screen.print("turnPID started: ");
        Brain.Screen.print(_target);
        stop = false;
        Brain.Screen.clearScreen();
        if (_target > 180) {
            _target -= 360;
        } else if (_target < -180) {
            _target += 360;
        }
        if (_target > 0) {
            _target += 180;
        }
        target = _target;
        double speed;
        error = target;
        int time = 0;
        while (fabs(error) >= 0) {
            update();
            speed = (kp * error) + (ki * i) + (kd * d);
            if (speed < 0.1 && time >= 200) {
                Brain.Screen.print("Speed too low; stopping");
                // printToConsole("Speed too low; stopping");
                stopTurnPID();
                break;
            }
            if (!stop) {
                Left.spin(forward, ((kp * error) + (ki * i) + (kd * d)) * 0.88, pct);
                Right.spin(reverse, ((kp * error) + (ki * i) + (kd * d)) * 0.88, pct);
            }
            time += 20;
            wait(20, msec);
        }
    // }
}