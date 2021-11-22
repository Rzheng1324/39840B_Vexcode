// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         20              
// LeftMotor            motor         10              
// arm                  motor         1               
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         20              
// LeftMotor            motor         9               
// arm                  motor         1               
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         2               
// LeftMotor            motor         9               
// arm                  motor         1               
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         2               
// LeftMotor            motor         9               
// arm                  motor         10              
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         2               
// LeftMotor            motor         9               
// arm                  motor         10              
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         1               
// LeftMotor            motor         9               
// arm                  motor         10              
// wrist                motor         7               
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         1               
// LeftMotor            motor         9               
// arm                  motor         10              
// wrist                motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightMotor           motor         1               
// LeftMotor            motor         9               
// arm                  motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// wrist                motor         7               
// arm                  motor         10              
// claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
#include <iostream>
using namespace vex;

competition Competition;
void pre_auton(void){
  vexcodeInit();
}
void autonomous(void){

  arm.setPosition(0,degrees);
  while(arm.position(degrees) > -1287.6){
    arm.spinFor(reverse, 10,degrees);
  std::cout << arm.position(degrees) << std::endl; 

  }
  wait(10, seconds);


}
void usercontrol(void){
  //double turnImportance = 0.5;
  while (1){

    double turnVal = -((Controller1.Axis1.position(percent)));
    double fowardVal = ((Controller1.Axis3.position(percent)));

    double turnVolts = turnVal * 0.12;
    double fowardVolts = fowardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0)) /** turnImportance*/;

    LeftMotor.spin(forward, fowardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, -(fowardVolts + turnVolts), voltageUnits::volt);

    Brain.Screen.print(LeftMotor.power());
    Brain.Screen.newLine();

    // arm
    if (Controller1.ButtonL2.pressing() == true){
      arm.spin(reverse, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL1.pressing() == true){
      arm.spin(forward, 100, velocityUnits::pct);
    }
    else{
      arm.stop(brakeType::hold);
    }


/*
    // wrist
    if (Controller1.ButtonX.pressing() == true){
      wrist.spin(forward);
    }
    else if(Controller1.ButtonB.pressing() == true){
      wrist.spin(reverse);
    }
    else{
      wrist.stop(brakeType::hold);
    }


    // claw
    if (Controller1.ButtonR2.pressing()){
      claw.spin(forward);
    }
    if (Controller1.ButtonR1.pressing()){
      claw.spin(reverse);
    }
    */

    //Don't want motor to stop moving when you let go.
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
