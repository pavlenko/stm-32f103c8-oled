#include "PE_Button.h"

#define STATUS_CURRENT_Pos (0U)
#define STATUS_CURRENT_Msk (1U << STATUS_CURRENT_Pos)
#define STATUS_CURRENT     STATUS_CURRENT_Msk

#define STATUS_PREVIOUS_Pos (1U)
#define STATUS_PREVIOUS_Msk (1U << STATUS_PREVIOUS_Pos)
#define STATUS_PREVIOUS     STATUS_PREVIOUS_Msk

#define STATUS_TRIG_PRESS_Pos (2U)
#define STATUS_TRIG_PRESS_Msk (1U << STATUS_TRIG_PRESS_Pos)
#define STATUS_TRIG_PRESS     STATUS_TRIG_PRESS_Msk

#define STATUS_TRIG_RELEASE_Pos (3U)
#define STATUS_TRIG_RELEASE_Msk (1U << STATUS_TRIG_RELEASE_Pos)
#define STATUS_TRIG_RELEASE     STATUS_TRIG_RELEASE_Msk

#define STATUS_TRIG_HOLD_Pos (4U)
#define STATUS_TRIG_HOLD_Msk (1U << STATUS_TRIG_HOLD_Pos)
#define STATUS_TRIG_HOLD     STATUS_TRIG_HOLD_Msk

PE_Button::PE_Button(PE_ButtonReader_t reader) {
    _reader = reader;
}

void PE_Button::initialize(uint32_t millis) {
    _millis = millis;
}

void PE_Button::dispatch(uint32_t millis) {
    // Save previous state
    if (_status & STATUS_CURRENT) {
        _status |= STATUS_PREVIOUS;
    } else {
        _status &= ~STATUS_PREVIOUS;
    }

    // Read current state and prefetch handlers & flag positions
    if (_reader()) {
        _status |= STATUS_CURRENT;
    } else {
        _status &= ~STATUS_CURRENT;
    }

    // Reset execution flags if state changed
    if ((_status & STATUS_CURRENT) != (_status & STATUS_PREVIOUS)) {
        _millis = millis;
        _status &= ~(STATUS_TRIG_PRESS | STATUS_TRIG_RELEASE | STATUS_TRIG_HOLD);
        return;
    }

    // Process pressed/released handler, must be first because must called always
    if (millis - _millis > PE_BUTTON_TIMEOUT_DEBRIEF) {
        if ((_status & STATUS_CURRENT) == 1U) {
            if ((_status & STATUS_TRIG_PRESS) == 0U) {
                _status |= STATUS_TRIG_PRESS;
                if (_onPress) _onPress();
            }
        } else {
            if ((_status & STATUS_TRIG_RELEASE) == 0U) {
                _status |= STATUS_TRIG_RELEASE;
                if (_onRelease) _onRelease();//TODO check not triggered before press
            }
        }
    }

#if PE_BUTTON_USE_HOLD_SINGULAR == 1
    // Process singular handler
    if (millis - _millis > PE_BUTTON_TIMEOUT_HOLD_SINGULAR) {
        if ((_status & STATUS_TRIG_HOLD) == 0U) {
            _status |= STATUS_TRIG_HOLD;
            if (_onHoldSingular) _onHoldSingular();
        }
    }
#endif

#if PE_BUTTON_USE_HOLD_REPEATED == 1
    // Process repeated handler
    if (millis - _millis > PE_BUTTON_TIMEOUT_HOLD_REPEATED) {
        _millis = millis - PE_BUTTON_TIMEOUT_REPEAT;
        if (_onHoldRepeated) _onHoldRepeated();
    }
#endif
}

void PE_Button::setOnPress(PE_ButtonHandler_t handler) {
    _onPress = handler;
}

void PE_Button::setOnRelease(PE_ButtonHandler_t handler) {
    _onRelease = handler;
}

#if PE_BUTTON_USE_HOLD_SINGULAR == 1
void PE_Button::setOnHoldSingular(PE_ButtonHandler_t handler) {
    _onHoldSingular = handler;
}
#endif

#if PE_BUTTON_USE_HOLD_REPEATED == 1
void PE_Button::setOnHoldRepeated(PE_ButtonHandler_t handler) {
    _onHoldRepeated = handler;
}
#endif
