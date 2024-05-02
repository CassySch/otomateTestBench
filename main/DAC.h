//Voltage macros
#define MAX_VOLTAGE 4.75

//dac resolution
#define DAC_RES 4095

// Define I2C pins
#define DAC_1_SDA_PIN 7  // Example pin for SDA
#define DAC_1_SCL_PIN 6  // Example pin for SCL

// The MCP4725 has only 2 possible addresses
#define DAC_1_ADDRESS 0x60
#define DAC_2_ADDRESS 0x61

void send_to_dac(int dacAddr, float voltage);
void DacCommunicationInit(int sdaPin, int sclPin);