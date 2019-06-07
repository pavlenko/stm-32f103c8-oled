#ifndef TIMEOUT_H
#define TIMEOUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    TIMEOUT_SUCCESS = 0x00u,
    TIMEOUT_FAILURE = 0x01u,
} Timeout_Status_t;

typedef struct {
    uint32_t interval;
    uint32_t schedule;
    void (*callable)();
} Timeout_Timer_t;

typedef Timeout_Timer_t *Timeout_Item_t;

typedef struct {
    uint8_t limit;
    Timeout_Item_t *items;
} Timeout_List_t;

Timeout_Status_t Timeout_initialize(Timeout_List_t *timeout, uint8_t limit);

Timeout_Status_t Timeout_attachTimer(Timeout_List_t *timeout, Timeout_Timer_t *timer);

Timeout_Status_t Timeout_cancelTimer(Timeout_List_t *timeout, Timeout_Timer_t *timer);

void Timeout_dispatch(Timeout_List_t *timeout, uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif //TIMEOUT_H
