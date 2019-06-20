#ifndef PE_MGFX_H
#define PE_MGFX_H

#include <stdint.h>

typedef enum {
    PE_mGFX_BLACK,
    PE_mGFX_WHITE,
} PE_mGFX_Color_t;

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t lsb;
} PE_mGFX_Bitmap_t;

typedef struct {
    const uint16_t *bitmap;
    uint8_t width;
    uint8_t height;
} PE_mGFX_Font_t;

class PE_mGFX {
private:
    uint8_t *_buffer;
    uint16_t _width;
    uint16_t _height;

public:
    /**
     * Create GFX canvas
     *
     * @param width
     * @param height
     */
    PE_mGFX(uint16_t width, uint16_t height);

    /**
     * Initialize internal buffer
     *
     * @return
     */
    bool initialize();

    /**
     * Clear buffer data
     */
    void clear();

    /**
     * Draw pixel
     *
     * @param x
     * @param y
     * @param color
     */
    void pixel(uint16_t x, uint16_t y, PE_mGFX_Color_t color);

    /**
     * Draw line
     *
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param color
     */
    void line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color);

    /**
     * Draw rectangle
     *
     * @param x0
     * @param y0
     * @param x1
     * @param y1
     * @param color
     */
    void rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color);

    /**
     * Draw circle
     *
     * @param cx
     * @param cy
     * @param r
     * @param color
     */
    void circle(uint16_t cx, uint16_t cy, uint16_t r, PE_mGFX_Color_t color);

    /**
     * Draw bitmap
     *
     * @param x
     * @param y
     * @param bitmap
     * @param color
     */
    void bitmap(uint16_t x, uint16_t y, PE_mGFX_Bitmap_t *bitmap, PE_mGFX_Color_t color);

    /**
     * Draw single char
     *
     * @param x
     * @param y
     * @param symbol
     * @param font
     * @param color
     */
    void symbol(uint16_t x, uint16_t y, char symbol, PE_mGFX_Font_t *font, PE_mGFX_Color_t color);

    /**
     * Draw string
     *
     * @param x
     * @param y
     * @param string
     * @param font
     * @param color
     */
    void string(uint16_t x, uint16_t y, const char *string, PE_mGFX_Font_t *font, PE_mGFX_Color_t color);

    /**
     * Get internal buffer size
     *
     * @return
     */
    uint16_t getBufferSize();

    /**
     * Get pointer to internal buffer
     *
     * @return
     */
    uint8_t * getBufferData();
};

#endif //PE_MGFX_H
