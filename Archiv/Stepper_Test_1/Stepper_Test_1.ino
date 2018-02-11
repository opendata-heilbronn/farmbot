// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: HRFMessage.h,v 1.1 2009/08/15 05:32:58 mikem Exp mikem $

#include <AccelStepper.h>

#define X_ENABLE_PIN       38

const byte buttons[] = { 2,3,14 };

// Define a stepper and the pins it will use
AccelStepper stepper(1, 54, 55); //InterfaceType (driver), stepPin, dirPin

void setup()
{  
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN    , LOW);
  for (int i = 0; i < sizeof(buttons); i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Serial.begin(115200);
  stepper.setMaxSpeed(1500);
  stepper.setAcceleration(5000);
}
bool forward = true;
void loop()
{
  for (int i = 0; i < sizeof(buttons); i++)
  {
    //Serial.print(digitalRead(buttons[i]));
    if(!digitalRead(buttons[i]))
    {
      switch(i)
      {
        case 0:
          stepper.moveTo(0);
          break;
        case 1:
          stepper.moveTo(1500);
          break;
        case 2:
          stepper.moveTo(3000);
          break;
      }
    }
    
  }
  Serial.println();
    /*if (stepper.distanceToGo() == 0)
    {
	// Random change to speed, position and acceleration
	// Make sure we dont get 0 speed or accelerations
	delay(1000);
  
  if(forward)
  {
    stepper.moveTo(1200);
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(5000);
  forward = false;
  }
  else
  {
    stepper.moveTo(0);
  stepper.setMaxSpeed(10000);
  stepper.setAcceleration(5000);
  forward = true;
  }
	
    }*/
    stepper.run();
}
