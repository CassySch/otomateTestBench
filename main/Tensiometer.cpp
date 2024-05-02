#include "Tensiometer.h"

//voltage step scale, CBAR per volt
#define SCALE_CBAR MAX_VOLTAGE/MAX_CBAR

//sets the DAC to simulated tensiometer voltage output value
void setTensiometer(int cbar, int tensiometer_num){
  float voltage = cbar * SCALE_CBAR;
  int dacAddr = (tensiometer_num == 0) ? DAC_1_ADDRESS : DAC_2_ADDRESS;
  send_to_dac(dacAddr, voltage);
}
