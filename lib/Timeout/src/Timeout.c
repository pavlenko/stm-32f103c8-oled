#include "Timeout.h"

#include <malloc.h>
#include <stddef.h>
#include <string.h>

Timeout_Status_t Timeout_initialize(Timeout_List_t *timeout, uint32_t time, uint8_t limit) {
    timeout->time  = time;
    timeout->limit = limit;
    timeout->items = (Timeout_Item_t *) malloc(limit * sizeof(Timeout_Item_t));

    if (!timeout->items) {
        return TIMEOUT_FAILURE;
    }

    // Fill array to pointers to null
    for (uint8_t i = 0; i < timeout->limit; i++) {
        *(timeout->items + i) = NULL;
    }

    return TIMEOUT_SUCCESS;
}

uint32_t Timeout_createHandlerSingular(Timeout_List_t *timeout, uint32_t interval, void (*callable)()) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if ((*(timeout->items + i)) == NULL) {
            (*(timeout->items + i)) = (Timeout_Timer_t *) malloc(sizeof(Timeout_Timer_t));

            if (!(*(timeout->items + i))) {
                return 0;
            }

            timeout->last++;

            (*(timeout->items + i))->identity = timeout->last;
            (*(timeout->items + i))->interval = 0;
            (*(timeout->items + i))->schedule = interval + timeout->time;
            (*(timeout->items + i))->callable = callable;

            return timeout->last;
        }
    }

    return 0;
}

uint32_t Timeout_createHandlerRepeated(Timeout_List_t *timeout, uint32_t interval, void (*callable)()) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if ((*(timeout->items + i)) == NULL) {
            (*(timeout->items + i)) = (Timeout_Timer_t *) malloc(sizeof(Timeout_Timer_t));

            if (!(*(timeout->items + i))) {
                return 0;
            }

            timeout->last++;

            (*(timeout->items + i))->identity = timeout->last;
            (*(timeout->items + i))->interval = interval;
            (*(timeout->items + i))->schedule = interval + timeout->time;
            (*(timeout->items + i))->callable = callable;

            return timeout->last;
        }
    }

    return 0;
}

Timeout_Status_t Timeout_cancelHandler(Timeout_List_t *timeout, uint32_t identity) {
    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if ((*(timeout->items + i)) != NULL && (*(timeout->items + i))->identity == identity) {
            (*(timeout->items + i)) = NULL;
            return TIMEOUT_SUCCESS;
        }
    }

    return TIMEOUT_FAILURE;
}

void Timeout_dispatch(Timeout_List_t *timeout, uint32_t time) {
    timeout->time = time;

    for (uint8_t i = 0; i < timeout->limit; ++i) {
        if ((*(timeout->items + i)) == NULL) {
            continue;
        }

        if ((*(timeout->items + i))->schedule < time) {
            (*(timeout->items + i))->callable();

            if ((*(timeout->items + i))->interval > 0) {
                (*(timeout->items + i))->schedule += timeout->items[i]->interval;
            } else {
                (*(timeout->items + i)) = NULL;
            }
        }
    }
}
