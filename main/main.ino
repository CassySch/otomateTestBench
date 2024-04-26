#include "commandInputs.h"
EnVar command;
void setup() {
  Serial.begin(115200);
}
void loop() {
  command.processRequest();
}