#include "Timeout.h"

#include <malloc.h>
#include <stddef.h>
#include <string.h>

//TODO error of initialization here, cannot attach timer after call this function
void Timeout_initialize(Timeout_t *timeout, uint8_t limit) {
    timeout->items = (Timer_t **) malloc(limit * sizeof(Timer_t *));

    for (uint8_t i = 0; i < timeout->limit; ++i) {
        timeout->items[i] = NULL;
    }
}

Timeout_Status_t Timeout_attachTimer(Timeout_t *timeout, Timer_t *timer) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if (timeout->items[i] == NULL) {
            timeout->items[i] = timer;
            return TIMEOUT_SUCCESS;
        }
    }

    return TIMEOUT_FAILURE;
}

Timeout_Status_t Timeout_cancelTimer(Timeout_t *timeout, Timer_t *timer) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if (timeout->items[i] == timer) {
            timeout->items[i] = NULL;
            return TIMEOUT_SUCCESS;
        }
    }

    return TIMEOUT_FAILURE;
}

void Timeout_dispatch(Timeout_t *timeout, uint32_t ms) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if (timeout->items[i] == NULL) {
            continue;
        }

        if (timeout->items[i]->schedule < ms) {
            timeout->items[i]->callable();

            if (timeout->items[i]->interval > 0) {
                timeout->items[i]->schedule += timeout->items[i]->interval;
            } else {
                timeout->items[i] = NULL;
            }
        }
    }
}
