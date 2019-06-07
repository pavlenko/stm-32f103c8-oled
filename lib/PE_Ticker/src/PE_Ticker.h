#ifndef PE_TICKER_H
#define PE_TICKER_H

#include <stdint.h>

typedef struct {
    uint32_t identity;
    uint32_t interval;
    uint32_t schedule;
    void (*callable)();
} PE_Ticker_Handler_t;

class PE_Ticker {
private:
    uint32_t _last = 0;
    uint32_t _time = 0;
    uint8_t _size  = 0;
    PE_Ticker_Handler_t **_list = nullptr;
public:
    PE_Ticker() = default;

    /**
     * Initialize handlers list with specific time and size
     *
     * @param time
     * @param limit
     *
     * @return true or false if cannot allocate memory for list
     */
    bool initialize(uint32_t time, uint8_t size);

    /**
     * Create and attach singular run handler
     *
     * @param interval
     * @param callable
     *
     * @return Handler identity for use in cancel logic or 0 if cannot create handler
     */
    uint32_t createHandlerSingular(uint32_t interval, void (*callable)());

    /**
     * Create and attach repeated run handler
     *
     * @param interval
     * @param callable
     *
     * @return Handler identity for use in cancel logic or 0 if cannot create handler
     */
    uint32_t createHandlerRepeated(uint32_t interval, void (*callable)());

    /**
     * Cancel specific handler by identity
     *
     * @param identity
     *
     * @return true or false if no handler with specific identity
     */
    bool cancelHandler(uint32_t identity);

    /**
     * Dispatch handlers, must be called as fast as possible but at least at each millisecond
     *
     * @param time
     */
    void dispatch(uint32_t time);
};

#endif //PE_TICKER_H
