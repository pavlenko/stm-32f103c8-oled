#ifndef _M_GFX_FONT_H
#define _M_GFX_FONT_H

#include <stdint.h>

typedef struct {
    const uint16_t *bitmap;
    uint8_t width;
    uint8_t height;
} mGFX_Font_t;

#endif //_M_GFX_FONT_H
