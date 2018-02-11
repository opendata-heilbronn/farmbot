#ifndef GCODE_H
#define GCODE_H

#include "movement.h"
#include "gadgets.h"

void help() {
  Serial.print(F("Farmbot Motor controller "));
  Serial.println(VERSION);
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X(mm)] [Y(mm) Z(mm)]; - linear move"));
  Serial.println(F("G01 [X(steps)] [Y(steps) Z(steps)]; - linear move"));
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

float parsenum(char code, float val)
{
  byte start = bufStr.indexOf(code);
  if(start == 255)
  {
    return val;
  }
  byte end = bufStr.substring(start).indexOf(" ");
  String result = bufStr.substring(start+1,start+end);
  float resFloat = result.toFloat();
  return resFloat;
}


void newPos()
{
  for(int i = 0; i < 3; i++)
  {
    stepperAxis[i]->moveTo(positions[i]);
    distToGo[i] = stepperAxis[i]->distanceToGo();
  }

  stopped = false;
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
  switch(cmd)
  {
    case  0:
      positions[0] = round((parsenum('X', 0)*XmmToStepsFactor));
      positions[1] = round((parsenum('Y', 0)*YmmToStepsFactor));
      positions[2] = round((parsenum('Z', 0)*ZmmToStepsFactor));
      newPos();
      break;
    case  1:
      positions[0] = round(parsenum('X', 0));
      positions[1] = round(parsenum('Y', 0));
      positions[2] = round(parsenum('Z', 0));
      newPos();
      break;
    case  4:  pause(parsenum('P',0)*1000); break;
    case 28:  homingInProgress = true ; break;
    case 90:  mode_abs=1;  break;  // absolute mode
    case 91:  mode_abs=0;  break;  // relative mode
    case 92:  turnVacOn(); break;
    case 93:  turnVacOff(); break;
    default:  break;
  }
  cmd = parsenum('M',-1);
  switch(cmd) {
    case 18:   switchSteppers(false); break;
    case 19:   switchSteppers(true); break;
    case 100:  help();  break;
    case 114:  printPos();  break;
    default:  break;
  }
  byte toolID = parsenum('T', -1);
  //if(toolID != -1)
    //pickupTool(static_cast<tools>(toolID));
}



void serialListener()
{
  char c = Serial.read();
  if(bufIdx < bufSize)
  {
    buf[bufIdx] = c;
    bufIdx++;
  }
  if(c=='\n')
  {
    //buf[bufIdx] = 0; //Strings must end with 0
    //Serial.println(buf);
    bufStr = String(buf);
    processCommand();
    ready(); //ready for new command
  }
}

#endif
