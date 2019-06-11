#include "PE_Servomotor.h"

PE_Servomotor::PE_Servomotor(PE_Servomotor_write_t send) {
    _send = send;
}

void PE_Servomotor::setDegree(uint16_t value) {
    _send(PE_SERVOMOTOR_SET_DEGREE, value);
}

void PE_Servomotor::setMicros(uint16_t value) {
    _send(PE_SERVOMOTOR_SET_MICROS, value);
}

void PE_Servomotor::setMinimum(uint16_t value) {
    _send(PE_SERVOMOTOR_SET_MINIMUM, value);
}

void PE_Servomotor::setMaximum(uint16_t value) {
    _send(PE_SERVOMOTOR_SET_MAXIMUM, value);
}