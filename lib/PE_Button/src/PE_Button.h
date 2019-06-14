#ifndef PE_BUTTON_H
#define PE_BUTTON_H

#include <stdint.h>

//TODO click handle

#ifndef PE_BUTTON_THRESHOLD_DEBRIEF
#define PE_BUTTON_THRESHOLD_DEBRIEF 10U
#endif

#ifndef PE_BUTTON_THRESHOLD_HOLD
#define PE_BUTTON_THRESHOLD_HOLD 1000U
#endif

// Timeout for execute repeated hold callback, must match condition: <val> > (<holdMS> - <debriefMS>) * 2
#ifndef PE_BUTTON_TIMEOUT_REPEATED
#define PE_BUTTON_TIMEOUT_REPEATED 250U
#endif

typedef enum {
    PE_BUTTON_STATE_RELEASED = -1,
    PE_BUTTON_STATE_UNKNOWN  =  0,
    PE_BUTTON_STATE_PRESSED  =  1,
} PE_ButtonState_t;

typedef bool (*PE_ButtonReader_t) ();

class PE_Button {
private:
    PE_ButtonReader_t _reader;
    uint8_t _status = 0;
    uint32_t _time = 0;
    void (*_onPress) ();
    void (*_onRelease) ();
    void (*_onHoldSingular) ();
    void (*_onHoldRepeated) ();
public:
    explicit PE_Button(PE_ButtonReader_t reader);

    void initialize(uint32_t time);

    void dispatch(uint32_t time);
};

#endif //PE_BUTTON_H
