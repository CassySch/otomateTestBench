#include "DAC.h"


#define MAX_CBAR 93 //max CBAR value that can be read by the tensiometer
#define GROUP_TENSIOMETER 0 //macro for i2c bus for tensiometer DACs

//function prototype
void setTensiometer(int cbar, int meter_num);