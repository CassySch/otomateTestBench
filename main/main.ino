#include "commandInputs.h"

EnVar command;
void setup() {
  Serial.begin(115200);
}
void loop() { 
  JsonDocument doc;
  
  //const char* json = "{\"temperature\":{\"indoor\":24,\"outdoor\":20}}";
  //deserializeJson(doc, json);

  getSerialJson(&doc);
  command.applyValues(&doc);
}