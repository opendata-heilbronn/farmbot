#ifndef GENERAL_H
#define GENERAL_H

void ready() {
  bufIdx = 0; // clear input buffer
  for(int i = 0; i < sizeof(buf); i++)
  {
    buf[i] = 0;
  }
  bufStr = "";
  Serial.print(F("> ")); // signal ready to receive input
}

#endif
