#ifndef VARS_H
#define VARS_H

char buf[bufSize];
String bufStr;
byte bufIdx;
bool mode_abs = false, homingInProgress = false, pickupInProgress = false;
long tmpPickupPos[3];
long distToGo[3] = {0, 0, 0};
bool stopped = true;
bool failed = false;

long positions[3];
#endif
