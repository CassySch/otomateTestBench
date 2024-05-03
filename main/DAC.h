#include <Wire.h>

//Voltage macros
#define MAX_VOLTAGE 4.75

//dac resolution
#define DAC_RES 4095

// Define I2C pins
#define GROUP_0_SDA_PIN 7  // DACs 1 & 2 SDA pin
#define GROUP_0_SCL_PIN 6  // DACs 1 & 2 SCL pin
#define GROUP_1_SDA_PIN 5  // DAC 3 SDA pin
#define GROUP_1_SCL_PIN 4  // DAC 3 SCL pin

// The MCP4725 has only 2 possible addresses
#define DAC_1_ADDRESS 0x60
#define DAC_2_ADDRESS 0x61

void SendToDac(int dacAddr, float voltage, int group);
void DacInit();