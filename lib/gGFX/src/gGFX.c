#include "gGFX.h"

#include <malloc.h>
#include <string.h>

void gGFX_initialize(gGFX_Handle_t *handle, uint16_t width, uint16_t height) {
    handle->width  = width;
    handle->height = height;
    handle->buffer = (uint8_t *) malloc(handle->width * handle->height);

    gGFX_clear(handle);
}

void gGFX_clear(gGFX_Handle_t *handle) {
    memset(handle->buffer, 0, handle->width * handle->height);
}

void gGFX_pixel(gGFX_Handle_t *handle, uint16_t x, uint16_t y, uint8_t color) {
    if (x >= handle->width || y >= handle->height) return;

    handle->buffer[x + y * handle->width] = color;
}

void gGFX_line(gGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    int16_t dx  = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    int16_t dy  = (y0 < y1) ? (y1 - y0) : (y0 - y1);
    int16_t sx  = (x0 < x1) ? 1 : -1;
    int16_t sy  = (y0 < y1) ? 1 : -1;
    int16_t err = ((dx > dy) ? dx : -dy) / 2;

    if (dx == 0) {
        do {
            gGFX_pixel(handle, x0, y0, color);
            y0 += dy;
        } while (y0 != y1);

        return;
    }

    if (dy == 0) {
        do {
            gGFX_pixel(handle, x0, y0, color);
            x0 += dx;
        } while (x0 != x1);

        return;
    }

    do {
        gGFX_pixel(handle, x0, y0, color);

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

void gGFX_rectangle(gGFX_Handle_t *handle, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    gGFX_line(handle, x0, y0, x1, y0, color);
    gGFX_line(handle, x0, y1, x1, y1, color);
    gGFX_line(handle, x0, y0, x0, y1, color);
    gGFX_line(handle, x1, y0, x1, y1, color);
}

void gGFX_circle(gGFX_Handle_t *handle, uint16_t cx, uint16_t cy, uint16_t r, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    gGFX_pixel(handle, cx, cy + r, color);
    gGFX_pixel(handle, cx, cy - r, color);
    gGFX_pixel(handle, cx + r, cy, color);
    gGFX_pixel(handle, cx - r, cy, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        gGFX_pixel(handle, cx + x, cy + y, color);
        gGFX_pixel(handle, cx - x, cy + y, color);
        gGFX_pixel(handle, cx + x, cy - y, color);
        gGFX_pixel(handle, cx - x, cy - y, color);

        gGFX_pixel(handle, cx + y, cy + x, color);
        gGFX_pixel(handle, cx - y, cy + x, color);
        gGFX_pixel(handle, cx + y, cy - x, color);
        gGFX_pixel(handle, cx - y, cy - x, color);
    }
}

void gGFX_bitmap(gGFX_Handle_t *handle, uint16_t x, uint16_t y, gGFX_Bitmap_t *bitmap) {
    for (uint16_t j = 0; j < bitmap->height; j++, y++) {
        for (uint16_t i = 0; i < bitmap->width; i++) {
            gGFX_pixel(handle, x + i, y, bitmap->data[j * bitmap->width + i]);
        }
    }
}