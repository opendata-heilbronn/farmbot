#ifndef CONST_H
#define CONST_H

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

#define VERSION "v0.3"
#define BAUD 115200

#define bufSize 64

enum homingModes {homeDone, runHome, moveAway, calibrate};
homingModes curHomingMode[3] = {runHome, runHome, runHome}; //current state of axes
enum tools {noTool, toolA, toolB, toolC, toolD}; //can also be used as just ids due to enum
tools currentTool = noTool, putBackTool = noTool;
enum pickupModes {p_done, p_goOverTools, p_moveDown, p_moveTool, p_moveUp, p_goHome};
pickupModes currentPickupMode = p_done;
//                            X     Y     Z                           X       Y      Z
const float axisSpeed[3] = {1500, 1500, 1500},    axisAccel[3] =    {1500,  2500,   5000},
          homingSpeed[3] =  {250,  500,  500},    homingAccel[3] =  {5000,  10000, 10000},
           calibSpeed[3] =  {100,  100,  100},    calibAccel[3] =  {50000,  50000, 50000};

//position constants
const long toolsPos[] = {0,602,0},   //first holder position (top)
           toolPitch = 512,           //how far tool holders are spaced apart
           toolPickupDepth = 7500,    //how far to move down to pickup tool from holder
           toolPutBackDepth = 101,   //how far to move down to put tool back in holder
           toolMoveOut = 500,        //how far to move tool out of holder
           toolMoveUp = 500;         //how far to move up after picking up / putting back tool


const float XmmToStepsFactor = 5.0167224080267558528428093645485,
            YmmToStepsFactor = 5.0167224080267558528428093645485,
            ZmmToStepsFactor = 25;

#endif
