#include "ssd1306.h"

#include "i2c.h"
#include "main.h"

void PE_SSD1306_reset() {};

void PE_SSD1306_write(uint8_t reg, const uint8_t *data, uint16_t size) {
    if (HAL_I2C_Mem_Write(&i2c2, PE_SSD1306_I2C_ADDRESS_8BIT_A, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t *) data, sizeof(uint8_t) * size, 1000) != HAL_OK) {
        Error_Handler();
    }
}

PE_SSD1306 ssd1306_api = PE_SSD1306(PE_SSD1306_VCC_INTERNAL, 128, 64, PE_SSD1306_reset, PE_SSD1306_write);
PE_mGFX ssd1306_gfx    = PE_mGFX(128, 64);