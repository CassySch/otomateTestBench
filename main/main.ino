#include "commandInputs.h"
#include "relays.h"
#include "DAC.h"

hw_timer_t * timer = NULL;

EnVar command;
void setup() {
  Serial.begin(115200);
  relayInit();
  DacCommunicationInit(DAC_1_SDA_PIN,DAC_1_SCL_PIN);
  send_to_dac(DAC_1_ADDRESS,3.0);

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