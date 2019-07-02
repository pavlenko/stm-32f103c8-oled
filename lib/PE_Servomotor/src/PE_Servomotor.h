#ifndef PE_SERVOMOTOR_H
#define PE_SERVOMOTOR_H

#include <stdint.h>

/** Instructions **************************************************************/

// Register read
#define PE_SERVO_CMD_R_REGISTER(_reg_) ((0x00U) | ((0x1FU) & (_reg_)))

// Register write
#define PE_SERVO_CMD_W_REGISTER(_reg_) ((0x20U) | ((0x1FU) & (_reg_)))

/** Registers *****************************************************************/

// Control registers
#define PE_SERVO_EN_CH   0x00U

// Value registers
#define PE_SERVO_VAL_CH0 0x08U
#define PE_SERVO_VAL_CH1 0x09U
#define PE_SERVO_VAL_CH2 0x0AU
#define PE_SERVO_VAL_CH3 0x0BU
#define PE_SERVO_VAL_CH4 0x0CU
#define PE_SERVO_VAL_CH5 0x0DU
#define PE_SERVO_VAL_CH6 0x0EU
#define PE_SERVO_VAL_CH7 0x0FU

// Calibration min registers
#define PE_SERVO_MIN_CH0 0x10U
#define PE_SERVO_MIN_CH1 0x11U
#define PE_SERVO_MIN_CH2 0x12U
#define PE_SERVO_MIN_CH3 0x13U
#define PE_SERVO_MIN_CH4 0x14U
#define PE_SERVO_MIN_CH5 0x15U
#define PE_SERVO_MIN_CH6 0x16U
#define PE_SERVO_MIN_CH7 0x17U

// Calibration max registers
#define PE_SERVO_MAX_CH0 0x18U
#define PE_SERVO_MAX_CH1 0x19U
#define PE_SERVO_MAX_CH2 0x1AU
#define PE_SERVO_MAX_CH3 0x1BU
#define PE_SERVO_MAX_CH4 0x1CU
#define PE_SERVO_MAX_CH5 0x1DU
#define PE_SERVO_MAX_CH6 0x1EU
#define PE_SERVO_MAX_CH7 0x1FU

/** EN bits *******************************************************************/
#define PE_SERVO_EN_CH0_Pos (0U)
#define PE_SERVO_EN_CH0_Msk (1U << PE_SERVO_EN_CH0_Pos)
#define PE_SERVO_EN_CH0     PE_SERVO_EN_CH0_Msk

#define PE_SERVO_EN_CH1_Pos (1U)
#define PE_SERVO_EN_CH1_Msk (1U << PE_SERVO_EN_CH1_Pos)
#define PE_SERVO_EN_CH1     PE_SERVO_EN_CH1_Msk

#define PE_SERVO_EN_CH2_Pos (2U)
#define PE_SERVO_EN_CH2_Msk (1U << PE_SERVO_EN_CH2_Pos)
#define PE_SERVO_EN_CH2     PE_SERVO_EN_CH2_Msk

#define PE_SERVO_EN_CH3_Pos (3U)
#define PE_SERVO_EN_CH3_Msk (1U << PE_SERVO_EN_CH3_Pos)
#define PE_SERVO_EN_CH3     PE_SERVO_EN_CH3_Msk

#define PE_SERVO_EN_CH4_Pos (4U)
#define PE_SERVO_EN_CH4_Msk (1U << PE_SERVO_EN_CH4_Pos)
#define PE_SERVO_EN_CH4     PE_SERVO_EN_CH4_Msk

#define PE_SERVO_EN_CH5_Pos (5U)
#define PE_SERVO_EN_CH5_Msk (1U << PE_SERVO_EN_CH5_Pos)
#define PE_SERVO_EN_CH5     PE_SERVO_EN_CH5_Msk

#define PE_SERVO_EN_CH6_Pos (6U)
#define PE_SERVO_EN_CH6_Msk (1U << PE_SERVO_EN_CH6_Pos)
#define PE_SERVO_EN_CH6     PE_SERVO_EN_CH6_Msk

#define PE_SERVO_EN_CH7_Pos (7U)
#define PE_SERVO_EN_CH7_Msk (1U << PE_SERVO_EN_CH7_Pos)
#define PE_SERVO_EN_CH7     PE_SERVO_EN_CH7_Msk




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
