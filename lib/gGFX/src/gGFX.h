#ifndef _G_GFX_H
#define _G_GFX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t *buffer;
    uint16_t width;
    uint16_t height;
} gGFX_Handle_t;

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
} gGFX_Bitmap_t;

/**
 * @param handle
 * @param width
 * @param height
 */
void gGFX_initialize(gGFX_Handle_t *handle, uint16_t width, uint16_t height);

/**
 * @param handle
 */
void gGFX_clear(gGFX_Handle_t *handle);

/**
 * @param handle
 * @param x
 * @param y
 * @param color
 */
void gGFX_pixel(gGFX_Handle_t *handle, uint16_t x, uint16_t y, uint8_t color);

/**
 * @param handle
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void gGFX_line(gGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);

/**
 * @param handle
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void gGFX_rectangle(gGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);

/**
 * @param handle
 * @param cx
 * @param cy
 * @param r
 * @param color
 */
void gGFX_circle(gGFX_Handle_t *handle, uint16_t cx, uint16_t cy, uint16_t r, uint8_t color);

/**
 * @param handle
 * @param x
 * @param y
 * @param bitmap
 * @param color
 */
void gGFX_bitmap(gGFX_Handle_t *handle, uint16_t x, uint16_t y, gGFX_Bitmap_t *bitmap);

/**
 * @param x
 * @param y
 * @param symbol
 * @param font
 * @param color
 */
//void gGFX_symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, uint8_t color);

/**
 * @param x
 * @param y
 * @param string
 * @param font
 * @param color
 */
//void gGFX_string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, uint8_t color);

#ifdef __cplusplus
}
#endif

#endif //_G_GFX_H
