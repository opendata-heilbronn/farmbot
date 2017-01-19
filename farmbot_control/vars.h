#ifndef VARS_H
#define VARS_H

char buf[bufSize];
String bufStr;
byte bufIdx;
bool mode_abs = false, homingInProgress = false, pickupInProgress = false;
long tmpPickupPos[3];

long positions[3];
#endif
