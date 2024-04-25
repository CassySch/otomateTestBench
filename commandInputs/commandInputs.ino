#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "filtering.h"

#define MAX_INPUT_SIZE 256

void setup() {
  Serial.begin(115200);
}

void loop() {
  getRequest();
}

void extractVals(char inputBuffer[MAX_INPUT_SIZE]){

struct EnVar vals;
const char* commandType;
int i = 0;
  // Parse the JSON object
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, inputBuffer);
  // Check for parsing errors
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
  } else {
    // Iterate over the members of the JSON object
for (JsonPair member : doc.as<JsonObject>()) {
  i++;
  Serial.println(i);
  const char* currentKey = member.key().c_str();
  
  Serial.println(currentKey);
    // Extract the key and value of each member
    if ((strcmp(currentKey,"command")== 0 ) && member.value() == "temperature") {
         commandType = member.value();
         Serial.println("command select");
    }

    else if((strcmp(currentKey, "indoor") == 0) && strcmp(commandType,"temperature") == 0){
      vals.tempIndoor = member.value().as<float>();
      Serial.println(vals.tempIndoor);
      Serial.println("indoor temp set");
    }

    else if((strcmp(currentKey, "outdoor") == 0) && strcmp(commandType,"temperature") == 0) {
        vals.tempOutdoor = member.value().as<float>();
        Serial.println("outdoor temp set"); 
        Serial.println(vals.tempOutdoor);
    }

    if ((strcmp(currentKey,"command")== 0 ) && member.value().as<String>() == "humidity") {
         commandType = member.value();
         Serial.println("Hum command");
    }

    else if((strcmp(currentKey, "indoor") == 0) && strcmp(commandType,"humidity") == 0){
      vals.humIndoor = member.value().as<float>();
      Serial.println(vals.humIndoor);
      Serial.println(" Hum indoor");
    }

    else if((strcmp(currentKey,"outdoor") == 0) && strcmp(commandType,"humidity") == 0) {
        vals.humOutdoor = member.value().as<float>();
        Serial.println(vals.humOutdoor);
        Serial.println("Hum outdoor");
    }

}

// Output the values
Serial.println("Indoor Temperature: " + String(vals.tempIndoor));
Serial.println("Outdoor Temperature: " + String(vals.tempOutdoor));
Serial.println("Outdoor Humidity: " + String(vals.humOutdoor));
Serial.println("Indoor Humidity: " + String(vals.humIndoor));

  }
  // Wait for a short moment before reading again
  delay(1000);
}     

void getRequest(){
  Serial.println("Enter JSON object:");
  while (!Serial.available()) {} // Wait for user input

  // Read input until a newline character is encountered
  char inputBuffer[MAX_INPUT_SIZE];
  unsigned int index = 0;
  while (index < MAX_INPUT_SIZE - 1) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        break; // Exit the loop when newline character is encountered
      } else {
        inputBuffer[index++] = c; // Store character in inputBuffer
      }
    }
  }
  inputBuffer[index] = '\0'; // Add NULL at end of input buffer

  extractVals(inputBuffer);
}
