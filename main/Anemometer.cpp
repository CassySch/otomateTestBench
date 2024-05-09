#include "Anemometer.h"

void SetWind(float speed){
  int pulse_ms=0, pps=0;
  pulse_ms = (1000/(speed/2.4)) - 15; // calculates the duration of one pwm pulse, (half the period)
  setPwm(pulse_ms, pulse_ms, PinAnemometer); //sets pwm pulse signal according to wind speed set
}
