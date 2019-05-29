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
    void pixel(uint16_t x, uint16_t y, MonoLCD_COLOR_t color);

    /**
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param color
     */
    void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color);

    /**
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param color
     */
    void rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color);

    /**
     * @param cx
     * @param cy
     * @param r
     * @param color
     */
    void circle(uint16_t cx, uint16_t cy, uint16_t r, MonoLCD_COLOR_t color);
};

#endif //MONO_LCD_H
