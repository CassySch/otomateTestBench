#include "commandInputs.h"

EnVar command;
void setup() {
  Serial.begin(115200);
  pinMode(RELAY_1, input);
  pinMode(RELAY_2, input);
  pinMode(RELAY_3, input);
  pinMode(RELAY_4, input);
  pinMode(RELAY_5, input);
  pinMode(RELAY_6, input);
}
void loop() { 
  JsonDocument doc;
  
  //const char* json = "{\"temperature\":{\"indoor\":24,\"outdoor\":20}}";
  //deserializeJson(doc, json);

  getSerialJson(&doc);
  command.applyValues(&doc);
}