#include <math.h>

#define C1
#define C2
#define C3

#define SDA_PIN
#define SCL_PIN

void initSht(){
  pinMode(SDA_PIN,INPUT);
  pinMode(SCL_PIN,INPUT);
}
float convertToSOrh(float rhLin){
  float soRh;
  float rhLin;
  soRh = -(C2)+ sqrt(pow(C2,2)-4(C3*(C1-rhLin)));
  return soRh;
}

void sendHumidity(float soRh){

}