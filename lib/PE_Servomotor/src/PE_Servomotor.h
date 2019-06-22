#ifndef PE_SERVOMOTOR_H
#define PE_SERVOMOTOR_H

#include <stdint.h>

#define PE_SERVOMOTOR_DEGREE_MIN 0u
#define PE_SERVOMOTOR_DEGREE_MID 90u
#define PE_SERVOMOTOR_DEGREE_MAX 180u

#define PE_SERVOMOTOR_MICROS_MIN 500u
#define PE_SERVOMOTOR_MICROS_MID 1500u
#define PE_SERVOMOTOR_MICROS_MAX 2500u

#define PE_SERVOMOTOR_GET_DEGREE  0xF0
#define PE_SERVOMOTOR_SET_DEGREE  0xF1
#define PE_SERVOMOTOR_GET_MICROS  0xF2
#define PE_SERVOMOTOR_SET_MICROS  0xF3
#define PE_SERVOMOTOR_GET_MINIMUM 0xF4
#define PE_SERVOMOTOR_SET_MINIMUM 0xF5
#define PE_SERVOMOTOR_GET_MAXIMUM 0xF6
#define PE_SERVOMOTOR_SET_MAXIMUM 0xF7

//TODO api must support control local and remote
//TODO check connection
//TODO calibration mode???

typedef void (*PE_Servomotor_send_t) (uint8_t reg, uint16_t data);
typedef uint16_t (*PE_Servomotor_read_t) (uint8_t reg);

class PE_Servomotor {
private:
    PE_Servomotor_send_t _send;
    PE_Servomotor_read_t _read;
public:
    /**
     * Default constructor
     *
     * @param send
     * @param read
     */
    explicit PE_Servomotor(PE_Servomotor_send_t send, PE_Servomotor_read_t read);

    /**
     * Get current angle degree
     *
     * @return
     */
    uint16_t getDegree();

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
     * Get pulse range minimum
     *
     * @return
     */
    uint16_t getMinimum();

    /**
     * Set pulse range minimum, default is PE_SERVOMOTOR_MICROS_MIN
     *
     * @param value
     */
    void setMinimum(uint16_t value);

    /**
     * Get pulse range maximum
     *
     * @return
     */
    uint16_t getMaximum();

    /**
     * Set pulse range maximum, default is PE_SERVOMOTOR_MICROS_MAX
     *
     * @param value
     */
    void setMaximum(uint16_t value);
};

#endif //PE_SERVOMOTOR_H
