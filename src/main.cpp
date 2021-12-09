#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// claw                 motor         4               
// LeftMotor            motor         10              
// RightMotor           motor         20              
// arm                  motor         12              
// Controller1          controller                    
// MotorGroup17         motor_group   17, 11          
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <cmath>
#include <iostream>
using namespace vex;

competition Competition;
void pre_auton(void){
  vexcodeInit();
}
void autonomous(void){
  arm.setPosition(0, degrees);
  while(1){
    arm.setVelocity(900, percent);
    //LeftMotor.setVelocity(100, percent);
    //RightMotor.setVelocity(900, percent);
   /* while(arm.position(degrees) > 0){
      LeftMotor.stop();
      RightMotor.stop();
      arm.spin(forward);
      
    }*/
    arm.spin(forward);
    Brain.Screen.print(arm.position(degrees));
    Brain.Screen.print("   ");
    if (arm.position(degrees) > 1440 * 7 + 180){
      RightMotor.setVelocity(300, percent);
      //RightMotor = motor(PORT20, ratio18_1, true);
    //  motor_group mo = motor_group(LeftMotor, RightMotor);
      
      arm.stop();
      claw.spin(reverse);
      //LeftMotor.rotateFor(-5.81, rotationUnits::rev, false);
     // mo.rotateFor(5.81, rotationUnits::rev, false);
      while (LeftMotor.position(rotationUnits::rev) <2 && RightMotor.position(rotationUnits::rev) < 2){
        LeftMotor.spin(forward, 100, voltageUnits::volt);
        RightMotor.spin(forward, -100, voltageUnits::volt);
      }
      //LeftMotor.spinFor(forward, 5.81, rotationUnits::rev);
      //RightMotor.spinFor(reverse, 5.81, rotationUnits::rev, false);
      //LeftMotor.spinFor(forward, 5.81, rotationUnits::rev, false);
      //RightMotor.rotateFor(5.81, rotationUnits::rev, false);
      claw.spin(reverse);
      break;
    }
    claw.spin(forward);
    wait(100, msec);
    //RightMotor.spinFor(forward, 5.81, rotationUnits::rev, false);
    //LeftMotor.spinFor(reverse, 5.81, rotationUnits::rev, false);
  }
  RightMotor = motor(PORT20, ratio18_1, false);
  
  wait(1, sec);
  //LeftMotor.startRotateFor(5.81, rotationUnits::rev);
 //RightMotor.startRotateFor(5.81, rotationUnits::rev);
  claw.spin(forward);
  wait(1, sec);
  while (LeftMotor.position(rotationUnits::rev) <1 && RightMotor.position(rotationUnits::rev) < 1){
        LeftMotor.spin(forward, -10, voltageUnits::volt);
        RightMotor.spin(forward, 10, voltageUnits::volt);
  }
  //LeftMotor.startRotateFor(-5.81, rotationUnits::rev);
  //RightMotor.startRotateFor(-5.81, rotationUnits::rev);
  //for (int i = 0; i < 20; i++){
    //LeftMotor.spin(forward);
    //RightMotor.spin(reverse);
  //}
  
  /*while (true){
    LeftMotor.spin(forward);
    RightMotor.spin(reverse);
    if (Vision1.objectCount > 0){
      
      for (int i = 0; i < Vision1.objectCount; i++){
        if (20 > Vision1.objects[i].centerX - 157.2 > -20){
          LeftMotor.stop();
          RightMotor.stop();
          LeftMotor.spin(forward);
          RightMotor.spin(forward);
        }
      }
    }
  }*/
}
void usercontrol(void){
  //double turnImportance = 0.5;
  while (1){
    LeftMotor.setVelocity(200, percent);
    RightMotor.setVelocity(200, percent);
    double turnVal = -((Controller1.Axis1.position(percent)));
    double fowardVal = ((Controller1.Axis3.position(percent)));

    double turnVolts = turnVal * 0.12;
    double fowardVolts = fowardVal * 0.12 * (1 - (std::abs(turnVolts)/12.0)) /** turnImportance*/;

    LeftMotor.spin(forward, fowardVolts - turnVolts, voltageUnits::volt);
    RightMotor.spin(forward, -(fowardVolts + turnVolts), voltageUnits::volt);

    Brain.Screen.print(LeftMotor.power());
    Brain.Screen.newLine();
    arm.setVelocity(900, percent);
    // arm
    if (Controller1.ButtonL1.pressing() == true){
      arm.spin(reverse, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing() == true){
      arm.spin(forward, 100, velocityUnits::pct);
    }
    else{
      arm.stop(brakeType::hold);
    }


    // claw
    if (Controller1.ButtonR2.pressing()){
      arm.spin(reverse, 0.01, vex::velocityUnits::pct);
      claw.spin(forward);//200, percent);
    }
    if (Controller1.ButtonR1.pressing()){
      claw.spin(reverse);//, 200, percent);
    }

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
