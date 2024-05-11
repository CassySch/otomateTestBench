#include <driver/ledc.h>
#include "RainSensor.h"
#include <Arduino.h>


static int tipCount=0, neededPulses=0;
void isr_rg() {
  tipCount++; //increments pulse number
  if (tipCount>=neededPulses) {
    ledc_stop(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 1);
    //ledc_stop(LEDC_LOW_SPEED_MODE, pwmChannel, 1); // Stop the PWM signal
    tipCount = 0; //resets pwm count
  }
}

void setRain(int millilitres) {
  int numpulses = millilitres / Bucket_Size;
  neededPulses = numpulses;
  ledcWrite(pwmChannel, 128); //sets 50Hz pwm with 50% duty cycle
}

void RainSensorInit() {
  ledcSetup(pwmChannel, RainFreq, RainRes); //pwm setup
  ledcAttachPin(pwmPin, pwmChannel);
  attachInterrupt(digitalPinToInterrupt(pwmPin), isr_rg, FALLING);
  tipCount = 0; //resets pwm count
  neededPulses = 0; //resets target pwm count
}