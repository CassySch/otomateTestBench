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

#define data_pin
#define clock_pin

#define READ 0
#define WRITE 1

float soRh;

void initSht() {
    pinMode(data_pin, INPUT);
    pinMode(clock_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(data_pin), readWrite_I2C1, FALLING); //Transmission start starts off with low data
}

enum State = {
        IDLE = 0,
        TRANSMISSION_START,
        READ_00,
        READ_01,
        READ_02,
        READ_03,
        READ_04,
        READ_05,
        READ_06,
        READ_07,
        SEND_ACK,
        WRITE_00,
        WRITE_01,
        WRITE_02,
        WRITE_03,
        WRITE_04,
        WRITE_05,
        WRITE_06,
        WRITE_07,
        WAIT_ACK,
        WAIT_ACK_DONE,
        WRITE_08,
        WRITE_09,
        WRITE_10,
        WRITE_11,
        WRITE_12,
        WRITE_13,
        WRITE_14,
        WRITE_15,
        WRITE_DONE,
};

static enum State state = IDLE;
static int data_value = 0;

struct I2C_SLAVE {
    const void (*isr)(); 
    const int dataPin;
    const int clockPin;
    const enum State *state;
    const int *dataValue;
    const int *temperatureValue; //pointer to global temperature value
    const int *humidityValue;
};

extern void IRAM_ATTR readWrite_I2C1();

//for another sensor just create another instance of the struct and create another isr
static struct I2C_SLAVE sensor1 = { readWriteI2C1, SDA_PIN, SCL_PIN, &state, &data_value, &indoorTemperature, &soRh};


void IRAM_ATTR readWriteI2C1() {
    readWrite(&sensor1); 
}

void readWrite(struct I2C_SLAVE *p) {
    switch (state) {
        case IDLE:
            if ((digitalRead(p->clockPin))) { //For transmission start when data is changing clock should be high
                attachInterrupt(digitalPinToInterrupt(data_pin), readWrite_I2C1, RISING); //Transmission start ends with rising edge so next expected is data rising
                state++;
                *p->dataValue = 0; //clear whatever might be in the dataValue
            }
            break;
        case TRANSMISSION_START:
          if ((digitalRead(p->clockPin))){
            attachInterrupt(digitalPinToInterrupt(clock_pin), readWrite_I2C1, RISING); //Read on rising of clock
            state++;
          }
          break;
        case READ_00:
        case READ_01:
        case READ_02:
        case READ_03:
        case READ_04:
        case READ_05:
        case READ_06:
        case READ_07:
            *p->dataValue <<= 1; //Shift the bits by 1 to the left to prepare for shifting in LSB
            *p->dataValue |= digitalRead(p->dataPin); //write to the LSB
            state++;

            if (state == SEND_ACK) {
                if (/* check if it is a valid command and address*/) {
                    attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING);
                    pinMode(dataPin, INPUT);
                } else {
                    // not a valid command or address so ignore and go to idle
                    attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING); //back to idle and wait for begining of transmission start sequence
                    pinMode(dataPin, INPUT);
                    state = IDLE;
                }
            }
            break;

        case SEND_ACK:
            digitalWrite(p->dataPin, LOW);
            state++;
            break;

        case SEND_ACK_DONE:
            digitalWrite(p->dataPin, HIGH);

            if (/* command is measure */) { //don't think we need any of the other types of commands so may not need this
                if (dataValue == 00011) {
                    *p->dataValue = *p->humidityValue; //dataValue has the global humidityValue 
                    state = WRITE_00; //start writing data
                } else if (dataValue == 00011) {
                    *p->dataValue = *p->temperatureValue;
                    state = WRITE_00;
                } else {
                    attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING); //back to idle as command was not a valid measurre command
                    pinMode(dataPin, INPUT);
                    state = IDLE;
                }
            } else {
                attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING); //not measure command go back to idle
                pinMode(dataPin, INPUT);
                state = IDLE;
            }

        case WRITE_00:
        case WRITE_01:
        case WRITE_02:
        case WRITE_03:
        case WRITE_04:
        case WRITE_05:
        case WRITE_06:
        case WRITE_07: //Wait ack is the next state 
        case WRITE_08:
        case WRITE_09:
        case WRITE_10:
        case WRITE_11:
        case WRITE_12:
        case WRITE_13:
        case WRITE_14:
        case WRITE_15: //write done is next state
            digitalWrite(p->dataPin, *p->dataValue & 1); //Isolate the LSB
            *p->dataValue >>= 1; //shift next bit over into LSB position
            state++;

            if (state == WAIT_ACK) {
                attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, RISING); //Read on rising
            } else if (state == WRITE_DONE) {
                attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING);
                pinMode(dataPin, INPUT);
                state = IDLE;
            }
            break;

        case WAIT_ACK:
            if (digitalRead(p->dataPin)) { 
                // no ack
                attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING);
                pinMode(dataPin, INPUT);
                state = IDLE;
            } else {
                // ack done
                state++;
            }
            break;

        case WAIT_ACK_DONE:
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING);
            state++;
            break;
    }
}

float convertToSoRh(float rhLin) {
    float rhLin;
    soRh = (-(C2) + sqrt(pow(C2, 2) - 4(C3 * (C1 - rhLin)))) / (2 * C3);
    return soRh;
}

void convertToSoT(float T) {
    //Have to figure out the conversion
}
