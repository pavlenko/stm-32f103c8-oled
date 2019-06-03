#ifndef _SERVOMOTOR_H
#define _SERVOMOTOR_H

#include <stdint.h>

typedef struct {
    uint16_t min;
    uint16_t max;
    uint16_t current;
    void (*set) (uint16_t us);
    uint16_t (*get) ();
} Servo_Handle_t;

void Servo_initialize(Servo_Handle_t *servo, uint16_t min, uint16_t max);

void Servo_setAngle(Servo_Handle_t *servo, uint16_t deg);

uint16_t Servo_getAngle(Servo_Handle_t *servo);

#endif //_SERVOMOTOR_H
