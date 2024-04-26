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
    else if (strcmp(currentKey,"command") == 0 && !(member.value().is<String>())) {
      Serial.println("Invalid Input");
      break;
    }
  //Temperature 
    else if (strcmp(commandType,"temperature") == 0) {
      if(strcmp(currentKey, "indoor") == 0 && member.value().is<float>()) Vals.tempIndoor = member.value();
      else if(strcmp(currentKey, "outdoor") == 0 && member.value().is<float>()) Vals.tempOutdoor = member.value();
      else {
        Serial.println("Invalid Input");
        break;
      }
    }

  //Humidity
    else if (strcmp(commandType,"humidity") == 0) {
      if(strcmp(currentKey, "indoor") == 0 && member.value().is<float>()) Vals.humIndoor = member.value();
      else if(strcmp(currentKey, "outdoor") == 0 && member.value().is<float>()) Vals.humOutdoor = member.value();
      else {
        Serial.println("Invalid Input");
        break;
      }
    }
  
  //Wind
    else if(strcmp(commandType,"wind") == 0) {
      if(strcmp(currentKey, "speed") == 0 && member.value().is<float>()) Vals.windSpeed = member.value();
      else if(strcmp(currentKey,"direction") == 0 && member.value().is<float>()) Vals.windDir = member.value();
      else {
        Serial.println("Invalid Input");
        break;
      }
    }
  //Rain
    else if(strcmp(commandType,"rain") == 0) {
      if (strcmp(currentKey, "pwm") == 0 && member.value().is<float>()) Vals.rainPwm = member.value();
      else {
        Serial.println("Invalid Input");
        break;
      }
    }
  //Moisture
    else if(strcmp(commandType,"moisture") == 0) {
      if (strcmp(currentKey, "out1") == 0 && member.value().is<float>()) Vals.out1 = member.value();
      else if (strcmp(currentKey, "out2") == 0 && member.value().is<float>()) Vals.out2 = member.value();
      else if (strcmp(currentKey, "out3") == 0 && member.value().is<float>()) Vals.out3 = member.value();
      else {
        Serial.println("Invalid Input");
        break;
      }
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


