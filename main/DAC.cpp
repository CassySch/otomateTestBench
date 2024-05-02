#include <Wire.h>
#include "DAC.h"
#include "Arduino.h"

uint16_t voltage_to_dac(float voltage) {
  return (uint16_t)((voltage / 4.75) * 4095);
}

// Function to send data to the DAC
void send_to_dac(int dacAddr, float voltage) {
  uint16_t value = voltage_to_dac(voltage);
  // DAC expects a 16-bit value
  Wire.beginTransmission(dacAddr);
  Wire.write(highByte(value)); // Send high byte
  Wire.write(lowByte(value));  // Send low byte
  Wire.endTransmission();
}

void DacCommunicationInit(int sdaPin, int sclPin){ 
  Wire.begin(sdaPin, sclPin);
 }
