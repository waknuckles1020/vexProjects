/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Ayush                                            */
/*    Created:      Thu Aug 04 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RFM                  motor         1               
// RBM                  motor         2               
// LFM                  motor         3               
// LBM                  motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

//required libraries
#include "vex.h"
using namespace vex;

//subsystems===============================================
//drive 
#include "drive.h"

double rightPow;
double leftPow;



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true){
<<<<<<< HEAD
    //driver methods
    setMotors();
=======
    rightPow = Controller1.Axis2.position();
    leftPow = Controller1.Axis3.position();

    setMotors(rightPow, leftPow);
>>>>>>> parent of de518ae (asdf)

    wait(20, msec);
  }
  
  
}
