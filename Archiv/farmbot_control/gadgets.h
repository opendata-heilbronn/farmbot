#ifndef GADGETS_H
#define GADGETS_H
#define VAC_PUMP 40

void initGadgets(){
  pinMode(VAC_PUMP, OUTPUT);
}

void turnVacOn(){
  digitalWrite(VAC_PUMP, HIGH);
}

void turnVacOff(){
  digitalWrite(VAC_PUMP, LOW);
}

#endif
