#ifndef PE_BUTTON_H
#define PE_BUTTON_H

#include <stdint.h>

//TODO click handle
//TODO long press handle
//TODO periodic update on hold

typedef struct {
    void (*onPressed) ();
    void (*onRelease) ();
    void (*onDispatch) ();
} PE_Button_t;

class PE_Buttons {
private:
    uint32_t _time = 0;
public:
    void initialize(uint32_t time);

    void dispatch(uint32_t time);
};


#endif //PE_BUTTON_H
