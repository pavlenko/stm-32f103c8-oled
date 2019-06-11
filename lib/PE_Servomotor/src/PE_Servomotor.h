#ifndef PE_SERVOMOTOR_H
#define PE_SERVOMOTOR_H

#include <stdint.h>

#define PE_SERVOMOTOR_PULSE_MIN 500u
#define PE_SERVOMOTOR_PULSE_MID 1500u
#define PE_SERVOMOTOR_PULSE_MAX 2500u

#define PE_SERVOMOTOR_SET_MICROS 0x01u
#define PE_SERVOMOTOR_GET_MICROS 0x02u

//TODO api must support control local and remote
//TODO check connection
//TODO write microseconds??? or maybe write angle is preferred
//TODO get/set min/max via remote api
//TODO calibration mode???
//TODO read data from remote servo???

typedef void (*PE_Servomotor_write_t) (uint8_t reg, uint16_t data);

class PE_Servomotor {
private:
    PE_Servomotor_write_t _write;
    uint16_t _min;
    uint16_t _max;
public:
    PE_Servomotor(PE_Servomotor_write_t write);

    PE_Servomotor(uint16_t min, uint16_t max);

    uint16_t getMin() const;

    void setMin(uint16_t min);

    uint16_t getMax() const;

    void setMax(uint16_t max);
};


#endif //PE_SERVOMOTOR_H
