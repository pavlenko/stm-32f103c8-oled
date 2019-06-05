#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <stdint.h>

typedef struct {
    uint32_t interval;
    uint32_t schedule;// Internal
    void (*callable)();
} Timer_t;

uint8_t attach(Timer_t *timer);// return status
uint8_t detach(Timer_t *timer);// return status

void dispatch(uint32_t ms);

#endif //TIMEOUT_H
