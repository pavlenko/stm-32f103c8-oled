#ifndef PE_SERVOMOTOR_H
#define PE_SERVOMOTOR_H

#include <stdint.h>

#define PE_SERVOMOTOR_DEGREE_MIN 0u
#define PE_SERVOMOTOR_DEGREE_MID 90u
#define PE_SERVOMOTOR_DEGREE_MAX 180u

#define PE_SERVOMOTOR_MICROS_MIN 500u
#define PE_SERVOMOTOR_MICROS_MID 1500u
#define PE_SERVOMOTOR_MICROS_MAX 2500u

#define PE_SERVOMOTOR_SET_DEGREE  0xF0
#define PE_SERVOMOTOR_SET_MICROS  0xF1
#define PE_SERVOMOTOR_SET_MINIMUM 0xF2
#define PE_SERVOMOTOR_SET_MAXIMUM 0xF3

//TODO api must support control local and remote
//TODO check connection
//TODO write microseconds??? or maybe write angle is preferred
//TODO get/set min/max via remote api
//TODO calibration mode???
//TODO read data from remote servo???

typedef void (*PE_Servomotor_write_t) (uint8_t reg, uint16_t data);

class PE_Servomotor {
private:
    PE_Servomotor_write_t _send;
public:
    /**
     * Default constructor
     *
     * @param send
     */
    explicit PE_Servomotor(PE_Servomotor_write_t send);

    /**
     * Set current angle degree
     *
     * @param value
     */
    void setDegree(uint16_t value);

    /**
     * Set current angle pulse
     *
     * @param value
     */
    void setMicros(uint16_t value);

    /**
     * Set pulse range minimum, default is PE_SERVOMOTOR_MICROS_MIN
     *
     * @param value
     */
    void setMinimum(uint16_t value);

    /**
     * Set pulse range maximum, default is PE_SERVOMOTOR_MICROS_MAX
     *
     * @param value
     */
    void setMaximum(uint16_t value);
};

#endif //PE_SERVOMOTOR_H
