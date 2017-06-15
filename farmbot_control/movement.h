#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "general.h"

void switchSteppers(bool on)
{
  digitalWrite(X_ENABLE_PIN, !on);
  digitalWrite(Y_ENABLE_PIN, !on);
  digitalWrite(Z_ENABLE_PIN, !on);
}


void setSpeed(const float* speedArr, const float* accelArr) //TODO test if works
{
  for(int i = 0; i < 3; i++)
  {
    stepperAxis[i]->setMaxSpeed    (speedArr[i]);
    stepperAxis[i]->setAcceleration(accelArr[i]);
  }
}

bool checkHome()
{
  int stillHoming = 3; //count of unhomed axes
  for(int i = 0; i < 3; i++) //check for all 3 axes
  {
    //Serial.print(curHomingMode[i]);
    //Serial.print(" ");
    switch(curHomingMode[i])
    {
      case runHome:
        if(!digitalRead(minEndSwitch[i]))
        {
          stepperAxis[i]->stop();
          stepperAxis[i]->moveTo(stepperAxis[i]->currentPosition()+100); //move some distance away from sensor
          curHomingMode[i] = moveAway;
        }
        break;
      case moveAway:
        if(!stepperAxis[i]->isRunning())
        {
          //setSpeed(calibSpeed, calibAccel);
          stepperAxis[i]->setMaxSpeed    (calibSpeed[i]);
          stepperAxis[i]->setAcceleration(calibAccel[i]);
          stepperAxis[i]->moveTo(-100000);
          curHomingMode[i] = calibrate;
        }
        break;
      case calibrate:
        if(!digitalRead(minEndSwitch[i]))
        {
          stepperAxis[i]->stop();
          stepperAxis[i]->setCurrentPosition(0);
          curHomingMode[i] = homeDone;
        }
        break;
      case homeDone:
        stillHoming--;
        break;
    }
  }
  if(!stillHoming) //returns true, if all axes are at their endStops
  {
    homingInProgress = false;
    setSpeed(axisSpeed, axisAccel);
    ready();
    Serial.println("ok");
  }
  return !stillHoming;
}


void home()
{
  homingInProgress = true;
  if(!checkHome()) //check if homing is not done
  {
    setSpeed(homingSpeed, homingAccel);
    for(int i = 0; i < 3; i++)
    {
      //Serial.println(stepperAxis[i]->maxSpeed());
      curHomingMode[i] = runHome;
      stepperAxis[i]->moveTo(-100000);
    }
  }
}


//returns false if any axes is still running
bool isStopped()
{
  bool stopped = true;
  for(int i = 0; i < 3; i++)
  {
    stopped = stopped && !stepperAxis[i]->isRunning();
  }
  return stopped;
}
#endif
