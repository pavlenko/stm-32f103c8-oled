#include "gGFX.h"

#include <malloc.h>
#include <string.h>

void gGFX_initialize(gGFX_Buffer_t *buffer) {
    buffer->data = (uint8_t *) malloc(buffer->width * buffer->height);
}

void gGFX_clear(gGFX_Buffer_t *buffer) {
    memset(buffer, 0, buffer->width * buffer->height);
}
