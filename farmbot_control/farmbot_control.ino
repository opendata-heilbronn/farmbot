#include <AccelStepper.h>
#include "const.h"
#include "stepper.h"
#include "vars.h"
#include "gcode.h"

void setup() {
  Serial.begin(BAUD);
  help();
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

  ready();
  delay(1000);
  Serial.println("homing started");
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

  for(int i = 0; i < 3; i++)
  {
    stepperAxis[i]->run();
  }
}

//TODO: rewrite for AccelStepper Array
/*void pickupTool(tools tool)
{
  if(currentTool != noTool)
  {
    tmpPickupPos[0] = toolsPos[0] + toolMoveOut;
    tmpPickupPos[1] = toolsPos[1]+currentTool*toolPitch; //calculate y of the corresponding tool holder
    putBackTool = tool; //save tool to pickup after current tool was put back
    if(tool == noTool) //if the current tool is meant to be put back and no new tool to be picked up
    {
      putBackTool = static_cast<tools>(255); //dummy tool, else the state machine would act like it is in pickup mode instead of put back mode [probably smashing the tool to pieces]
    }
  }
  else
  {
    tmpPickupPos[0] = toolsPos[0];
    tmpPickupPos[1] = toolsPos[1]+tool*toolPitch; //calculate y of the corresponding tool holder
    currentTool = tool;
  }
  tmpPickupPos[2] = toolsPos[2];

  steppers.moveTo(tmpPickupPos);
  currentPickupMode = p_goOverTools;
}
*/

//TODO: rewrite for AccelStepper Array
/*
void checkPickup()
{
  switch(currentPickupMode)
  {
    case p_goOverTools:
      if(isStopped())
      {
        currentPickupMode = p_moveDown;
        tmpPickupPos[2] = (putBackTool == noTool) ? toolPickupDepth : toolPutBackDepth;  //tmpPickupPos for x/y will stay the same | set how far to move down based on putting tool back or picking it up
        steppers.moveTo(tmpPickupPos);
      }
      break;
    case p_moveDown:
      if(isStopped())
      {
        currentPickupMode = p_moveTool;
        tmpPickupPos[0] += (putBackTool == noTool) ? +toolMoveOut : -toolMoveOut; //tmpPickupPos for x/z will stay the same | move tool either in or out (put back / pick up)
        steppers.moveTo(tmpPickupPos);
      }
      break;
    case p_moveTool:
      if(isStopped())
      {
        currentPickupMode = p_moveUp;
        tmpPickupPos[2] -= toolMoveUp; //tmpPickupPos for x/y will stay the same
        steppers.moveTo(tmpPickupPos);
      }
      break;
    case p_moveUp:
      if(isStopped())
      {
        if(putBackTool == noTool)
        {
          currentPickupMode = p_goHome;
          home();
        }
        else //after putting toool back and picking new up
        {
          if(putBackTool == 255) //if no new tool is meant to be picked up
          {
            currentPickupMode = p_goHome;
            home();
          }
          else
          {
            currentPickupMode = p_goOverTools;
            currentTool = putBackTool;
            putBackTool = noTool;
            tmpPickupPos[0] = toolsPos[0];
            tmpPickupPos[1] = toolsPos[1]+currentTool*toolPitch; //calculate y of the corresponding tool holder
            //tmpPickupPos[2] = toolsPos[2];  //should stay at same height after putting back tool to avoid unnecessary z-movement
            steppers.moveTo(tmpPickupPos);
          }
        }
      }
      break;
    case p_goHome:
      if(isStopped())
      {
        ready();
      }

      break;
    default: break;
  }
}*/
