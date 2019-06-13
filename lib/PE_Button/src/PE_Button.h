#ifndef PE_BUTTON_H
#define PE_BUTTON_H

#include <stdint.h>

//TODO click handle
//TODO long press handle
//TODO periodic update on hold

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
public:
    explicit PE_Button(PE_ButtonReader_t reader);

    void initialize(uint32_t time);

    void dispatch(uint32_t time);
};

#endif //PE_BUTTON_H
