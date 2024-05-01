//#include <ArduinoJson.h>
//#include <ArduinoJson.hpp>
#include "commandInputs.h"

EnVar Vals;

extern bool dataFlag;
void EnVar::applyValues(JsonDocument* doc) {
  if(dataFlag == NOT_VALID_DATA) return;
  else{
  // Iterate over the members of the JSON object
  for (JsonPair member : doc->as<JsonObject>()) {
    const char* currentKey = member.key().c_str();
    const char* memberKey;
    JsonObject commandObject = member.value();
    //command verification
    if (strcmp(currentKey, "temperature") == 0) {
      //Value of key is an object containing possible settings
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "indoor") Vals.tempIndoor = kvp.value();
        else if (kvp.key() == "outdoor") Vals.tempOutdoor = kvp.value();
        else{
           Serial.print("Not a valid member:");
           memberKey = kvp.key().c_str();
           Serial.println(memberKey);
        }
      }
      Serial.println("{ \"response\": \"temperature\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "humidity") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "indoor") Vals.humIndoor = kvp.value();
        else if (kvp.key() == "outdoor") Vals.humOutdoor = kvp.value();
        else{
           Serial.print("Not a valid member:");
           memberKey = kvp.key().c_str();
           Serial.println(memberKey);
        }
      }
      Serial.println("{ \"response\": \"humidity\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "wind") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "speed") Vals.windSpeed = kvp.value();
        else if (kvp.key() == "direction")Vals.windDir = kvp.value();
        else{
           Serial.print("Not a valid member:");
           memberKey = kvp.key().c_str();
           Serial.println(memberKey);
        }
      }
      Serial.println("{ \"response\": \"wind\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "moisture") == 0) {
      for (JsonPair kvp : commandObject) {
        if (kvp.key() == "moisture1") Vals.windSpeed = kvp.value();
        else if (kvp.key() == "moisture2") Vals.moisture1 = kvp.value();
        else if (kvp.key() == "moisture3") Vals.moisture2 = kvp.value();
        else if (kvp.key() == "moisture3") Vals.moisture3 = kvp.value();
        else{
           Serial.print("Not a valid member:");
           memberKey = kvp.key().c_str();
           Serial.println(memberKey);
        }
      }
      Serial.println("{ \"response\": \"soil\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "rain") == 0) {
      Vals.rainPwm = member.value();
      Serial.println("{ \"response\": \"rain\", \"status\" : \"ok\" }");
    } else if (strcmp(currentKey, "inputs") == 0) {
      ReadRelays();
      Serial.println("{\"response\":\"inputs\",\"values\":[" + String(relayVals[0]) + "," + String(relayVals[1]) + "," + String(relayVals[2]) + "," + String(relayVals[3]) + "," + String(relayVals[4]) + "," + String(relayVals[5]) + "]}");
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






