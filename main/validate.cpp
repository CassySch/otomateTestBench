#include "commandInputs.h"

bool dataFlag = NOT_VALID_DATA;

DeserializationError validateJson(const char* jsonString, JsonDocument* doc) {
  DeserializationError error = deserializeJson(*doc, jsonString);
  if(jsonString[0] != '{') error = DeserializationError::IncompleteInput; //desirializeJson doesn't seem to generate an error when { is missing
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
