#include "mGFX.h"

#include <malloc.h>
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
    int16_t dx  = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    int16_t dy  = (y0 < y1) ? (y1 - y0) : (y0 - y1);
    int16_t sx  = (x0 < x1) ? 1 : -1;
    int16_t sy  = (y0 < y1) ? 1 : -1;
    int16_t err = ((dx > dy) ? dx : -dy) / 2;

    if (dx == 0) {
        do {
            mGFX_pixel(handle, x0, y0, color);
            y0 += dy;
        } while (y0 != y1);

        return;
    }

    if (dy == 0) {
        do {
            mGFX_pixel(handle, x0, y0, color);
            x0 += dx;
        } while (x0 != x1);

        return;
    }

    do {
        mGFX_pixel(handle, x0, y0, color);

        if (err > -dx) {
            err -= dy;
            x0  += sx;
        }

        if (err < dy) {
            err += dx;
            y0  += sy;
        }
    } while (x0 != x1 || y0 != y1);
}

void mGFX_rectangle(mGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, mGFX_Color_t color) {
    mGFX_line(handle, x0, y0, x1, y0, color);
    mGFX_line(handle, x0, y1, x1, y1, color);
    mGFX_line(handle, x0, y0, x0, y1, color);
    mGFX_line(handle, x1, y0, x1, y1, color);
}
