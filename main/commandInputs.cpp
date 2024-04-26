#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "commandInputs.h"

EnVar Vals;

void EnVar::extractVals(){

const char* commandType;
  // Parse the JSON object
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, Vals.inputBuffer);

  // Check for parsing errors
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
  } else {
    // Iterate over the members of the JSON object
for (JsonPair member : doc.as<JsonObject>()) {
  const char* currentKey = member.key().c_str();
  //command verification
    if (strcmp(currentKey,"command") == 0 && member.value().is<String>()) commandType = member.value();
  //Temperature 
    else if (strcmp(commandType,"temperature") == 0 && member.value().is<float>()) {
      if(strcmp(currentKey, "indoor") == 0) Vals.tempIndoor = member.value();
      else if(strcmp(currentKey, "outdoor") == 0) Vals.tempOutdoor = member.value();
    }
  //Humidity
    else if (strcmp(commandType,"humidity") == 0 && member.value().is<float>()) {
      if(strcmp(currentKey, "indoor") == 0) Vals.humIndoor = member.value();
      else if(strcmp(currentKey, "outdoor") == 0) Vals.humOutdoor = member.value();
    }
  //Wind
    else if(strcmp(commandType,"wind") == 0 && member.value().is<float>()) {
      if(strcmp(currentKey, "speed") == 0 ) Vals.windSpeed = member.value();
      else if(strcmp(currentKey,"direction") == 0) Vals.windDir = member.value();
    }
  //Rain
    else if(strcmp(commandType,"rain") == 0 && member.value().is<float>()) {
      if (strcmp(currentKey, "pwm") == 0) Vals.rainPwm = member.value();
    }
  //Moisture
    else if(strcmp(commandType,"moisture") == 0 && member.value().is<float>()) {
      if (strcmp(currentKey, "out1") == 0) Vals.out1 = member.value();
      else if (strcmp(currentKey, "out2") == 0) Vals.out2 = member.value();
      else if (strcmp(currentKey, "out3") == 0) Vals.out3 = member.value();
    }
    else {
        Serial.println("Invalid Input");
        break;
    }

    
}

// Output the values
Serial.println("Indoor Temperature: " + String(Vals.tempIndoor));
Serial.println("Outdoor Temperature: " + String(Vals.tempOutdoor));
Serial.println("Outdoor Humidity: " + String(Vals.humOutdoor));
Serial.println("Indoor Humidity: " + String(Vals.humIndoor));
  }
  delay(1000);
}     


void EnVar::processRequest(const char* c){
  // Read input until a newline character is encountered
  for (int index = 0; index < strlen(c); index++){
    if (c[index] == '\n') break; // Exit the loop when newline character is encountered
    else Vals.inputBuffer[index] = c[index]; // Store character in inputBuffer
  }
  Vals.inputBuffer[index] = '\0'; // Add NULL at end of input buffer
  Vals.extractVals();
}


