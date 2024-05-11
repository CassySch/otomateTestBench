#define pwmChannel 0 // Choose a PWM channel (0 to 15)
#define pwmPin 5 // Choose a pin (e.g., GPIO5)
#define RainFreq 50 // Desired PWM frequency in Hz
#define RainRes 8 // PWM resolution (bits)

#define Bucket_Size 0.0254 //macro for bucket volume of rain sensor in bucket mode

//function prototypes
void RainSensorInit();
void setRain(int millilitres);