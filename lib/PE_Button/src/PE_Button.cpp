#include "PE_Button.h"

#define PE_BUTTON_STATUS_CURRENT           0
#define PE_BUTTON_STATUS_PREVIOUS          1
#define PE_BUTTON_STATUS_TRIGGERED_PRESS   2
#define PE_BUTTON_STATUS_TRIGGERED_RELEASE 3
#define PE_BUTTON_STATUS_TRIGGERED_HOLD    4

#define PE_BUTTON_BIT_GET(_byte_, _bit_) (((_byte_) >> (_bit_)) & 0x01)
#define PE_BUTTON_BIT_SET(_byte_, _bit_) ((_byte_) |= (1UL << (_bit_)))
#define PE_BUTTON_BIT_CLR(_byte_, _bit_) ((_byte_) &= ~(1UL << (_bit_)))

PE_Button::PE_Button(PE_ButtonReader_t reader) {
    _reader = reader;
}

void PE_Button::initialize(uint32_t time) {
    _time = time;
}

void PE_Button::dispatch(uint32_t time) {
    _time = time;

    PE_ButtonState_t state;

    // Save the previous value
    if (PE_BUTTON_BIT_GET(_status, PE_BUTTON_STATUS_CURRENT)) {
        PE_BUTTON_BIT_SET(_status, PE_BUTTON_STATUS_PREVIOUS);
    } else {
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATUS_PREVIOUS);
    }

    // Save the current state (0 == released, 1 == pressed)
    if (_reader()) {
        PE_BUTTON_BIT_SET(_status, PE_BUTTON_STATUS_CURRENT);
    } else {
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATUS_CURRENT);
    }

    if (PE_BUTTON_BIT_GET(_status, PE_BUTTON_STATUS_CURRENT) != PE_BUTTON_BIT_GET(_status, PE_BUTTON_STATUS_PREVIOUS)) {
        // If state changed - reset counter and return unknown state
        _counter = 0;

        // Clear callback triggered flags
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATUS_TRIGGERED_PRESS);
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATUS_TRIGGERED_RELEASE);
        PE_BUTTON_BIT_CLR(_status, PE_BUTTON_STATUS_TRIGGERED_HOLD);

        return;
    } else {
        if (_counter < sizeof(uint32_t)) {
            _counter++;
        }

        if (PE_BUTTON_BIT_GET(_status, PE_BUTTON_STATUS_CURRENT)) {
            if (_counter < BUTTON_DEBRIEF_THRESHOLD) {
                // If counter less than debrief threshold - return unknown state
                state = PE_BUTTON_STATE_UNKNOWN;
            } else {
                state = PE_BUTTON_STATE_PRESSED;
            }
        } else {
            if (_counter < BUTTON_DEBRIEF_THRESHOLD) {
                // If counter less than debrief threshold - return unknown state
                state = PE_BUTTON_STATE_UNKNOWN;
            } else {
                state = PE_BUTTON_STATE_RELEASED;
            }
        }
    }
}
