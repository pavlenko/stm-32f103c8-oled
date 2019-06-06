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
} Timer_t;

typedef struct {
    uint8_t limit;
    Timer_t **items;
} Timeout_t;

void Timeout_initialize(Timeout_t *timeout, uint8_t limit);

Timeout_Status_t Timeout_attachTimer(Timeout_t *timeout, Timer_t *timer);

Timeout_Status_t Timeout_cancelTimer(Timeout_t *timeout, Timer_t *timer);

void Timeout_dispatch(Timeout_t *timeout, uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif //TIMEOUT_H
