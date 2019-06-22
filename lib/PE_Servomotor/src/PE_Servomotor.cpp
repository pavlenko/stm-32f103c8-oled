#include "PE_Servomotor.h"

PE_Servomotor::PE_Servomotor(PE_Servomotor_send_t send, PE_Servomotor_read_t read) {
    _send = send;
    _read = read;
}

uint16_t PE_Servomotor::getDegree()
{
    return _read(PE_SERVOMOTOR_GET_DEGREE);
}

void PE_Servomotor::setDegree(uint16_t value)
{
    _send(PE_SERVOMOTOR_SET_DEGREE, value);
}

void PE_Servomotor::setMicros(uint16_t value)
{
    _send(PE_SERVOMOTOR_SET_MICROS, value);
}

uint16_t PE_Servomotor::getMinimum()
{
    return _read(PE_SERVOMOTOR_GET_MINIMUM);
}

void PE_Servomotor::setMinimum(uint16_t value)
{
    _send(PE_SERVOMOTOR_SET_MINIMUM, value);
}

uint16_t PE_Servomotor::getMaximum()
{
    return _read(PE_SERVOMOTOR_GET_MAXIMUM);
}

void PE_Servomotor::setMaximum(uint16_t value)
{
    _send(PE_SERVOMOTOR_SET_MAXIMUM, value);
}