// #include "cmath"
// #include "vex.h"
// #include "motors.h"
// #include "odom.h"

// odom::odom() {
//     θ = 0;
// }

// odom::odom(double initialRotation) {
//     θ = initialRotation;
// }

// odom::update() {
//     Δx = 0;
//     Δy = 0;
//     Δθ = InertialSensor.heading() - θ;
//     // L = Left.position(vex::deg) * M_PI * 2.75 - LPrev;
//     distanceTraveled = Right.position(vex::deg) * M_PI * TRACKING_WHEEL_SIZE - RPrev;
//     _arcLength = distanceTraveled;
//     r = _arcLength/Δθ;
//     Δx_local = r*(1-cos(Δθ));
//     Δy_local = r*sin(Δθ);
//     Δx = (Δx_local * cos(θ)) + (Δy_local * sin(θ));
//     Δy = (Δx_local * sin(θ)) + (Δy_local * cos(θ));

//     θ = InertialSensor.heading();
//     x += Δx;
//     y += Δy;

//     prev = YTrackingWheel.position(vex::deg) * M_PI * 2.75;
//     vex::wait(10, vex::msec);
// }