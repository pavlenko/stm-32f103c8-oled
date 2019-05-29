#include "MonoLCD.h"

MonoLCD::MonoLCD(uint16_t width, uint16_t height) {
    this->_width  = width;
    this->_height = height;

    uint8_t buffer[width * height / 8];

    this->_buffer = buffer;
}

void MonoLCD::drawPixel(uint16_t x, uint16_t y, MonoLCD_COLOR_t color) {
    if (x >= this->_width || y >= this->_height) {
        return;
    }

    if (color == MonoLCD_COLOR_WHITE) {
        this->_buffer[x + (y / 8) * this->_width] |= 1u << (y % 8u);
    } else {
        this->_buffer[x + (y / 8) * this->_width] &= ~(1u << (y % 8u));
    }
}
