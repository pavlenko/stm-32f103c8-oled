#include "MonochromeGFX.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

MonochromeGFX::MonochromeGFX(uint16_t width, uint16_t height): width(width), height(height) {
    buffer = (uint8_t *) malloc(width * ((height + 7) / 8));
}

MonochromeGFX::~MonochromeGFX() {
    if (buffer) {
        free(buffer);
        buffer = nullptr;
    }
}

void MonochromeGFX::clear() {
    memset(buffer, 0x00, width * ((height + 7) / 8));
}
