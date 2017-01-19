#ifndef STEPPER_H
#define STEPPER_H

#include "const.h"

AccelStepper stepper1(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepper2(1, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper stepper3(1, Z_STEP_PIN, Z_DIR_PIN);
//MultiStepper steppers;
AccelStepper* stepperAxis[] = {&stepper1, &stepper2, &stepper3};

const int minEndSwitch[] = {X_MIN_PIN, Y_MIN_PIN, Z_MIN_PIN};
const int maxEndSwitch[] = {X_MAX_PIN, Y_MAX_PIN, Z_MAX_PIN};
#endif
