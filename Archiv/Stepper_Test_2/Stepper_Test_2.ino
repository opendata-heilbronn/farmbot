#include <AccelStepper.h>
#include <MultiStepper.h>

#define VERSION "v0.0.1"
#define BAUD 115200
#define bufSize 64
//char buf[bufSize];
String buf = "                                                                ";
byte bufIdx;
bool mode_abs=false;
const float XmmToStepsFactor = 5.0167224080267558528428093645485,
            YmmToStepsFactor = 5.0167224080267558528428093645485,
            ZmmToStepsFactor = 25;
            

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
long positions[3];

void switchSteppers(bool on)
{
  digitalWrite(X_ENABLE_PIN, !on);
  digitalWrite(Y_ENABLE_PIN, !on);
  digitalWrite(Z_ENABLE_PIN, !on);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  help();
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  switchSteppers(true);
  stepper1.setMaxSpeed(1500);
  stepper1.setAcceleration(2500);
  stepper2.setMaxSpeed(1500);
  stepper2.setAcceleration(2500);
  stepper3.setMaxSpeed(1500);
  stepper3.setAcceleration(5000);
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);
  ready();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available())
  {
    serialListener();
  }
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
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode"));
  Serial.println(F("G92 [X(steps)] [Y(steps)]; - change logical position"));
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
  stepper1.moveTo(curX);
  stepper2.moveTo(curY);
  stepper3.moveTo(curZ);
  /*positions[0] = curX;
  positions[1] = curY;
  positions[2] = curZ;
  steppers.moveTo(positions);*/
  Serial.println(curX);
  Serial.println(curY);
  Serial.println(curZ);
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
    case 90:  mode_abs=1;  break;  // absolute mode
    case 91:  mode_abs=0;  break;  // relative mode
  }
  cmd = parsenum('M',-1);
  switch(cmd) {
    case 18:   switchSteppers(false);
    case 19:   switchSteppers(true);
    case 100:  help();  break;
    case 114:  printPos();  break;
    default:  break;
  }
  
}

