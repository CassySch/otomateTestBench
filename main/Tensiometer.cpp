#include "Tensiometer.h"
//voltage step scale, CBAR per volt
#define SCALE_CBAR MAX_VOLTAGE/MAX_CBAR

//sets the DAC to simulated tensiometer voltage output value
void setTensiometer(int cbar, int meter_num){
  float voltage = cbar * SCALE_CBAR;
  int dacAddr = (meter_num == 0) ? DAC_1_ADDRESS : DAC_2_ADDRESS;
  SendToDac(dacAddr, voltage, GROUP_TENSIOMETER); //utilises first i2c bus, with two DACs for indoor and outdoor humidity
}
