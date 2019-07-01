#include "servomotor.h"

#include "stm32f1xx.h"
#include "stdint.h"
#include "tim.h"

__STATIC_INLINE long constrain(long amt, long low, long high) {
    return amt < low ? low : (amt > high ? high : amt);
}

__STATIC_INLINE long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static uint16_t servo0_micros     = PE_SERVOMOTOR_MICROS_MID;
static uint16_t servo0_micros_min = PE_SERVOMOTOR_MICROS_MIN;
static uint16_t servo0_micros_max = PE_SERVOMOTOR_MICROS_MAX;

void servo0_send(uint8_t reg, uint16_t data) {
    if (PE_SERVOMOTOR_SET_DEGREE == reg) {
        tim1.Instance->CCR1 = servo0_micros = map(
            constrain(data, PE_SERVOMOTOR_DEGREE_MIN, PE_SERVOMOTOR_DEGREE_MAX),
            PE_SERVOMOTOR_DEGREE_MIN,
            PE_SERVOMOTOR_DEGREE_MAX,
            servo0_micros_min,
            servo0_micros_max
        );
    }

    if (PE_SERVOMOTOR_SET_MICROS == reg) {
        tim1.Instance->CCR1 = servo0_micros = constrain(data, servo0_micros_min, servo0_micros_max);
    }

    if (PE_SERVOMOTOR_SET_MINIMUM == reg) {
        servo0_micros_min = data;
    }

    if (PE_SERVOMOTOR_SET_MAXIMUM == reg) {
        servo0_micros_max = data;
    }
}

uint16_t servo0_read(uint8_t reg) {
    if (PE_SERVOMOTOR_GET_DEGREE == reg) {
        return map(
            servo0_micros,
            servo0_micros_min,
            servo0_micros_max,
            PE_SERVOMOTOR_DEGREE_MIN,
            PE_SERVOMOTOR_DEGREE_MAX
        );
    }

    if (PE_SERVOMOTOR_GET_MICROS == reg) {
        return servo0_micros;
    }

    return 0;
}

PE_Servomotor servo0 = PE_Servomotor(servo0_send, servo0_read);