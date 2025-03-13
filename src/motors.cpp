// #include <iostream>
#include "vex.h"
#include "motors.h"
using namespace vex;
using namespace std;

// #define printToConsole(text) std::cout<<text<<std::endl;
// #define TRACKING_WHEEL_SIZE 2.75 //CHANGE TO CORRECT SIZE (diameter)

brain Brain;

motor L1(PORT7, ratio6_1, true);
motor L2(PORT11, ratio6_1, true);
motor L3(PORT13, ratio6_1, true);
motor R1(PORT16, ratio6_1, false);
motor R2(PORT18, ratio6_1, false);
motor R3(PORT20, ratio6_1, false);

motor_group Left(L1,L2,L3);
motor_group Right(R1,R2,R3);
motor_group driveBase(L1,L2,L3, R1,R2,R3);

motor ladyBrown(PORT14, ratio18_1, true);

motor intake1(PORT19, ratio6_1, false);
motor intake2(PORT12, ratio18_1, true); //belt

motor_group intake(intake1, intake2);

// digital_out piston1(Brain.ThreeWirePort.A); 
digital_out piston2(Brain.ThreeWirePort.A); //Clamp
// digital_out piston3(Brain.ThreeWirePort.D); 
digital_out piston4(Brain.ThreeWirePort.B); //sweeper

distance DistanceSensor(PORT10);
distance DistanceSensor1(PORT4); //Clamp distance sensor
// distance DistanceSensor2(PORT17);
// distance DistanceSensor3(PORT7);

distance rightSensor(PORT2);
distance leftSensor(PORT15);
distance backSensor(PORT9);
distance frontSensor(PORT10);

inertial InertialSensor(PORT5);

rotation XTrackingWheel(PORT22, true);
rotation YTrackingWheel(PORT17, true);

optical ColorSensor(PORT6); //Color sorting

controller Controller1(primary);