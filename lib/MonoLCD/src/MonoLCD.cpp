#include "MonoLCD.h"

MonoLCD::MonoLCD(uint16_t width, uint16_t height) {
    this->_width  = width;
    this->_height = height;

    uint8_t buffer[width * height / 8];

    this->_buffer = buffer;
}

void MonoLCD::pixel(uint16_t x, uint16_t y, MonoLCD_COLOR_t color) {
    if (x >= this->_width || y >= this->_height) return;

    if (color == MonoLCD_COLOR_WHITE) {
        this->_buffer[x + (y / 8) * this->_width] |= 1u << (y % 8u);
    } else {
        this->_buffer[x + (y / 8) * this->_width] &= ~(1u << (y % 8u));
    }
}

//TODO
void MonoLCD::line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color) {
    if (x0 >= this->_width) x0 = this->_width - 1;
    if (x1 >= this->_width) x1 = this->_width - 1;
    if (y0 >= this->_height) y0 = this->_height - 1;
    if (y1 >= this->_height) y1 = this->_height - 1;

    int16_t dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    int16_t dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);

    if (dx == 0) {/*vertical line*/return;}

    if (dy == 0) {/*horizontal line*/return;}

    /*diagonal line*/
}
