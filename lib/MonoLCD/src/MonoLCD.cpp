#include "MonoLCD.h"

MonoLCD::MonoLCD(uint16_t width, uint16_t height, MonoLCD_ADAPTER_t adapter) {
    this->_width  = width;
    this->_height = height;

    uint8_t buffer[width * height / 8];

    this->_buffer  = buffer;
    this->_adapter = adapter;
}

//TODO pass some info to adapter (x,y,width,height,...)
void MonoLCD::update() {
    for (int i = 0; i < this->_height / 8; ++i) {
        this->_adapter(&this->_buffer[this->_width * i], this->_width);
    }
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

void MonoLCD::bitmap(uint16_t x, uint16_t y, MonoLCD_BITMAP_t *bitmap, MonoLCD_COLOR_t color) {
    uint16_t width = (bitmap->width + 7) / 8;
    uint8_t byte   = 0;

    for (uint16_t j = 0; j < bitmap->height; j++, y++) {
        for (uint16_t i = 0; i < bitmap->width; i++) {
            if (i & 7u) {
                byte <<= 1u;
            } else {
                byte = bitmap->data[j * width + i / 8];
            }

            if (byte & 0x80u) this->pixel(x + i, y, color);
        }
    }
}

void MonoLCD::symbol(uint16_t x, uint16_t y, char symbol, MonoLCD_FONT_t *font, MonoLCD_COLOR_t color) {
    uint16_t i, j, line;

    for (i = 0; i < font->height; i++) {
        line = font->data[(symbol - 32) * font->height + i];

        for (j = 0; j < font->width; j++) {
            if (line & 0x8000u) {
                this->pixel(x + j, y + i, color);
            }

            line <<= 1u;
        }
    }
}

void MonoLCD::string(uint16_t x, uint16_t y, const char *string, MonoLCD_FONT_t *font, MonoLCD_COLOR_t color) {
    while (*string++) {
        this->symbol(x, y, *string, font, color);
    }
}
