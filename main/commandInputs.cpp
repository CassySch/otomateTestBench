//#include <ArduinoJson.h>
//#include <ArduinoJson.hpp>
#include "commandInputs.h"

EnVar Vals;
bool dataFlag = NOT_VALID_DATA;

void EnVar::applyValues(JsonDocument* doc) {
  if(dataFlag == NOT_VALID_DATA) return;
  else{
  // Iterate over the members of the JSON object
  for (JsonPair member : doc->as<JsonObject>()) {
    const char* currentKey = member.key().c_str();
    JsonObject commandObject = member.value();
    //command verification
    if (strcmp(currentKey, "temperature") == 0) {
      //Value of key is an object containing possible settings
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "indoor") Vals.tempIndoor = kvp.value();
        else if (kvp.key() == "outdoor") Vals.tempOutdoor = kvp.value();
      }
      Serial.println("{ \"response\": \"temperature\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "humidity") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "indoor") Vals.humIndoor = kvp.value();
        else if (kvp.key() == "outdoor") Vals.humOutdoor = kvp.value();
      }
      Serial.println("{ \"response\": \"humidity\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "wind") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "speed") Vals.windSpeed = kvp.value();
        else if (kvp.key() == "direction") Vals.windDir = kvp.value();
      }
      Serial.println("{ \"response\": \"wind\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "moisture") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "moisture1") Vals.windSpeed = kvp.value();
        else if (kvp.key() == "moisture2") Vals.moisture1 = kvp.value();
        else if (kvp.key() == "moisture3") Vals.moisture2 = kvp.value();
        else if (kvp.key() == "moisture3") Vals.moisture3 = kvp.value();
      }
      Serial.println("{ \"response\": \"soil\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "rain") == 0) {
      Vals.rainPwm = member.value();
      Serial.println("{ \"response\": \"rain\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "inputs") == 0) {
      ReadRelays();
      Serial.println("{\"response\":\"inputs\",\"values\":[" + String(relayVals[0]) + "," + String(relayVals[1]) + "," + String(relayVals[2]) + "," + String(relayVals[3]) + "," + String(relayVals[4]) + "," + String(relayVals[5]) + "," + String(relayVals[6]) + "]}");
    } else {
      Serial.print("Not a recognized value:");
      Serial.println(currentKey);
    }
  }
  // Output the values
  Serial.println("Indoor Temperature: " + String(Vals.tempIndoor));
  Serial.println("Outdoor Temperature: " + String(Vals.tempOutdoor));
  Serial.println("Outdoor Humidity: " + String(Vals.humOutdoor));
  Serial.println("Indoor Humidity: " + String(Vals.humIndoor));
  Serial.println("Wind Speed: " + String(Vals.windSpeed));
  Serial.println("Wind Direction: " + String(Vals.windDir));
  Serial.println("Rain: " + String(Vals.rainPwm));
  }
}


const char* getSerialJson(char* request) {
  //char request[MAX_INPUT_SIZE + 1];
  char* p = request;  //pointer to request array
  int len = MAX_INPUT_SIZE;

  Serial.println("Enter JSON object:");
  while (!Serial.available()) {}  // Wait for user input
  while (len--) {
    if (Serial.available() > 0) {
      char c = Serial.read();
      if (c == '\n') {
        break;  // Exit the loop when newline character is encountered
      } else {
        *p++ = c;  //increment address of pointer and store c
      }
    }
  }
  *p = '\0';  // Add NULL at end of input

  return request;
}

DeserializationError validateJson(const char* jsonString, JsonDocument* doc) {
  DeserializationError error = deserializeJson(*doc, jsonString);
  if (error == DeserializationError::EmptyInput
      || error == DeserializationError::IncompleteInput
      || error == DeserializationError::InvalidInput
      || error == DeserializationError::NoMemory
      || error == DeserializationError::TooDeep) {
    Serial.println("NOT VALID JSON");
    dataFlag = NOT_VALID_DATA;
  } else dataFlag = VALID_DATA;
  return error;
}

void EnVar::ReadRelays() {
  for (int i = 0; i < NUMRELAYS; i++) {
    relayVals[i] = digitalRead(relayArray[i]);
  }
}
