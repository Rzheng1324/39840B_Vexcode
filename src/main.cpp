

#include "vex.h"
#include <cmath>
#include <iostream>
using namespace vex;

competition Competition;
void pre_auton(void){
  vexcodeInit();
}
void autonomous(void){
  LeftMotor.startRotateFor(5.81, rotationUnits::rev);
  RightMotor.startRotateFor(5.81, rotationUnits::rev);
  claw.spin(forward);
  LeftMotor.startRotate(-5.81, rotationUnits::rev);
  RightMotor.startRotateFor(-5.81, rotationUnits::rev);
  for (int i = 0; i < 20; i++){
    LeftMotor.spin(forward);
    RightMotor.spin(reverse);
  }
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
      arm.spin(reverse, 100, vex::velocityUnits::pct);
      claw.spin(forward);
    }
    if (Controller1.ButtonR1.pressing()){
      claw.spin(reverse);
    }
    else{
      claw.stop(brakeType::coast);
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
