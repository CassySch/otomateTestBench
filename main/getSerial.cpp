#include "commandInputs.h"

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