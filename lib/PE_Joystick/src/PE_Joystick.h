#ifndef PE_JOYSTICK_H
#define PE_JOYSTICK_H

#include <stdint.h>

typedef enum {
    PE_JOYSTICK_AXIS_X,
    PE_JOYSTICK_AXIS_Y,
} PE_JoystickAxis_t;

typedef int8_t (*PE_JoystickReader_t) (PE_JoystickAxis_t axis);

class PE_Joystick {
private:
    int8_t _xPosition = 0;
    int8_t _yPosition = 0;
    PE_JoystickReader_t _reader = nullptr;
public:
    /**
     * Update joystick positions in blocking mode
     */
    void update(void);

    int8_t getXPosition(void);

    void setXPosition(int8_t position);

    int8_t getYPosition(void);

    void setYPosition(int8_t position);
};


#endif //PE_JOYSTICK_H
