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
    uint8_t *buffer;
    uint16_t width;
    uint16_t height;
} mGFX_Handle_t;

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t lsb;
} mGFX_Bitmap_t;

/**
 * @param handle
 * @param width
 * @param height
 */
void mGFX_initialize(mGFX_Handle_t *handle, uint16_t width, uint16_t height);

/**
 * @param handle
 */
void mGFX_clear(mGFX_Handle_t *handle);

/**
 * @param handle
 * @param x
 * @param y
 * @param color
 */
void mGFX_pixel(mGFX_Handle_t *handle, uint16_t x, uint16_t y, mGFX_Color_t color);

/**
 * @param handle
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_line(mGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color);

/**
 * @param handle
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void mGFX_rectangle(mGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color);

/**
 * @param handle
 * @param cx
 * @param cy
 * @param r
 * @param color
 */
void mGFX_circle(mGFX_Handle_t *handle, uint16_t cx, uint16_t cy, uint16_t r, mGFX_Color_t color);

/**
 * @param handle
 * @param x
 * @param y
 * @param bitmap
 * @param color
 */
void mGFX_bitmap(mGFX_Handle_t *handle, uint16_t x, uint16_t y, mGFX_Bitmap_t *bitmap, mGFX_Color_t color);

/**
 * @param x
 * @param y
 * @param symbol
 * @param font
 * @param color
 */
//void mGFX_symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, mGFX_Color_t color);

/**
 * @param x
 * @param y
 * @param string
 * @param font
 * @param color
 */
//void mGFX_string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, mGFX_Color_t color);

#ifdef __cplusplus
}
#endif

#endif //_M_GFX_H
