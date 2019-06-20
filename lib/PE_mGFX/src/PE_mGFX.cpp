#include "PE_mGFX.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

PE_mGFX::PE_mGFX(uint16_t width, uint16_t height) {
    _width  = width;
    _height = height;
    _buffer = nullptr;
}

bool PE_mGFX::initialize() {
    if ((_buffer != nullptr) || !(_buffer = (uint8_t *) malloc(_width * ((_height + 7) / 8)))) {
        return false;
    }

    clear();

    return true;
}

void PE_mGFX::clear() {
    memset(_buffer, 0, _width * ((_height + 7) / 8));
}

void PE_mGFX::pixel(uint16_t x, uint16_t y, PE_mGFX_Color_t color) {
    if (x >= _width || y >= _height) return;

    if (color == PE_mGFX_WHITE) {
        _buffer[x + (y / 8) * _width] |= 1u << (y % 8u);
    } else if (color == PE_mGFX_BLACK) {
        _buffer[x + (y / 8) * _width] &= ~(1u << (y % 8u));
    }
}

void PE_mGFX::line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color) {
    uint16_t diffX = abs(x1 - x0);
    uint16_t diffY = abs(y1 - y0);

    if (diffX == 0 && diffY == 0) {
        return;
    }

    int stepX = (x0 > x1) ? -1 : 1;
    int stepY = (y0 > y1) ? -1 : 1;

    diffY <<= 1u; // diffY is now 2*diffY
    diffX <<= 1u; // diffX is now 2*diffX

    pixel(x0, y0, color);

    if (diffX > diffY) {
        // Optimization for draw line with width > height
        int fraction = diffY - (diffX >> 1u);

        while (x0 != x1) {
            if (fraction >= 0) {
                y0       += stepY;
                fraction -= diffX;
            }

            x0       += stepX;
            fraction += diffY;

            pixel(x0, y0, color);
        }
    } else {
        // Optimization for draw line with width < height
        int fraction = diffX - (diffY >> 1u);

        while (y0 != y1) {
            if (fraction >= 0) {
                x0       += stepX;
                fraction -= diffY;
            }

            y0       += stepY;
            fraction += diffX;

            pixel(x0, y0, color);
        }
    }
}

void PE_mGFX::rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color) {
    line(x0, y0, x1, y0, color);
    line(x0, y1, x1, y1, color);
    line(x0, y0, x0, y1, color);
    line(x1, y0, x1, y1, color);
}

void PE_mGFX::circle(uint16_t cx, uint16_t cy, uint16_t r, PE_mGFX_Color_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    pixel(cx, cy + r, color);
    pixel(cx, cy - r, color);
    pixel(cx + r, cy, color);
    pixel(cx - r, cy, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        pixel(cx + x, cy + y, color);
        pixel(cx - x, cy + y, color);
        pixel(cx + x, cy - y, color);
        pixel(cx - x, cy - y, color);

        pixel(cx + y, cy + x, color);
        pixel(cx - y, cy + x, color);
        pixel(cx + y, cy - x, color);
        pixel(cx - y, cy - x, color);
    }
}

void PE_mGFX::bitmap(uint16_t x, uint16_t y, PE_mGFX_Bitmap_t *bitmap, PE_mGFX_Color_t color) {
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

                if (byte & 0x80u) pixel(x + i, y, color);
            } else {
                if (i & 7u) {
                    byte >>= 1u;
                } else {
                    byte = bitmap->data[j * width + i / 8];
                }

                if (byte & 0x01u) pixel(x + i, y, color);
            }
        }
    }
}

void PE_mGFX::symbol(uint16_t x, uint16_t y, char symbol, PE_mGFX_Font_t *font, PE_mGFX_Color_t color) {
    uint16_t i, j, b;

    for (i = 0; i < font->height; i++) {
        b = font->bitmap[(symbol - 32) * font->height + i];

        for (j = 0; j < font->width; j++) {
            if ((b << j) & 0x8000) {
                pixel(x + j, y + i, (PE_mGFX_Color_t) color);
            } else {
                pixel(x + j, y + i, (PE_mGFX_Color_t) !color);
            }
        }
    }
}

void PE_mGFX::string(uint16_t x, uint16_t y, const char *string, PE_mGFX_Font_t *font, PE_mGFX_Color_t color) {
    while (*string) {
        symbol(x, y, *string, font, color);

        x += font->width;

        string++;
    }
}

uint16_t PE_mGFX::getBufferSize() {
    return _width * ((_height + 7) / 8);
}

uint8_t *PE_mGFX::getBufferData() {
    return _buffer;
}
