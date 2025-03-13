// #pragma once
// #include "cmath"
// #include "vex.h"
// #include "motors.h"

// class odom {
//     private:
//     //double L /*The distance that the left-side tracking wheel has traveled*/;
//     //double R /*The distance that the right-side tracking wheel has traveled*/;
//     //double LPrev = 0;
//     //double RPrev = 0;
//     double distanceTraveled;
//     double Prev;
//     double Δθ = 0; //Change in theta (θ)
//     double Δx = 0; //Change in X
//     double Δx_local = 0; //Change in X locally (not counting theta/from robot's pov)
//     double Δy = 0; //Change in Y
//     double Δy_local = 0; //Change in Y locally (not counting theta/from robot's pov)
//     double x = 0;
//     double y = 0;
//     double θ = 0;
//     double r = 1; 
//     double _arcLength = 0;

//     public:
//     odom();

//     odom(double initialRotation);

//     void update();
// };