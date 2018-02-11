#include "pitches.h"
#include "songs.h"

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

const byte bPin = X_STEP_PIN;
int steps = 0;
long oldTempo;
long userTempo = 120;

void setup() {
  // put your setup code here, to run once:
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(X_DIR_PIN, HIGH);
}

void buzz(int targetPin, long frequency, long length, long tempo) {
  long delayValue = 1000000/frequency/2;
  long numCycles = frequency * length/ (tempo/.3);
  for (long i=0; i < numCycles; i++){
    digitalWrite(targetPin,HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin,LOW);
    delayMicroseconds(delayValue);
    steps++;
      //digitalWrite(X_DIR_PIN, !digitalRead(X_DIR_PIN));
  }
}


void playNote(int noteInt, long length, long tempo = oldTempo,long breath = 0){
  oldTempo = tempo;
  length = length - breath;
  buzz(bPin, noteInt, length, tempo);
  if(breath > 0) { //take a short pause or 'breath' if specified
    delay(breath);
  }
  if(steps >= 3000)
    {
      steps = 0;
      digitalWrite(X_DIR_PIN, !digitalRead(X_DIR_PIN)); //Invert Stepper direction
    }
    delay(1);
  //digitalWrite(X_DIR_PIN, !digitalRead(X_DIR_PIN));
}


void loop() {
  // put your main code here, to run repeatedly:
  playSong("He's a Pirate");
  playSong("Can Can");
  playSong("Song of Storms");
}



