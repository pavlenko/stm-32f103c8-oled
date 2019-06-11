#include "PE_Servomotor.h"

PE_Servomotor::PE_Servomotor(PE_Servomotor_write_t write) {
    _write = write;
}

PE_Servomotor::PE_Servomotor(uint16_t min, uint16_t max) {
    _min = min;
    _max = max;
}

uint16_t PE_Servomotor::getMin() const {
    return _min;
}

void PE_Servomotor::setMin(uint16_t min) {
    _min = min;
}

uint16_t PE_Servomotor::getMax() const {
    return _max;
}

void PE_Servomotor::setMax(uint16_t max) {
    _max = max;
}
