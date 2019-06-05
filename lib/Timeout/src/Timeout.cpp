#include "Timeout.h"

Timer_t *items[32];
uint16_t count = 32;

typedef enum {
    TIMER_SUCCESS = 0x00u,
    TIMER_FAILURE = 0x01u,
} Timer_Status_t;

Timer_Status_t attach2(uint32_t interval, void (*callable)(), uint8_t *index) {
    return TIMER_SUCCESS;
}

Timer_Status_t detach(uint8_t index);

void dispatch(uint32_t ms) {
    uint8_t index;

    for (index = 1; index < count; index++) {
        if (items[index] == nullptr) {
            continue;
        }

        if (items[index]->schedule < ms) {
            items[index]->callable();

            if (items[index]->interval > 0) {
                items[index]->schedule += items[index]->interval;
            } else {
                items[index] = nullptr;//TODO how to delete array item during loop
            }
        }
    }
}

uint8_t getSize1() {
    return sizeof(Timer_t);
}

uint8_t getSize2() {
    return sizeof(Timer_t *);// Get size of pointer
}
