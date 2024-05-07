#include <math.h>

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
bool clockPulse[15];
bool dataPulse[15];

void initSht(){
  pinMode(SDA_PIN,INPUT);
  pinMode(SCL_PIN,INPUT);
  attachInterrupt(digitalPinToInterrupt(SCL_PIN), clockVals, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SDA_PIN), dataVals, CHANGE);
}
void IRAM_ATTR dataVals(){
  clockPulse[i++] = digitalRead(SDA_PIN);
}
void IRAM_ATTR clockVals(){
  dataPulse[i++] = digitalRead(SCL_PIN);
}

float convertToSoRh(float rhLin){
  float soRh, rhLin;
  soRh = (-(C2)+sqrt(pow(C2,2)-4(C3*(C1-rhLin))))/(2*C3);

  return soRh;
}

void sendHumidity(float soRh){
  digitalWrite(SDA_PIN,soRh);
}

void sendTemperature(float soT){
}

enum state = {idle = 0,recieving,writing,reading} state = idle;
//enum dataSequenceState = {dataLow = 0,dataHigh};
//enum clockSequenceState = {clockLow = 0,clockHigh};
bool startSequence[][] ={1,0,1},{0,0,1};
bool correct = 0;
bool command[];
switch(state){
  case idle:
      for(int j =0; j<3; j++){
        if (startSequence[0][j]) == clockPulse[j]) && (startSequence[1][j]) == dataPulse[j]) correct = 1;
        else {
          correct = 0;
          break;
          }
      }
      if (correct == 1) state = recieving;
      else state = idle;
    break;
  case recieving:

    break;
  case writing:
    break;
  case reading:
    break;
}