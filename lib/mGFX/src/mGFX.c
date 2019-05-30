#include "mGFX.h"

#include <malloc.h>
#include <string.h>

void mGFX_initialize(mGFX_Buffer_t *buffer) {
    buffer->data = (uint8_t *) malloc(buffer->width * ((buffer->height + 7) / 8));
}

void mGFX_clear(mGFX_Buffer_t *buffer) {
    memset(buffer, 0, buffer->width * ((buffer->height + 7) / 8));
}
