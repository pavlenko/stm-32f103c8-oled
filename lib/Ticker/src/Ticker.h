#ifndef TICKER_H
#define TICKER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*Ticker_Handler_t) ();

typedef struct {
    uint32_t interval;
    void (*callback) ();
} Ticker_Timer_t;

typedef struct {
    uint32_t        currentTime;
    Ticker_Timer_t *repeatedList;
    uint8_t         repeatedSize;
    Ticker_Timer_t *singularList;
    uint8_t         singularSize;
} Ticker_Handle_t;

void Ticker_initialize();

void Ticker_setSingular(uint32_t intervalMS, Ticker_Handler_t handler);

void Ticker_setRepeated(uint32_t intervalMS, Ticker_Handler_t handler);

void Ticker_dispatch();

#ifdef __cplusplus
}
#endif

#endif //TICKER_H
