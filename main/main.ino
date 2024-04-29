#include "commandInputs.h"

EnVar command;
void setup() {
  Serial.begin(115200);
  pinMode(RELAY_1, INPUT);
  pinMode(RELAY_2, INPUT);
  pinMode(RELAY_3, INPUT);
  pinMode(RELAY_4, INPUT);
  pinMode(RELAY_5, INPUT);
  pinMode(RELAY_6, INPUT);
}
void loop() { 
  JsonDocument doc;
  
  //const char* json = "{\"temperature\":{\"indoor\":24,\"outdoor\":20}}";
  //deserializeJson(doc, json);

  getSerialJson(&doc);
  command.applyValues(&doc);
}