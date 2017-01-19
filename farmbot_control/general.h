#ifndef GENERAL_H
#define GENERAL_H

void ready() {
  bufIdx=0; // clear input buffer
  String buf = "                                                                ";
  Serial.print(F("> ")); // signal ready to receive input
}

#endif
