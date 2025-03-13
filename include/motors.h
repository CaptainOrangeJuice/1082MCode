#pragma once

// #include <iostream>
#include "vex.h"
using namespace vex;
using namespace std;

// #define printToConsole(text) std::cout<<text<<std::endl;
#define TRACKING_WHEEL_SIZE 2.75 //CHANGE TO CORRECT SIZE (diameter)

extern brain Brain;

extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;

extern motor_group Left;
extern motor_group Right;
extern motor_group driveBase;

extern motor ladyBrown;

extern motor intake1;
extern motor intake2;

extern motor_group intake;

// digital_out piston1(Brain.ThreeWirePort.A); 
extern digital_out piston2;
// digital_out piston3(Brain.ThreeWirePort.D); 
extern digital_out piston4;

extern distance DistanceSensor;
extern distance DistanceSensor1; //Clamp distance sensor
// distance DistanceSensor2(PORT17);
// distance DistanceSensor3(PORT7);

extern distance rightSensor;
extern distance leftSensor;
extern distance backSensor;
extern distance frontSensor;

extern inertial InertialSensor;

extern rotation XTrackingWheel;
extern rotation YTrackingWheel;

extern optical ColorSensor; //Color sorting

extern controller Controller1;