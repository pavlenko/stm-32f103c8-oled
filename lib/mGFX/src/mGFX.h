#ifndef _M_GFX_H
#define _M_GFX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    mGFX_BLACK,
    mGFX_WHITE,
} mGFX_Color_t;

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
} mGFX_Buffer_t;

void mGFX_initialize(mGFX_Buffer_t *buffer);
void mGFX_clear(mGFX_Buffer_t *buffer);

/**
 * @param x
 * @param y
 * @param color
 */
void mGFX_pixel(uint16_t x, uint16_t y, mGFX_Color_t color);

/**
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color);

/**
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color);

/**
 * @param cx
 * @param cy
 * @param r
 * @param color
 */
void mGFX_circle(uint16_t cx, uint16_t cy, uint16_t r, mGFX_Color_t color);

/**
 * @param x
 * @param y
 * @param bitmap
 * @param color
 */
void mGFX_bitmap(uint16_t x, uint16_t y, MonoLCD_BITMAP_t *bitmap, mGFX_Color_t color);

/**
 * @param x
 * @param y
 * @param symbol
 * @param font
 * @param color
 */
void mGFX_symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, mGFX_Color_t color);

/**
 * @param x
 * @param y
 * @param string
 * @param font
 * @param color
 */
void mGFX_string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, mGFX_Color_t color);

#ifdef __cplusplus
}
#endif

#endif //_M_GFX_H
