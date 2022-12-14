/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RFM                  motor         1               
// RBM                  motor         2               
// LFM                  motor         3               
// LBM                  motor         4               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "cmath"
using namespace vex;
using namespace std;
competition Competition;


//VARIABLES======================================================================
//constant for pi
double pi = M_PI;

//varibles in code
//drive----
double x;
double y;
double turn;
double theta;

double pw;
double s;
double c;
double mx;
 
double leftFront;
double rightFront;
double leftBack;
double rightBack;

//FUNCTIONS======================================================================
//Helper Functions
void calcDeadzone(){ //calculates deadzone of joystick for less need of precision
  if(theta > (-1*pi)/12 && theta < (pi/12)){
    theta = 0;
  } else if(theta > (-7*pi)/12 && theta < (-5*pi)/12){
    theta = -1*(pi)/2;
  } else if(theta > (5*pi)/12 && theta < 7*(pi/12)){
    theta = pi/2;
  } else if((theta > (11*pi)/12 && theta < (pi)) || (theta > (-1*pi)/12 && theta < (-11*pi/12))){
    theta = pi;
  } else {
    theta = theta;
  }
}

//Button Functions 
int fwdDir = 1;
void switchDir(){ //inverts forward and backward for orientations
  fwdDir *= -1;
}

//Auton Functions


// define your global instances of motors and other devices here

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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
  
  //Buttons used in driver control
  Controller1.ButtonA.pressed(switchDir);
  
  while (1) {
    //HIDDEN PROCESSES===================================================================================
    //DRIVE PROCESS------------------------------------------
    //positions for joystick values
    x = (fwdDir)*Controller1.Axis4.position(); // x position of joystick (inverted if fwdDir = -1)
    y = (-1*fwdDir)*Controller1.Axis3.position(); // y position of joystick
    turn = 1*(Controller1.Axis1.position()); // turn value

    //information for motors
    theta = atan2(y, x); // angle from origin to (x, y)
    pw = hypot(x, y); // power sent to motors, based off distance from origin to (x, y)

    calcDeadzone(); //snaps joystick to absolute direction if within 15 degrees  

    //math for sending power into motors
    s = sin(theta - pi/4); // sin value for motors
    c = cos(theta - pi/4); // cos value for motors
    mx = std::max(abs(s), abs(c)); // reaches max motor value if in absolute direction

    //assigns power to vars for motors
    leftFront = pw * s/mx + turn;
    rightFront = pw * c/mx - turn;
    leftBack = pw * c/mx + turn;
    rightBack = pw * s/mx - turn;

    //spins motors
    RFM.spin(vex::forward, rightFront, vex::percent);
    LFM.spin(vex::forward, leftFront, vex::percent);
    RBM.spin(vex::forward, rightBack, vex::percent);
    LBM.spin(vex::forward, leftBack, vex::percent);

    //DRIVER CONTROL====================================================================================
    
    /* 

      Add buttons here for controlling other motors

    */

    wait(20, msec); 
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
