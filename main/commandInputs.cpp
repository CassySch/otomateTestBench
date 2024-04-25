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
  
  //Temperature 
    if ((strcmp(currentKey,"command")== 0 ) && member.value() == "temperature")commandType = member.value();
    else if((strcmp(currentKey, "indoor") == 0) && strcmp(commandType,"temperature") == 0) Vals.tempIndoor = member.value().as<float>();
    else if((strcmp(currentKey, "outdoor") == 0) && strcmp(commandType,"temperature") == 0) Vals.tempOutdoor = member.value().as<float>();
    
  //Humidity
    if ((strcmp(currentKey,"command")== 0 ) && member.value().as<String>() == "humidity") commandType = member.value();
    else if((strcmp(currentKey, "indoor") == 0) && strcmp(commandType,"humidity") == 0) Vals.humIndoor = member.value().as<float>();
    else if((strcmp(currentKey,"outdoor") == 0) && strcmp(commandType,"humidity") == 0) Vals.humOutdoor = member.value().as<float>();
  
  //Wind
    if ((strcmp(currentKey,"command")== 0 ) && member.value().as<String>() == "wind") commandType = member.value();
    else if((strcmp(currentKey, "speed") == 0) && strcmp(commandType,"wind") == 0) Vals.windSpeed = member.value().as<float>();
    else if((strcmp(currentKey,"direction") == 0) && strcmp(commandType,"wind") == 0) Vals.windDir = member.value().as<float>();

    //Rain
    if ((strcmp(currentKey,"command")== 0 ) && member.value().as<String>() == "rain") commandType = member.value();
    else if((strcmp(currentKey, "pwm") == 0) && strcmp(commandType,"wind") == 0) Vals.rainPwm = member.value().as<float>();

    //Moisture
    if ((strcmp(currentKey,"command")== 0 ) && member.value().as<String>() == "moisture") commandType = member.value();
    else if((strcmp(currentKey,"out1") == 0) && strcmp(commandType,"moisture") == 0) Vals.windSpeed = member.value().as<float>();
    else if((strcmp(currentKey,"out2") == 0) && strcmp(commandType,"moisture") == 0) Vals.windDir = member.value().as<float>();
    else if((strcmp(currentKey,"out3") == 0) && strcmp(commandType,"moisture") == 0) Vals.windDir = member.value().as<float>();
}



// Output the values
Serial.println("Indoor Temperature: " + String(Vals.tempIndoor));
Serial.println("Outdoor Temperature: " + String(Vals.tempOutdoor));
Serial.println("Outdoor Humidity: " + String(Vals.humOutdoor));
Serial.println("Indoor Humidity: " + String(Vals.humIndoor));
  }
  delay(1000);
}     

void EnVar::getRequest(){
  Serial.println("Enter JSON object:");
  while (!Serial.available()) {} // Wait for user input

  // Read input until a newline character is encountered
  unsigned int index = 0;
  while (index < MAX_INPUT_SIZE - 1) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        break; // Exit the loop when newline character is encountered
      } else {
        Vals.inputBuffer[index++] = c; // Store character in inputBuffer
      }
    }
  }
  Vals.inputBuffer[index] = '\0'; // Add NULL at end of input buffer

  Vals.extractVals();
}


