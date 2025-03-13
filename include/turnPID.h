#pragma once
#include "cmath"
#include "vex.h"
#include "motors.h"

class turnPID {
    double position;
    double target;
    double error = 0;
    double i;
    double d;

    double prevError;

    double kp = 3;
    double ki = 0.1;
    double kd = 3.5;

    bool stop = false;

    public:
        turnPID();
        
        void reset();

        void update();

        void stopTurnPID();

        void runTurnPID(double _target);
};