#include "led.h"

#include "stm32f1xx_hal.h"

void MX_LED_Init() {
    // Enable port clock, must be first
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef gpio;

    gpio.Pin   = GPIO_PIN_13;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    // Init led pin
    HAL_GPIO_Init(GPIOC, &gpio);

    // Set led off
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    //__HAL_RCC_GPIOC_CLK_ENABLE();
}

void LED(LED_State_t state) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, state == LED_ON ? GPIO_PIN_RESET : GPIO_PIN_SET);
}