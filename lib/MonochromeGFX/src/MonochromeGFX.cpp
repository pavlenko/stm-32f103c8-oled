#include "MonochromeGFX.h"

#include <stdio.h>
#include <malloc.h>

MonochromeGFX::MonochromeGFX(uint16_t width, uint16_t height): width(width), height(height) {
    buffer = (uint8_t *) malloc(width * ((height + 7) / 8));
}

MonochromeGFX::~MonochromeGFX() {
    if (buffer) {
        free(buffer);
        buffer = nullptr;
    }
}
