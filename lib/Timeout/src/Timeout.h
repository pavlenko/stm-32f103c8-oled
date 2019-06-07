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
    uint32_t identity;
    uint32_t interval;
    uint32_t schedule;
    void (*callable)();
} Timeout_Timer_t;

typedef Timeout_Timer_t *Timeout_Item_t;

typedef struct {
    uint32_t time;
    uint32_t last;
    uint8_t limit;
    Timeout_Item_t *items;
} Timeout_List_t;

/**
 * Initialize handlers list with specific time and size
 *
 * @param timeout
 * @param time
 * @param limit
 *
 * @return Success or failure if cannot allocate memory for list
 */
Timeout_Status_t Timeout_initialize(Timeout_List_t *timeout, uint32_t time, uint8_t limit);

/**
 * Create and attach singular run handler
 *
 * @param timeout
 * @param interval
 * @param callable
 *
 * @return Handler identity for use in cancel logic or 0 if cannot create handler
 */
uint32_t Timeout_createHandlerSingular(Timeout_List_t *timeout, uint32_t interval, void (*callable)());

/**
 * Create and attach repeated run handler
 *
 * @param timeout
 * @param interval
 * @param callable
 *
 * @return Handler identity for use in cancel logic or 0 if cannot create handler
 */
uint32_t Timeout_createHandlerRepeated(Timeout_List_t *timeout, uint32_t interval, void (*callable)());

/**
 * Cancel specific handler by identity
 *
 * @param timeout
 * @param identity
 *
 * @return Success or failure if no handler with specific identity
 */
Timeout_Status_t Timeout_cancelHandler(Timeout_List_t *timeout, uint32_t identity);

/**
 * Dispatch handlers, must be called as fast as possible but at least at each millisecond
 *
 * @param timeout
 * @param time
 */
void Timeout_dispatch(Timeout_List_t *timeout, uint32_t time);

#ifdef __cplusplus
}
#endif

#endif //TIMEOUT_H
