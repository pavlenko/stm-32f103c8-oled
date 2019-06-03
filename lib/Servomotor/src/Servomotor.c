#include "Servomotor.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Servo_initialize(Servo_Handle_t *servo, uint16_t min, uint16_t max) {
    servo->min = min;
    servo->max = max;
}

void Servo_setAngle(Servo_Handle_t *servo, uint16_t deg) {
    servo->current = map(deg, 0, 180, servo->min, servo->max);
}

uint16_t Servo_getAngle(Servo_Handle_t *servo) {
    return map(servo->current, servo->min, servo->max, 0, 180);
}
