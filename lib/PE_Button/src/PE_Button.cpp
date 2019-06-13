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

#define PE_BUTTON_BIT_GET(_byte_, _bit_) (((_byte_) >> (_bit_)) & 0x01)
#define PE_BUTTON_BIT_SET(_byte_, _bit_) ((_byte_) |= (1UL << (_bit_)))
#define PE_BUTTON_BIT_CLR(_byte_, _bit_) ((_byte_) &= ~(1UL << (_bit_)))

PE_Button::PE_Button(PE_ButtonReader_t reader) {
    _reader = reader;
}

void PE_Button::initialize(uint32_t time) {
    _time = time;
}

void testOnPress(){}
void testOnRelease(){}

void PE_Button::dispatch(uint32_t time) {
    uint8_t position;
    void (*handler) ();

    if (_status & STATUS_CURRENT) {
        _status |= STATUS_PREVIOUS;
    } else {
        _status &= ~STATUS_PREVIOUS;
    }

    if (_reader()) {
        _status |= STATUS_CURRENT;
        position = STATUS_TRIG_PRESS_Pos;
        handler  = testOnPress;
    } else {
        _status &= ~STATUS_CURRENT;
        position = STATUS_TRIG_RELEASE_Pos;
        handler  = testOnRelease;
    }

    if ((_status & STATUS_CURRENT) != (_status & STATUS_PREVIOUS)) {
        _time = time;
        _status &= ~(STATUS_TRIG_PRESS | STATUS_TRIG_RELEASE | STATUS_TRIG_HOLD);
        return;
    }

    bool repeated = true;//TODO configurable
    //TODO how to implement both hold and repeated
    if (time - _time > PE_BUTTON_THRESHOLD_HOLD) {
        if (repeated) {
            _time = time - PE_BUTTON_TIMEOUT_REPEATED;
            handler();
        } else if ((_status & (1U << position)) == 0) {
            _status |= (1U << position);
            handler();
        }
    }

    if (time - _time < PE_BUTTON_THRESHOLD_DEBRIEF) {
        return;
    }

    if ((_status & (1U << position)) == 0) {
        _status |= (1U << position);
        handler();
    }
}
