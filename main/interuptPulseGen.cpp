#include "esp32-hal-timer.h"
#include "commandInputs.h"


hw_timer_t *timer = NULL;
int timeOn, timeOff;
int cnt = 0;
int prescalerVal;
extern int numPin;

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

void pwmInitTimer0(int prescaler){
    if(timer == NULL){
      timer = timerBegin(0, prescaler, true);
      timerAttachInterrupt(timer, &pulse, true);
      timerAlarmWrite(timer, 300, false); //Set the timer's trigger event initially trigers an iterupt at tick 300 to give time to the setup to happen and does not reload after interupt
      timerAlarmEnable(timer);
    }
}

void setPwm(int onTime, int offTime, int pinNum){
    timeOn = onTime;
    timeOff = offTime;
    numPin = pinNum;
}
