#ifndef _G_GFX_H
#define _G_GFX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
} gGFX_Buffer_t;

void gGFX_initialize(gGFX_Buffer_t *buffer);
void gGFX_clear(gGFX_Buffer_t *buffer);

/**
 * @param x
 * @param y
 * @param color
 */
void mGFX_pixel(uint16_t x, uint16_t y, uint8_t color);

/**
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);

/**
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);

/**
 * @param cx
 * @param cy
 * @param r
 * @param color
 */
void mGFX_circle(uint16_t cx, uint16_t cy, uint16_t r, uint8_t color);

/**
 * @param x
 * @param y
 * @param bitmap
 * @param color
 */
void mGFX_bitmap(uint16_t x, uint16_t y, MonoLCD_BITMAP_t *bitmap);

/**
 * @param x
 * @param y
 * @param symbol
 * @param font
 * @param color
 */
void mGFX_symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, uint8_t color);

/**
 * @param x
 * @param y
 * @param string
 * @param font
 * @param color
 */
void mGFX_string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, uint8_t color);

#ifdef __cplusplus
}
#endif

#endif //_G_GFX_H
