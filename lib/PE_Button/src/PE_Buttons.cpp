#include "PE_Buttons.h"

void PE_Buttons::initialize(uint32_t time) {
    _time = time;
}

void PE_Buttons::dispatch(uint32_t time) {
    _time = time;
}
