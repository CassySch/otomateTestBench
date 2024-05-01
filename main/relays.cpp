#include "commandInputs.h"

void EnVar::ReadRelays() {
  for (int i = 0; i < NUMRELAYS; i++) {
    relayVals[i] = digitalRead(relayArray[i]);
  }
}

void relayInit(){
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, INPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, INPUT);
  pinMode(RELAY_5, INPUT);
  pinMode(RELAY_6, INPUT);
}