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
  char inputArray[MAX_INPUT_SIZE + 1];

  //const char* json = "{\"temperature\":{\"indoor\":14,\"outdoor\":20}}";
  //deserializeJson(doc, json);

  const char* request = getSerialJson(inputArray);
  //Serial.println(request);
  validateJson(request,&doc);
  command.applyValues(&doc);
}