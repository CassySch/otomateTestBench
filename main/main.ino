#include "commandInputs.h"
#include "relays.h"

EnVar command;
void setup() {
  Serial.begin(115200);
  relayInit();
  pwmInitTimer0(80,3000000,1000000,4);
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