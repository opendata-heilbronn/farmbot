#include <AccelStepper.h>
#include "const.h"
#include "stepper.h"
#include "vars.h"
#include "gcode.h"
#include "gadgets.h"

void setup() {
  Serial.begin(BAUD);
  //help();
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MIN_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);
  setSpeed(axisSpeed, axisAccel);
  switchSteppers(true);
  initGadgets();

  ready();
  delay(1000);
  //Serial.println("homing started");
  home();
}


void loop() {

  if(Serial.available())
  {
    serialListener();
  }

  if(homingInProgress)
    checkHome();
  /*else if(pickupInProgress)
    checkPickup();*/

  //Check all axeses
  for(int i = 0; i < 3; i++)
  {
    bool stateMin = !digitalRead(minEndSwitch[i]);
    bool stateMax = !digitalRead(maxEndSwitch[i]);

    short distance = stepperAxis[i]->distanceToGo();

    //Is this axis still running?
    if(stepperAxis[i]->isRunning()){

      //Did it hit the Min Switch?
      if(stateMin &&  distance < 0){
        
        stepperAxis[i]->setCurrentPosition(0);
        stepperAxis[i]->moveTo(stepperAxis[i]->currentPosition()+15);

      //Did it hit the Max Switch?
      }else if(stateMax && distance > 0){
        
        switch(i){
          case 0:
            stepperAxis[i]->setCurrentPosition(22784);
          break;
        }
        
        stepperAxis[i]->moveTo(stepperAxis[i]->currentPosition()-15);

      //Nothing hitted, we are fine!  
      }else{

        //Has the Z-Axis already stopped?
        if((i != 2 && stepperAxis[2]->distanceToGo() == 0) || (i == 2 && stepperAxis[2]->distanceToGo() != 0)){
          stepperAxis[i]->run();
        }
      }
      
    }
  }

  //Have we stopped? If yes: Report it to the Host
  if(!stopped && !stepperAxis[0]->isRunning() && !stepperAxis[1]->isRunning() && !stepperAxis[2]->isRunning()){
    stopped = true;
    setSpeed(axisSpeed, axisAccel);
    Serial.println("ok");  
  }

}
