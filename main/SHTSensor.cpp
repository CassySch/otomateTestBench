#include <math.h>
#include <arduino.h>

//#define  TWELVE_BIT_HUM
#define EIGHT_BIT_HUM

#ifdef TWELVE_BIT_HUM
  #define C1 -2.0468
  #define C2 0.0367
  #define C3 -1.5955/1000000
#endif

#ifdef EIGHT_BIT_HUM
  #define C1 -2.0468
  #define C2 0.5872
  #define C3 -4.0845/10000
#endif

#define SDA_PIN
#define SCL_PIN

#define READ 0
#define WRITE 1


bool actionType = READ;
float soRh;

void initSht(){
  pinMode(SDA_PIN,INPUT);
  pinMode(SCL_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(SCL_PIN), readWrite, CHANGE);
}



void IRAM_ATTR readWrite(){
  enum state = {idle = 0,read,sendAck,writeHum,writeTemp,receiveAck} state = idle;
  if(digitalRead(SCL_PIN)== 0) lowCnt++;
  switch(state){
    case idle:
        if !(digitalRead(SDA_PIN)&&(digitalRead(SCL_PIN)) state = read;
        else state = idle;
      break;
    case read:
        
      break;
    case sendAck:
      if(lowCnt == 8) digitalWrite(SDA_PIN,LOW);
      else if(lowCnt == 9) digitalWrite(SDA_PIN,HIGH);
      
      if(command = readHum) state = writeHum;
      else if (command = readTemp) state = writeTemp;
      break;
    case writeHum:
    static float humidity = soRh;
    for (int i = sizeof(humidity) * 8 - 1; i >= 0; i--) {
          // Extract the i-th bit from num
          int bit = (humidity >> i) & 1;
          digitalWrite(struct.sdaPin,bit);
      break;
    case writeTemp:
      break;
    case receiveAck:
      break;
  }
  if(actionType){
    attachInterrupt(digitalPinToInterrupt(SCL_PIN), readWrite, FALLING);
    }
}



float convertToSoRh(float rhLin){
  float rhLin;
  soRh = (-(C2)+sqrt(pow(C2,2)-4(C3*(C1-rhLin))))/(2*C3);
}


void convertToSoT(float soT){
  //Have to figure out the conversion
}
