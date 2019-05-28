#include "SSD1306.h"

void SSD1306_initialize(SSD1306_t *instance)
{
    /* Init LCD */
    instance->writeByte(SSD1306_SET_DISPLAY_OFF);
    instance->writeByte(SSD1306_SET_MEM_ADDR_MODE);
    instance->writeByte(0x10);
    instance->writeByte(SSD1306_SET_PAGE_START_ADDRESS(0)); //Set Page Start Address for Page Addressing Mode,0-7
    instance->writeByte(SSD1306_SET_COM_OUT_SCAN_DIR_REMAPPED);
    instance->writeByte(0x00); //---set low column address
    instance->writeByte(0x10); //---set high column address
    instance->writeByte(0x40); //--set start line address
    instance->writeByte(SSD1306_SET_CONTRAST_CONTROL);
    instance->writeByte(0xFF); // SSD1306_SET_CONTRAST_CONTROL value
    instance->writeByte(SSD1306_SET_SEGMENT_REMAP_ON);
    instance->writeByte(SSD1306_INVERSE_DISPLAY_0);
    instance->writeByte(SSD1306_SET_MULTIPLEX_RATIO);
    instance->writeByte(0x3F); // SSD1306_SET_MULTIPLEX_RATIO value
    instance->writeByte(SSD1306_ENTIRE_DISPLAY_ON_0);
    instance->writeByte(SSD1306_SET_DISPLAY_OFFSET);
    instance->writeByte(0x00); // SSD1306_SET_DISPLAY_OFFSET value
    instance->writeByte(SSD1306_SET_DISPLAY_CLOCK_DIVIDER);
    instance->writeByte(0xF0); // SSD1306_SET_DISPLAY_CLOCK_DIVIDER value
    instance->writeByte(SSD1306_SET_PRECHARGE_PERIOD);
    instance->writeByte(0x22); // SSD1306_SET_PRECHARGE_PERIOD value
    instance->writeByte(SSD1306_SET_COM_PINS_CONFIGURATION);
    instance->writeByte(0x12); // SSD1306_SET_COM_PINS_CONFIGURATION value
    instance->writeByte(SSD1306_SET_VCOMH_DESELECT_LEVEL);
    instance->writeByte(0x20); // SSD1306_SET_VCOMH_DESELECT_LEVEL value - 0x20,0.77xVcc
    instance->writeByte(0x8D); //--set DC-DC enable
    instance->writeByte(0x14); //
    instance->writeByte(SSD1306_SET_DISPLAY_ON);
}
