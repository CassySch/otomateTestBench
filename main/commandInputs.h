#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#define MAX_INPUT_SIZE 256

#define RELAY_1 14
#define RELAY_2 13
#define RELAY_3 12
#define RELAY_4 11
#define RELAY_5 10
#define RELAY_6 9

class EnVar {
  public:
    float tempIndoor,tempOutdoor,humOutdoor,humIndoor;
    int windSpeed,windDir,rainPwm,moisture1,moisture2,moisture3;
    int relayArray[6] = {RELAY_1,RELAY_2,RELAY_3,RELAY_4,RELAY_5,RELAY_6};
    
    void applyValues(JsonDocument* doc);
    void setTempIndoor();
    void setTempOutdoor();
    void setHumIndoor();
    void setHumOutdoor();
    void setWindSpeed();
    void setWindDir();
    void setMoisture();
};

DeserializationError getSerialJson(JsonDocument* doc);