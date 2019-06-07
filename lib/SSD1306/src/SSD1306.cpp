#include "SSD1306.h"

PE::SSD1306::SSD1306(uint8_t width, uint8_t height, SSD1306_reset reset, SSD1306_write write) {
    _width  = width;
    _height = height;
    _reset  = reset;
    _write  = write;
}

void PE::SSD1306::initialize(PE_SSD1306_VCC_t vccType) {
    _reset();

    uint8_t muxRatio   = _height - 1;
    uint8_t chargePump = (vccType == PE_SSD1306_VCC_EXTERNAL) ? 0x10 : 0x14;
    uint8_t preCharge  = (vccType == PE_SSD1306_VCC_EXTERNAL) ? 0x22 : 0xF1;

    static const uint8_t init1[] = {
        PE_SSD1306_DISPLAY_OFF,                 // 0xAE
        PE_SSD1306_DISPLAY_CLOCK_DIVIDER, 0x80, // 0xD5, the suggested value 0x80
        PE_SSD1306_MULTIPLEX_RATIO, muxRatio,   // 0xA8, value
        PE_SSD1306_DISPLAY_OFFSET, 0x00,        // 0xD3, no offset
        PE_SSD1306_START_LINE | 0x00,           // 0x40 | val
        PE_SSD1306_CHARGE_PUMP, chargePump,     // 0x8D, val
        PE_SSD1306_MEMORY_MODE, 0x00,           // 0x20, val (act like ks0108)
        PE_SSD1306_SEGMENT_REMAP_ON,            // 0xA0
        PE_SSD1306_COM_SCAN_DECREMENT,          // 0xC8
    };

    _write(SSD1306_WRITE_COMMAND, init1, sizeof(init1));

    if (96 == _width && 16 == _height) {
        uint8_t contrast = (vccType == PE_SSD1306_VCC_EXTERNAL) ? 0x10 : 0xAF;

        static const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x02,      // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        _write(SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    } if (128 == _width && 32 == _height) {
        uint8_t contrast = 0x8F;

        static const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x02,      // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        _write(SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    } if (128 == _width && 64 == _height) {
        uint8_t contrast = (vccType == PE_SSD1306_VCC_EXTERNAL) ? 0x9F : 0xCF;

        static const uint8_t init2[] = {
            PE_SSD1306_COM_PINS_CONFIG, 0x12,      // 0xDA, val
            PE_SSD1306_CONTRAST_CONTROL, contrast, // 0x81
        };

        _write(SSD1306_WRITE_COMMAND, init2, sizeof(init2));
    }

    static const uint8_t init3[] = {
        PE_SSD1306_PRE_CHARGE_PERIOD, preCharge, // 0xD9
        PE_SSD1306_VCOMH_DESELECT, 0x40,         // 0xDB, val
        PE_SSD1306_ALL_ON_DISABLE,               // 0xA4
        PE_SSD1306_INVERSE_DISABLE,              // 0xA6
        PE_SSD1306_SCROLL_DISABLE,               // 0x2E
        PE_SSD1306_DISPLAY_ON,
    };

    _write(SSD1306_WRITE_COMMAND, init3, sizeof(init3));
}

void PE::SSD1306::setEnabled(bool value) {
    static const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_DISPLAY_ON : PE_SSD1306_DISPLAY_OFF),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setInverse(bool value) {
    static const uint8_t data[] = {
            (uint8_t) (value ? PE_SSD1306_INVERSE_ENABLE : PE_SSD1306_INVERSE_DISABLE),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setContrast(uint8_t contrast) {
    static const uint8_t data[] = {
        PE_SSD1306_CONTRAST_CONTROL,
        contrast,
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setFlipX(bool value) {
    static const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_SEGMENT_REMAP_OFF : PE_SSD1306_SEGMENT_REMAP_ON),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setFlipY(bool value) {
    static const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_COM_SCAN_INCREMENT : PE_SSD1306_COM_SCAN_DECREMENT),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setAllEnabled(bool value) {
    static const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_ALL_ON_ENABLE : PE_SSD1306_ALL_ON_DISABLE),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::setScrollEnabled(bool value) {
    static const uint8_t data[] = {
        (uint8_t) (value ? PE_SSD1306_SCROLL_ENABLE : PE_SSD1306_SCROLL_DISABLE),
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
}

void PE::SSD1306::update(uint8_t *buffer, uint16_t size) {
    static const uint8_t data[] = {
        PE_SSD1306_PAGE_START_ADDRESS,
        PE_SSD1306_COLUMN_L_ADDRESS,
        PE_SSD1306_COLUMN_H_ADDRESS,
    };

    _write(SSD1306_WRITE_COMMAND, data, sizeof(data));
    _write(SSD1306_WRITE_DATA, buffer, size);
}
