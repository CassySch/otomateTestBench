#include "Anemometer.h"

void SetWind(float speed, int degrees){
  int pulse_ms=0, pps=0;
  float SensorOut;

  pulse_ms = (1000/(speed/2.4)) - 15; // calculates the duration of one pwm pulse, (half the period)
  setPwm(pulse_ms, pulse_ms, PinAnemometer); //sets pwm pulse signal according to wind speed set
  
  SensorOut = ((degrees/360)*1023)/(5.0/1023.0); //determines output voltage for simulated anemometer
  SendToDac(DAC_1_ADDRESS, SensorOut, GROUP_ANEMOMETER); //sets the DAC to the analog voltage value corresponding to the wind direction
}
