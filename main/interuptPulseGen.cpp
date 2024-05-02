#include "esp32-hal-timer.h"
#include "commandInputs.h"

hw_timer_t *timer = NULL;

int timeOn, timeOff;
int numPin;
int cnt = 0;

void IRAM_ATTR pulse(){
  noInterrupts(); // Disable interrupts
  if(cnt%2 == 0){
    digitalWrite(numPin,HIGH);
    timerAlarmWrite(timer, timeOn, false); // 2 seconds 
  }
  else{
    digitalWrite(numPin,LOW);
    timerAlarmWrite(timer, timeOff, false); // 1 second
    }
    cnt++;
    timerRestart(timer); // reset timer to 0
    interrupts(); // Re-enable interrupts
}

void pwmInitTimer0(int prescaler, int onTime, int offTime, int pinNum){
    timeOn = onTime;
    timeOff = offTime;
    numPin = pinNum;
    timer = timerBegin(0, prescaler, true);   // Initialize Timer 0 with a prescaler of 80 (80 MHz / 80 = 1 MHz)
    timerAttachInterrupt(timer, &pulse, true);
    timerAlarmWrite(timer, 0, false); //Set the timer's trigger event initially triigers an iterupt at tick 0 and does not reload after interupt
    timerAlarmEnable(timer);
    pinMode(pinNum,OUTPUT);
}

