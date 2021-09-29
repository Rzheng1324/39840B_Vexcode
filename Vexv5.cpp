/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       ryanzheng                                                 */
/*    Created:      Tue Sep 28 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         1               
// LeftMotor            motor         9               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
using namespace vex;

competition Competition;
void pre_auton(void){
  vexcodeInit();
}
void autonomous(void){

}
void usercontrol(void){
  double turnImportance = 0.5;
  while (1){

    double turnVal = Controller1.Axis1.position(percent);
    double fowardVal = Controller1.Axis3.position(percent);

    double turnVolts = turnVal * 0.12;
    double fowardVolts = fowardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0)) * turnImportance;

    LeftMotor.spin(forward, fowardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, fowardVolts + turnVolts, voltageUnits::volt);


    wait(20, msec);
  }
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while(true){
    wait(100, msec);
  }
  
}
