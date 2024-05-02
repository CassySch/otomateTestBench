#include <Wire.h>
#include "DAC.h"
#include "Arduino.h"

// Function to send data to the DAC
void send_to_dac(int dacAddr, float voltage) {
  uint16_t value = (uint16_t)((voltage / MAX_VOLTAGE) * DAC_RES);
  // DAC expects a 16-bit value
  Wire.beginTransmission(dacAddr);
  Wire.write(highByte(value)); // Send high byte
  Wire.write(lowByte(value));  // Send low byte
  Wire.endTransmission();
}

void DacCommunicationInit(int sdaPin, int sclPin){ 
  Wire.begin(sdaPin, sclPin);
 }
