#define MAX_INPUT_SIZE 256
class EnVar {
  private:
    float tempIndoor,tempOutdoor,humOutdoor,humIndoor;
    int windSpeed,windDir,rainPwm,out1,out2,out3;
    char inputBuffer[MAX_INPUT_SIZE];
    
  public:
    void extractVals();
    void setTempIndoor();
    void setTempOutdoor();
    void setHumIndoor();
    void setHumOutdoor();
    void setWindSpeed();
    void setWindDir();
    void setMoisture();
    void loop();
    void processRequest(const char* c);
};