#ifndef MONO_LCD_H
#define MONO_LCD_H

#include <stdint.h>

typedef enum {
    MonoLCD_COLOR_BLACK,
    MonoLCD_COLOR_WHITE,
} MonoLCD_COLOR_t;

class MonoLCD {
private:
    uint8_t *_buffer;
    uint16_t _width;
    uint16_t _height;
public:
    /**
     * @param width
     * @param height
     */
    MonoLCD(uint16_t width, uint16_t height);

    /**
     * @param x
     * @param y
     * @param color
     */
    void drawPixel(uint16_t x, uint16_t y, MonoLCD_COLOR_t color);
};

#endif //MONO_LCD_H
