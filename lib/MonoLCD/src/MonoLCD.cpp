#include "MonoLCD.h"

MonoLCD::MonoLCD(uint16_t width, uint16_t height) {
    this->_width  = width;
    this->_height = height;

    uint8_t buffer[width * height / 8];

    this->_buffer = buffer;
}

void MonoLCD::pixel(uint16_t x, uint16_t y, MonoLCD_COLOR_t color) {
    if (x >= this->_width || y >= this->_height) return;

    if (color == MonoLCD_COLOR_WHITE) {
        this->_buffer[x + (y / 8) * this->_width] |= 1u << (y % 8u);
    } else {
        this->_buffer[x + (y / 8) * this->_width] &= ~(1u << (y % 8u));
    }
}

void MonoLCD::line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color) {
    int16_t dx  = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    int16_t dy  = (y0 < y1) ? (y1 - y0) : (y0 - y1);
    int16_t sx  = (x0 < x1) ? 1 : -1;
    int16_t sy  = (y0 < y1) ? 1 : -1;
    int16_t err = ((dx > dy) ? dx : -dy) / 2;

    if (dx == 0) {
        do {
            this->pixel(x0, y0, color);
            y0 += dy;
        } while (y0 != y1);

        return;
    }

    if (dy == 0) {
        do {
            this->pixel(x0, y0, color);
            x0 += dx;
        } while (x0 != x1);

        return;
    }

    do {
        this->pixel(x0, y0, color);

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

void MonoLCD::rect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, MonoLCD_COLOR_t color, bool fill) {
    uint16_t i;

    this->line(x0, y0, x1, y0, color);
    this->line(x0, y1, x1, y1, color);
    this->line(x0, y0, x0, y1, color);
    this->line(x1, y0, x1, y1, color);

    if (fill) {
        for (i = y0 + 1; i < y1 - 1; i++) {
            this->line(x0, i, x1, i, color);
        }
    }
}

void MonoLCD::circle(uint16_t cx, uint16_t cy, uint16_t r, MonoLCD_COLOR_t color, bool fill) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    this->pixel(cx, cy + r, color);
    this->pixel(cx, cy - r, color);
    this->pixel(cx + r, cy, color);
    this->pixel(cx - r, cy, color);

    if (fill) {
        this->line(cx - r, cy, cx + r, cy, color);

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            this->line(cx - x, cy + y, cx + x, cy + y, color);
            this->line(cx + x, cy - y, cx - x, cy - y, color);

            this->line(cx + y, cy + x, cx - y, cy + x, color);
            this->line(cx + y, cy - x, cx - y, cy - x, color);
        }
    } else {
        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            this->pixel(cx + x, cy + y, color);
            this->pixel(cx - x, cy + y, color);
            this->pixel(cx + x, cy - y, color);
            this->pixel(cx - x, cy - y, color);

            this->pixel(cx + y, cy + x, color);
            this->pixel(cx - y, cy + x, color);
            this->pixel(cx + y, cy - x, color);
            this->pixel(cx - y, cy - x, color);
        }
    }
}
