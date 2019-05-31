#include "mGFX.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void mGFX_initialize(mGFX_Handle_t *handle, uint16_t width, uint16_t height) {
    handle->width  = width;
    handle->height = height;
    handle->buffer = (uint8_t *) malloc(handle->width * ((handle->height + 7) / 8));

    mGFX_clear(handle);
}

void mGFX_clear(mGFX_Handle_t *handle) {
    memset(handle->buffer, 0, handle->width * ((handle->height + 7) / 8));
}

void mGFX_pixel(mGFX_Handle_t *handle, uint16_t x, uint16_t y, mGFX_Color_t color) {
    if (x >= handle->width || y >= handle->height) return;

    if (color == mGFX_WHITE) {
        handle->buffer[x + (y / 8) * handle->width] |= 1u << (y % 8u);
    } else {
        handle->buffer[x + (y / 8) * handle->width] &= ~(1u << (y % 8u));
    }
}

void mGFX_line(mGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color) {
    int diffX = abs(x1 - x0);
    int diffY = abs(y1 - y0);

    if (diffX == 0 && diffY == 0) {
        return;
    }

    int stepX = (x0 > x1) ? -1 : 1;
    int stepY = (y0 > y1) ? -1 : 1;

    diffY <<= 1; // diffY is now 2*diffY
    diffX <<= 1; // diffX is now 2*diffX

    mGFX_pixel(handle, x0, y0, color);

    if (diffX > diffY) {
        // Optimization for draw line with width > height
        int fraction = diffY - (diffX >> 1);

        while (x0 != x1) {
            if (fraction >= 0) {
                y0       += stepY;
                fraction -= diffX;
            }

            x0       += stepX;
            fraction += diffY;

            mGFX_pixel(handle, x0, y0, color);
        }
    } else {
        // Optimization for draw line with width < height
        int fraction = diffX - (diffY >> 1);

        while (y0 != y1) {
            if (fraction >= 0) {
                x0       += stepX;
                fraction -= diffY;
            }

            y0       += stepY;
            fraction += diffX;

            mGFX_pixel(handle, x0, y0, color);
        }
    }
}

void mGFX_rectangle(mGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color) {
    mGFX_line(handle, x0, y0, x1, y0, color);
    mGFX_line(handle, x0, y1, x1, y1, color);
    mGFX_line(handle, x0, y0, x0, y1, color);
    mGFX_line(handle, x1, y0, x1, y1, color);
}

void mGFX_circle(mGFX_Handle_t *handle, uint16_t cx, uint16_t cy, uint16_t r, mGFX_Color_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    mGFX_pixel(handle, cx, cy + r, color);
    mGFX_pixel(handle, cx, cy - r, color);
    mGFX_pixel(handle, cx + r, cy, color);
    mGFX_pixel(handle, cx - r, cy, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        mGFX_pixel(handle, cx + x, cy + y, color);
        mGFX_pixel(handle, cx - x, cy + y, color);
        mGFX_pixel(handle, cx + x, cy - y, color);
        mGFX_pixel(handle, cx - x, cy - y, color);

        mGFX_pixel(handle, cx + y, cy + x, color);
        mGFX_pixel(handle, cx - y, cy + x, color);
        mGFX_pixel(handle, cx + y, cy - x, color);
        mGFX_pixel(handle, cx - y, cy - x, color);
    }
}

void mGFX_bitmap(mGFX_Handle_t *handle, uint16_t x, uint16_t y, mGFX_Bitmap_t *bitmap, mGFX_Color_t color) {
    uint16_t width = (bitmap->width + 7) / 8;
    uint8_t byte   = 0;

    for (uint16_t j = 0; j < bitmap->height; j++, y++) {
        for (uint16_t i = 0; i < bitmap->width; i++) {
            if (!bitmap->lsb) {
                if (i & 7u) {
                    byte <<= 1u;
                } else {
                    byte = bitmap->data[j * width + i / 8];
                }

                if (byte & 0x80u) mGFX_pixel(handle, x + i, y, color);
            } else {
                if (i & 7u) {
                    byte >>= 1u;
                } else {
                    byte = bitmap->data[j * width + i / 8];
                }

                if (byte & 0x01u) mGFX_pixel(handle, x + i, y, color);
            }
        }
    }
}

void mGFX_symbol(mGFX_Handle_t *handle, uint16_t x, uint16_t y, char symbol, mGFX_Font_t *font, mGFX_Color_t color) {
    uint16_t i, j, b;

    for (i = 0; i < font->height; i++) {
        b = font->bitmap[(symbol - 32) * font->height + i];

        for (j = 0; j < font->width; j++) {
            if ((b << j) & 0x8000) {
                mGFX_pixel(handle, x + j, y + i, (mGFX_Color_t) color);
            } else {
                mGFX_pixel(handle, x + j, y + i, (mGFX_Color_t) !color);
            }
        }
    }
}

void mGFX_string(mGFX_Handle_t *handle, uint16_t x, uint16_t y, const char *string, mGFX_Font_t *font, mGFX_Color_t color) {
    while (*string) {
        mGFX_symbol(handle, x, y, *string, font, color);

        x += font->width;

        string++;
    }
}
