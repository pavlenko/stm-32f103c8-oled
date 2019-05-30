#ifndef MONOCHROME_GFX_H
#define MONOCHROME_GFX_H

#include <stdint.h>

class MonochromeGFX {
private:
    uint8_t *buffer;
    uint16_t width;
    uint16_t height;
public:
    MonochromeGFX(uint16_t width, uint16_t height);
    ~MonochromeGFX();
    void clear();
};


#endif //MONOCHROME_GFX_H
