#include <math.h>
#include <arduino.h>

//#define  TWELVE_BIT_HUMIDITY
#define EIGHT_BIT_HUMIDITY

#ifdef TWELVE_BIT_HUMIDITY
#define C1 -2.0468
#define C2 0.0367
#define C3 -1.5955/1000000
#endif

#ifdef EIGHT_BIT_HUMIDITY
#define C1 -2.0468
#define C2 0.5872
#define C3 -4.0845/10000
#endif

#define SENSOR_1_SDA_PIN 1
#define SENSOR_1_SCL_PIN 2
#define SENSOR_2_SDA_PIN 3
#define SENSOR_2_SCL_PIN 4

#define  IDLE  0
#define  TRANSMISSION_START 1
#define  READ_00 2
#define  READ_01 3
#define  READ_02 4
#define  READ_03 5
#define  READ_04 6
#define  READ_05 7
#define  READ_06 8
#define  READ_07 9
#define  SEND_ACK 10
#define  SEND_ACK_DONE 11
#define  WRITE_00 12
#define  WRITE_01 13
#define  WRITE_02 14
#define  WRITE_03 15
#define  WRITE_04 16
#define  WRITE_05 17
#define  WRITE_06 18
#define  WRITE_07 19
#define  WRITE_07_DONE 20
#define  WAIT_ACK 21
#define  WRITE_08 22
#define  WRITE_09 23
#define  WRITE_10 24
#define  WRITE_11 25
#define  WRITE_12 26
#define  WRITE_13 27
#define  WRITE_14 28
#define  WRITE_15 29
#define  WRITE_DONE 30

// state transition commands
#define STATE_TO_NEXT 0
#define STATE_TO_READ 1
#define STATE_TO_WRITE_00 2
#define STATE_TO_WRITE_08 3
#define STATE_TO_TRANSMISSION_START 4
#define STATE_TO_IDLE 5
#define STATE_TO_SEND_ACK 6
#define STATE_TO_SEND_ACK_DONE 7
#define STATE_TO_WAIT_ACK 8

int soRh, soT;

static int state = IDLE;
static int data_value = 0;

struct I2C_SLAVE {
    void (*isr)();
    const int dataPin;
    const int clockPin;
    int *pState;
    int *pDataValue;
    int *pTemperatureValue; //pointer to global temperature value
    int *pHumidityValue;
};

void readWrite_I2C1();
void readWrite(const struct I2C_SLAVE *p);
void transitionState(const struct I2C_SLAVE *p, int transition);

//for another sensor just create another instance of the struct and create another isr
static const struct I2C_SLAVE sensor1 = { readWrite_I2C1, SENSOR_1_SDA_PIN, SENSOR_1_SCL_PIN, &state, &data_value, &soT, &soRh };

void initSht() {
    //attachInterrupt(digitalPinToInterrupt(SENSOR_1_SDA_PIN), readWriteI2C1, FALLING); //Transmission start starts off with falling edge on data
    transitionState(&sensor1, STATE_TO_IDLE);
}

void IRAM_ATTR readWriteI2C1() {
    readWrite(&sensor1);
}

void transitionState( struct I2C_SLAVE *p, int transition) {
    //process transitions
    switch (transition) {
        case STATE_TO_IDLE :
            *p->pState = IDLE;
            pinMode(p->dataPin, INPUT);
            attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, FALLING); //Transmission start ends with rising edge so next expected is data rising
            break;

        case STATE_TO_NEXT :
            *p->pState++;
            break;

        case STATE_TO_READ :
            *p->pState = READ_00;
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, RISING); //Read on rising of clock
            break;

        case STATE_TO_WRITE_00 :
            *p->pState = WRITE_00; //start writing MSB
            pinMode(p->dataPin, INPUT);     // data pin high impedance
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING); //Write on faling of clock
            break;

        case STATE_TO_WRITE_08 :
            *p->pState = WRITE_08; //start writing LSB
            pinMode(p->dataPin, INPUT);     // data pin high impedance
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING); //Write on faling of clock
            break;

        case STATE_TO_TRANSMISSION_START :
            *p->pState = TRANSMISSION_START;
            pinMode(p->dataPin, INPUT);     // data pin high impedance
            attachInterrupt(digitalPinToInterrupt(p->dataPin), p->isr, RISING);
            break;

        case STATE_TO_SEND_ACK:
            *p->pState = SEND_ACK;
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING);
            break;

        case STATE_TO_SEND_ACK_DONE:
            *p->pState = SEND_ACK_DONE;
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, FALLING);
            break;

        case STATE_TO_WAIT_ACK:
            *p->pState = WAIT_ACK;
            attachInterrupt(digitalPinToInterrupt(p->clockPin), p->isr, RISING); // Read on rising
            break;
    }
}

void readWrite(const struct I2C_SLAVE *p) {
    int transition = STATE_TO_NEXT;

    switch (state) {
        case IDLE:
            if ((digitalRead(p->clockPin))) { //For transmission start when data is changing clock should be high
                transition = STATE_TO_TRANSMISSION_START;
            }
            break;

        case TRANSMISSION_START:
            if ((digitalRead(p->clockPin))) {
                transition = STATE_TO_READ;
            }
            break;

        case READ_00:
            *p->pDataValue = 0; //clear whatever might be in the pDataValue
            // fall through

        case READ_01:
        case READ_02:
        case READ_03:
        case READ_04:
        case READ_05:
        case READ_06:
        case READ_07:
            // rising clock edge
            *p->pDataValue <<= 1; //Shift the bits by 1 to the left to prepare for shifting in LSb
            *p->pDataValue |= digitalRead(p->dataPin); // set LSb of byte

            if (state == READ_07) {
                if (true /* check if it is a valid command and address*/) {
                    transition = STATE_TO_SEND_ACK;
                } else {
                    // not a valid command or address so ignore and go to idle
                    transition = STATE_TO_IDLE;
                }
            }
            break;

        case SEND_ACK:
            // falling clock edge
            digitalWrite(p->dataPin, LOW);
            pinMode(p->dataPin, OUTPUT);
            break;

        case SEND_ACK_DONE:
            // falling clock edge
            pinMode(p->dataPin, INPUT); // data pin to high impedance
            //digitalWrite(p->dataPin, HIGH);

            if (*p->pDataValue == 5) {
                *p->pDataValue = *p->pHumidityValue; //pDataValue copies over the global pHumidityValue
                transition = STATE_TO_WRITE_00;
            } else if (*p->pDataValue == 3) {
                *p->pDataValue = *p->pTemperatureValue;
                transition = STATE_TO_WRITE_00;
            } else {
                transition = STATE_TO_IDLE;
            }
            break;

        case WRITE_00:
        case WRITE_01:
        case WRITE_02:
        case WRITE_03:
        case WRITE_04:
        case WRITE_05:
        case WRITE_06:
        case WRITE_07: // WRITE_07_DONE is next
        case WRITE_08:
        case WRITE_09:
        case WRITE_10:
        case WRITE_11:
        case WRITE_12:
        case WRITE_13:
        case WRITE_14:
        case WRITE_15: // WRITE_DONE is next pState
        
            // falling clock edge
            // simulate open collector output on data pin
            if ((*p->pDataValue & 0x8000)) {
                pinMode(p->dataPin, INPUT); // high impedance, open collector
            } else {
                digitalWrite(p->dataPin, LOW);
                pinMode(p->dataPin, OUTPUT);
            }

            *p->pDataValue <<= 1; //shift next bit over into MSB position
            break;

        case WRITE_07_DONE:
            // falling clock edge
            pinMode(p->dataPin, INPUT); // don't drive data pin, in case last bit was a 0
            transition = STATE_TO_WAIT_ACK;
            break;

        case WAIT_ACK:
            // rising clock edge
            if (digitalRead(p->dataPin)) {
                // no ack
                transition = STATE_TO_IDLE;
            } else {
                transition = STATE_TO_WRITE_08;
            }
            break;

        case WRITE_DONE :
            // falling clock edge
            transition = STATE_TO_IDLE;
            break;
    }

    transitionState(p, transition);
}

float convertToSoRh(float rhLin) {
    soRh = (-C2 + sqrt(pow(C2, 2) - 4*(C3 * (C1 - rhLin)))) / (2 * C3); //converts to format that the sensor outputs
    return soRh;
}

void convertToSoT(float T) {
    //Have to figure out the conversion
    //_temperature = (rawVal * D2) + D1;
    //invert this to convert
}
