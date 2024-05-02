#include "commandInputs.h"
#include "relays.h"

int numPin;
EnVar command;
void setup() {
  Serial.begin(115200);
  pinMode(4,OUTPUT);
  relayInit();
  pwmInitTimer0(80);
}
void loop() { 
  JsonDocument doc;
  char inputArray[MAX_INPUT_SIZE + 1];
  
  //Serial.println(numPin);
  //const char* json = "{\"temperature\":{\"indoor\":14,\"outdoor\":20}}";
  //deserializeJson(doc, json);
  setPwm(3000000,1000000,4);
  const char* request = getSerialJson(inputArray);
  //Serial.println(request);
  validateJson(request,&doc);
  command.applyValues(&doc);
  
}