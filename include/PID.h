#pragma once
#include "cmath"
#include "vex.h"
#include "motors.h"

class PID {
    double position;
    double target;
    double error = 0;
    double i;
    double d;

    double prevError;

    double kp = 4.3;
    double ki = 0.039;
    double kd = 2;

    bool stop = false;

    public:
        PID();
        
        void reset();

        void update();

        void stopPID();

        void runPID(double _target);
};