#include <Arduino.h>
#include "commandInputs.h"
#include "DAC.h"

#define GROUP_ANEMOMETER 1 //macro for i2c dac group for anemometer
#define PinAnemometer 9 //macro for anemometer pin

void SetWind(float speed, int degrees);