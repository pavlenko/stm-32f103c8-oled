#ifndef MONO_LCD_H
#define MONO_LCD_H

#include <stdint.h>

typedef enum {
    MonoLCD_COLOR_BLACK,
    MonoLCD_COLOR_WHITE,
} MonoLCD_COLOR_t;

typedef struct {
    const uint8_t *data;
    uint16_t width;
    uint16_t height;
} MonoLCD_BITMAP_t;

typedef struct {
    const uint16_t *data;
    uint16_t width;
    uint16_t height;
} MonoLCD_FONT_t;

typedef void (*MonoLCD_ADAPTER_t)(uint8_t *data, uint16_t length);

class MonoLCD {
private:
    uint8_t *_buffer;
    uint16_t _width;
    uint16_t _height;
    MonoLCD_ADAPTER_t _adapter;
public:
    /**
     * @param width
     * @param height
     */
    MonoLCD(uint16_t width, uint16_t height);

    void update();

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
     * @param fill
     */
    void rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color, bool fill);

    /**
     * @param cx
     * @param cy
     * @param r
     * @param color
     * @param fill
     */
    void circle(uint16_t cx, uint16_t cy, uint16_t r, MonoLCD_COLOR_t color, bool fill);

    /**
     * @param x
     * @param y
     * @param bitmap
     * @param color
     */
    void bitmap(uint16_t x, uint16_t y, MonoLCD_BITMAP_t *bitmap, MonoLCD_COLOR_t color);

    /**
     * @param x
     * @param y
     * @param symbol
     * @param font
     * @param color
     */
    void symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, MonoLCD_COLOR_t color);

    /**
     * @param x
     * @param y
     * @param string
     * @param font
     * @param color
     */
    void string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, MonoLCD_COLOR_t color);
};

#endif //MONO_LCD_H
