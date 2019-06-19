#include "PE_Joystick.h"

void PE_Joystick::update(void) {
    if (_reader) {
        _xPosition = _reader(PE_JOYSTICK_AXIS_X);
        _yPosition = _reader(PE_JOYSTICK_AXIS_Y);
    }
}

int8_t PE_Joystick::getXPosition(void) {
    return _xPosition;
}

void PE_Joystick::setXPosition(int8_t position) {
    _xPosition = position;
}

int8_t PE_Joystick::getYPosition(void) {
    return _yPosition;
}

void PE_Joystick::setYPosition(int8_t position) {
    _yPosition = position;
}
