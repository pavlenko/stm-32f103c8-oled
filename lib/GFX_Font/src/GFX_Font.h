#ifndef _GFX_FONT_H
#define _GFX_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef GFX_FONT_BITMAP_TYPE
#define GFX_FONT_BITMAP_TYPE
typedef const uint8_t GFX_Bitmap_t;
#endif

#ifndef GFX_FONT_GLYPH_TYPE
#define GFX_FONT_GLYPH_TYPE
typedef struct {
    uint16_t bitmapOffset; ///< Pointer into GFXfont->bitmap
    uint8_t  width;        ///< Bitmap dimensions in pixels
    uint8_t  height;       ///< Bitmap dimensions in pixels
    uint8_t  xAdvance;     ///< Distance to advance cursor (x axis)
    int8_t   xOffset;      ///< X dist from cursor pos to UL corner
    int8_t   yOffset;      ///< Y dist from cursor pos to UL corner
} GFX_Glyph_t;
#endif

#ifndef GFX_FONT_TYPE
#define GFX_FONT_TYPE
typedef struct {
    GFX_Bitmap_t *bitmap;  ///< Glyph bitmaps, concatenated
    GFX_Glyph_t  *glyph;   ///< Glyph array
    uint8_t      first;    ///< ASCII extents (first char)
    uint8_t      last;     ///< ASCII extents (last char)
    uint8_t      yAdvance; ///< Newline distance (y axis)
} GFX_Font_t;
#endif

#ifdef __cplusplus
}
#endif

#endif //_GFX_FONT_H
