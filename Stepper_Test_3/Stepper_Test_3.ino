#include <AccelStepper.h>
#include <MultiStepper.h>

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

const byte buttons[] = { 2,3,14 };

void setup() {
  // put your setup code here, to run once:
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  for (int i = 0; i < sizeof(buttons); i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Serial.begin(115200);
  stepper1.setMaxSpeed(1500);
  stepper1.setAcceleration(5000);
  stepper2.setMaxSpeed(1500);
  stepper2.setAcceleration(5000);
  stepper3.setMaxSpeed(1500);
  stepper3.setAcceleration(5000);
}

void loop()
{
  for (int i = 0; i < sizeof(buttons); i++)
  {
    if(!digitalRead(buttons[i]))
    {
      switch(i)
      {
        case 0:
          stepper1.moveTo(0);
          stepper2.moveTo(0);
          stepper3.moveTo(0);
          break;
        case 1:
          stepper1.moveTo(1500);
          stepper2.moveTo(1500);
          stepper3.moveTo(1500);
          break;
        case 2:
          stepper1.moveTo(3000);
          stepper2.moveTo(3000);
          stepper3.moveTo(3000);
          break;
      }
    }
    
  }
  stepper1.run();
  stepper2.run();
  stepper3.run();
}
