#include "PE_Button.h"

#define PE_BUTTON_STATE_CURRENT  0
#define PE_BUTTON_STATE_PREVIOUS 1

#define PE_BUTTON_BIT_GET(_byte_, _bit_) (((_byte_) >> (_bit_)) & 0x01)
#define PE_BUTTON_BIT_SET(_byte_, _bit_) ((_byte_) |= (1UL << (_bit_)))
#define PE_BUTTON_BIT_CLR(_byte_, _bit_) ((_byte_) &= ~(1UL << (_bit_)))

uint8_t state;

PE_Button::PE_Button(PE_ButtonReader_t reader) {
    _reader = reader;
}

void PE_Button::initialize(uint32_t time) {
    _time = time;
}

void PE_Button::dispatch(uint32_t time) {
    _time = time;

    // Save the previous value
    if (PE_BUTTON_BIT_GET(_status, PE_BUTTON_STATE_CURRENT)) {
        PE_BUTTON_BIT_SET(_status, PE_BUTTON_STATE_PREVIOUS);
    } else {
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATE_PREVIOUS);
    }

    // Save the current state (0 == released, 1 == pressed)
    if (_reader()) {
        PE_BUTTON_BIT_SET(_status, PE_BUTTON_STATE_CURRENT);
    } else {
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATE_CURRENT);
    }

    /*if (BUTTON_BIT_READ(_state, BUTTON_BIT_CURRENT) != BUTTON_BIT_READ(_state, BUTTON_BIT_PREVIOUS)) {
        // If state changed - reset counter and return unknown state
        _counter = 0;

        // Clear callback triggered flags
        BUTTON_BIT_CLEAR(_state, BUTTON_BIT_ON_PRESS);
        BUTTON_BIT_CLEAR(_state, BUTTON_BIT_ON_RELEASE);
        BUTTON_BIT_CLEAR(_state, BUTTON_BIT_ON_HOLD);

        return BUTTON_STATE_UNKNOWN;
    } else {
        if (_counter < sizeof(uint32_t)) {
            _counter++;
        }

        if (BUTTON_BIT_READ(_state, BUTTON_BIT_CURRENT)) {
            if (_counter < BUTTON_DEBRIEF_THRESHOLD) {
                // If counter less than debrief threshold - return unknown state
                return BUTTON_STATE_UNKNOWN;
            }

            return BUTTON_STATE_PRESSED;
        } else {
            if (_counter < BUTTON_DEBRIEF_THRESHOLD) {
                // If counter less than debrief threshold - return unknown state
                return BUTTON_STATE_UNKNOWN;
            }

            return BUTTON_STATE_RELEASED;
        }
    }*/
}
