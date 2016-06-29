#include <Arduino.h>

#include <AccelStepper.h>
#include <MultiStepper.h>



#define VERSION "v0.2"
#define BAUD 115200
//                           X     Y     Z                         X     Y     Z
const float axisSpeed[3] = {1500},                axisAccel[3] = {2500, 2500, 5000},
          homingSpeed[3] = {500},               homingAccel[3] = {50000},
           calibSpeed[3] = {100},                calibAccel[3] = {50000};

//position constants
const long toolsPos[] = {10,10,0},   //first holder position (top)
           toolPitch = 10,           //how far tool holders are spaced apart
           toolPickupDepth = 100,    //how far to move down to pickup tool from holder
           toolPutBackDepth = 101,   //how far to move down to put tool back in holder
           toolMoveOut = 100,        //how far to move tool out of holder
           toolMoveUp = 100;         //how far to move up after picking up / putting back tool


const float XmmToStepsFactor = 5.0167224080267558528428093645485,
            YmmToStepsFactor = 5.0167224080267558528428093645485,
            ZmmToStepsFactor = 25;


#define bufSize 64
//char buf[bufSize];
String buf = "                                                                ";
byte bufIdx;
bool mode_abs = false, homingInProgress = false, pickupInProgress = false;
long tmpPickupPos[3];

enum homingModes {homeDone, runHome, moveAway, calibrate};
homingModes curHomingMode[3] = {runHome}; //current state of axes
enum tools {noTool, toolA, toolB, toolC, toolD}; //can also be used as just ids due to enum
tools currentTool = noTool, putBackTool = noTool;
enum pickupModes {p_done, p_goOverTools, p_moveDown, p_moveTool, p_moveUp, p_goHome};
pickupModes currentPickupMode = p_done;



long curX, curY, curZ;

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

AccelStepper stepper1(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper2(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepper3(1, Z_STEP_PIN, Z_DIR_PIN);
MultiStepper steppers;
AccelStepper* stepperAxis[] = {&stepper1, &stepper2, &stepper3};
long positions[3];
const int endSwitch[] = {X_MIN_PIN, Y_MIN_PIN, Z_MIN_PIN};


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


void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  help();
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  setSpeed(axisSpeed, axisAccel);
  for(int i = 0; i < 3; i++)
  {
    /*stepperAxis[i]->setMaxSpeed    (axisSpeed[i]);
    stepperAxis[i]->setAcceleration(axisAccel[i]);*/
    steppers.addStepper(*(stepperAxis[i])); //not sure if works
  }
  /*steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);*/
  switchSteppers(true);
  ready();

}


void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    serialListener();
  }
  if(homingInProgress)
    checkHome();
  else if(pickupInProgress)
    checkPickup();
  stepper1.run();
  stepper2.run();
  stepper3.run();
  //steppers.run();

}


void help() {
  Serial.print(F("Farmbot Motor controller "));
  Serial.println(VERSION);
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G01 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G04 P[seconds]; - delay"));
  Serial.println(F("G28; - calibrate axes (homing)"));
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode [WIP]"));
  Serial.println(F("G92 [X(steps)] [Y(steps)]; - change logical position [WIP]"));
  Serial.println(F("T(ToolID); - change tool to ToolID"));
  Serial.println(F("M18; - disable motors"));
  Serial.println(F("M19; - enable motors"));
  Serial.println(F("M100; - this help message"));
  Serial.println(F("M114; - report position and feedrate"));
}


void ready() {
  bufIdx=0; // clear input buffer
  String buf = "                                                                ";
  Serial.print(F("> ")); // signal ready to receive input
}


void goHome()
{
  long homePos[] = {0};
  steppers.moveTo(homePos);
}


bool isStopped()
{
  bool stopped = true;
  for(int i = 0; i < 3; i++)
  {
    stopped = !stepperAxis[i]->isRunning();
  }
  return stopped; //returns false if any axes is still running
}


void pickupTool(tools tool)
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
          goHome();
        }
        else //after putting toool back and picking new up
        {
          if(putBackTool == 255) //if no new tool is meant to be picked up
          {
            currentPickupMode = p_goHome;
            goHome();
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
}


void home()
{
  homingInProgress = true;
  if(checkHome()) //check if homing is necessary
  {
    setSpeed(homingSpeed, homingAccel);
    for(int i = 0; i < 3; i++)
    {
      /*stepperAxis[i]->setMaxSpeed    (homingSpeed);
      stepperAxis[i]->setAcceleration(homingAccel);*/
      curHomingMode[i] = runHome;
      stepperAxis[i]->moveTo(-100000);
    }
  }
}


bool checkHome()
{
  int stillHoming = 3; //count of unhomed axes
  for(int i = 0; i < 3; i++) //check for all 3 axes
  {
    switch(curHomingMode[i])
    {
      case runHome:
        if(digitalRead(endSwitch[i]))
        {
          stepperAxis[i]->stop();
          stepperAxis[i]->moveTo(stepperAxis[i]->currentPosition()+100); //move some distance away from sensor
          curHomingMode[i] = moveAway;
        }
        break;
      case moveAway:
        if(!stepperAxis[i]->isRunning())
        {
          setSpeed(calibSpeed, calibAccel);
          stepperAxis[i]->moveTo(-100000);
          curHomingMode[i] = calibrate;
        }
        break;
      case calibrate:
        if(digitalRead(endSwitch[i]))
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
    homingInProgress = false;
  return !stillHoming;
}


void serialListener()
{
  char c = Serial.read();
  //Serial.print(c); //pong back the received command
  if(bufIdx < bufSize)
  {
    buf[bufIdx] = c;
    bufIdx++;
  }
  if(c=='\n')
  {
    //Serial.print(F("\r\n")); //pong back line feed
    buf[bufIdx] = 0; //Strings must end with 0
    Serial.println(buf);
    processCommand();
    ready(); //ready for new command
  }
}


float parsenum(char code, float val)
{
  byte start = buf.indexOf(code);
  if(start == 255)
  {
    return val;
  }
  byte ende = buf.substring(start).indexOf(" ");
  String result = buf.substring(start+1,start+ende);
  float resFloat = result.toFloat();
  return resFloat;
}


void newPos()
{
  positions[0] = curX;
  positions[1] = curY;
  positions[2] = curZ;
  stepper1.moveTo(positions[0]);
  stepper2.moveTo(positions[1]);
  stepper3.moveTo(positions[2]);
  //steppers.moveTo(positions);
  Serial.println(positions[0]);
  Serial.println(positions[1]);
  Serial.println(positions[2]);
}


void printPos()
{
  Serial.print("X");
  Serial.println(stepper1.currentPosition()/XmmToStepsFactor);
  Serial.print("Y");
  Serial.println(stepper2.currentPosition()/YmmToStepsFactor);
  Serial.print("Z");
  Serial.println(stepper3.currentPosition()/ZmmToStepsFactor);
}


void pause(long ms) {
  delay(ms/1000);
  delayMicroseconds(ms%1000);  // delayMicroseconds doesn't work for values > ~16k.
}


void processCommand()
{
  int cmd = parsenum('G',-1);
  //Serial.println(cmd);
  switch(cmd)
  {
    case  0:
    case  1:
      /*Serial.println(parsenum('X',(mode_abs?curX:0)) + (mode_abs?0:curX));
      curX = round((parsenum('X',(mode_abs?curX:0)) + (mode_abs?0:curX))*XmmToStepsFactor);
      curY = round((parsenum('Y',(mode_abs?curY:0)) + (mode_abs?0:curY))*YmmToStepsFactor);
      curZ = round((parsenum('Z',(mode_abs?curZ:0)) + (mode_abs?0:curZ))*ZmmToStepsFactor);*/
      curX = round((parsenum('X', 0)*XmmToStepsFactor));
      curY = round((parsenum('Y', 0)*YmmToStepsFactor));
      curZ = round((parsenum('Z', 0)*ZmmToStepsFactor));
      newPos();
      break;
    case  4:  pause(parsenum('P',0)*1000); break;
    case 28:  home(); break;
    case 90:  mode_abs=1;  break;  // absolute mode
    case 91:  mode_abs=0;  break;  // relative mode
    default:  break;
  }
  cmd = parsenum('M',-1);
  switch(cmd) {
    case 18:   switchSteppers(false);
    case 19:   switchSteppers(true);
    case 100:  help();  break;
    case 114:  printPos();  break;
    default:  break;
  }
  byte toolID = parsenum('T', -1);
  if(toolID != -1)
    pickupTool(static_cast<tools>(toolID));
}
