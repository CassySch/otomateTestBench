#include "DAC.h"
#include "Arduino.h"

TwoWire i2cbus1 = TwoWire(0); // Create an instance for the first I2C bus
TwoWire i2cbus2 = TwoWire(1); // Create an instance for the second I2C bus

// Function to send data to the DAC
void SendToDac(int dacAddr, float voltage, int group) {
  uint16_t value = (uint16_t)((voltage / MAX_VOLTAGE) * DAC_RES);
  // DAC expects a 16-bit value
  if (group == 0) {
    i2cbus1.beginTransmission(dacAddr);
    i2cbus1.write(highByte(value)); // Send high byte
    i2cbus1.write(lowByte(value));  // Send low byte
    i2cbus1.endTransmission();
  }
  else if (group == 1) {
    i2cbus2.beginTransmission(dacAddr);
    i2cbus2.write(highByte(value)); // Send high byte
    i2cbus2.write(lowByte(value));  // Send low byte
    i2cbus2.endTransmission();
  }
}

void DacInit(){ 
  i2cbus1.begin(GROUP_0_SDA_PIN, GROUP_0_SCL_PIN, 100000);
  i2cbus2.begin(GROUP_1_SDA_PIN, GROUP_1_SCL_PIN, 100000);
 }
