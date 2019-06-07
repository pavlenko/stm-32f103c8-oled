#ifndef PE_SSD1306_H
#define PE_SSD1306_H

/**
 * SSD1306 based displays API, except connection transport & graphics
 */
#include <stdint.h>

#define SSD1306_WRITE_COMMAND 0x00
#define SSD1306_WRITE_DATA    0x40

#define PE_SSD1306_MEMORY_MODE           0x20
#define PE_SSD1306_SCROLL_DISABLE        0x2E
#define PE_SSD1306_SCROLL_ENABLE         0x2F
#define PE_SSD1306_START_LINE            0x40
#define PE_SSD1306_CONTRAST_CONTROL      0x81
#define PE_SSD1306_CHARGE_PUMP           0x8D
#define PE_SSD1306_SEGMENT_REMAP_OFF     0xA0
#define PE_SSD1306_SEGMENT_REMAP_ON      0xA1
#define PE_SSD1306_ALL_ON_DISABLE        0xA4
#define PE_SSD1306_ALL_ON_ENABLE         0xA5
#define PE_SSD1306_INVERSE_DISABLE       0xA6
#define PE_SSD1306_INVERSE_ENABLE        0xA7
#define PE_SSD1306_MULTIPLEX_RATIO       0xA8
#define PE_SSD1306_DISPLAY_OFF           0xAE
#define PE_SSD1306_DISPLAY_ON            0xAF
#define PE_SSD1306_COM_SCAN_INCREMENT    0xC0
#define PE_SSD1306_COM_SCAN_DECREMENT    0xC8
#define PE_SSD1306_DISPLAY_OFFSET        0xD3
#define PE_SSD1306_DISPLAY_CLOCK_DIVIDER 0xD5
#define PE_SSD1306_PRE_CHARGE_PERIOD     0xD9
#define PE_SSD1306_COM_PINS_CONFIG       0xDA
#define PE_SSD1306_SET_VCOMH_DESELECT    0xDB

typedef enum {
    PE_SSD1306_VCC_EXTERNAL = 0x01,
    PE_SSD1306_VCC_INTERNAL = 0x02,
} PE_SSD1306_VCC_t;

namespace PE {
    typedef void (*SSD1306_reset) ();

    typedef void (*SSD1306_write) (uint8_t reg, const uint8_t *data, uint8_t size);

    class SSD1306 {
        uint8_t _width;
        uint8_t _height;
        SSD1306_reset _reset{};
        SSD1306_write _write{};
    public:
        /**
         * @param width  Display width in pixels
         * @param height Display height in pixels
         * @param reset  Reset logic adapter
         * @param write  Write logic adapter
         */
        SSD1306(uint8_t width, uint8_t height, SSD1306_reset reset, SSD1306_write write);

        /**
         * @param vccType
         */
        void initialize(PE_SSD1306_VCC_t vccType);

        /**
         * Set display enabled / disabled
         *
         * @param value
         */
        void setEnabled(bool value);

        /**
         * Inverse display pixels state (do not affect real memory data)
         *
         * @param value
         */
        void setInverse(bool value);

        /**
         * Set display contrast
         *
         * @param contrast
         */
        void setContrast(uint8_t contrast);

        /**
         * Set display flipped horizontally
         *
         * @param value
         */
        void setFlipHorizontal(bool value);

        /**
         * Set display flipped vertically
         *
         * @param value
         */
        void setFlipVertical(bool value);
    };
}


#endif //PE_SSD1306_H
