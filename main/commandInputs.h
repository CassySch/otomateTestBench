#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "relays.h"

#define MAX_INPUT_SIZE 256



#define NOT_VALID_DATA 0
#define VALID_DATA 1

class EnVar {
  public:
    float tempIndoor,tempOutdoor,humOutdoor,humIndoor;
    int windSpeed,windDir,rainPwm,moisture1,moisture2,moisture3;
    int relayArray[NUMRELAYS] = {RELAY_1,RELAY_2,RELAY_3,RELAY_4,RELAY_5,RELAY_6};
    int relayVals[NUMRELAYS];

    void applyValues(JsonDocument* doc);
    void setTempIndoor();
    void setTempOutdoor();
    void setHumIndoor();
    void setHumOutdoor();
    void setWindSpeed();
    void setWindDir();
    void setMoisture();
    void ReadRelays();
};

const char* getSerialJson(char* request);
DeserializationError validateJson(const char* jsonString,JsonDocument* doc);
void pwmInitTimer0(int prescaler, int onTime, int offTime, int pinNum);

