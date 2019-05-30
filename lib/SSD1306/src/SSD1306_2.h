#ifndef __SSD1306_H
#define __SSD1306_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define SSD1306_REG_COMMAND 0x00
#define SSD1306_REG_DATA    0x40

#define SSD1306_SET_MEM_ADDR_MODE   0x20
#define SSD1306_SET_DISPLAY_OFF     0xAE
#define SSD1306_SET_DISPLAY_ON      0xAF
#define SSD1306_SET_CONTRAST_CONTROL 0x81
#define SSD1306_ENTIRE_DISPLAY_ON_0 0xA4
#define SSD1306_ENTIRE_DISPLAY_ON_1 0xA5
#define SSD1306_INVERSE_DISPLAY_0   0xA6
#define SSD1306_INVERSE_DISPLAY_1   0xA7
#define SSD1306_SET_SEGMENT_REMAP_OFF 0xA0
#define SSD1306_SET_SEGMENT_REMAP_ON  0xA1
#define SSD1306_SET_MULTIPLEX_RATIO   0xA8
#define SSD1306_SET_COM_OUT_SCAN_DIR_NORMAL   0xC0
#define SSD1306_SET_COM_OUT_SCAN_DIR_REMAPPED 0xC8
#define SSD1306_SET_DISPLAY_OFFSET         0xD3
#define SSD1306_SET_COM_PINS_CONFIGURATION 0xDA
#define SSD1306_SET_DISPLAY_CLOCK_DIVIDER  0xD5
#define SSD1306_SET_PRECHARGE_PERIOD       0xD9
#define SSD1306_SET_VCOMH_DESELECT_LEVEL   0xDB
#define SSD1306_NOP                        0xE3

#define SSD1306_SET_PAGE_START_ADDRESS(addr) (0xB0 | (0x07 & addr))

#define SSD1306_VCOMH_DESELECT_LEVEL_065 0x00
#define SSD1306_VCOMH_DESELECT_LEVEL_077 0x20
#define SSD1306_VCOMH_DESELECT_LEVEL_083 0x30

typedef struct SSD1306_s {
    void (*writeByte)(uint8_t reg, uint8_t byte);
    void (*writeData)(uint8_t reg, uint8_t *data, uint16_t size);
} SSD1306_t;

void SSD1306_initialize(SSD1306_t *instance);

#ifdef __cplusplus
}
#endif

#endif //__SSD1306_H
