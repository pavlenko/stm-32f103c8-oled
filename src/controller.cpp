#include "controller.h"

#include "stm32f1xx_hal.h"

bool buttonAReader() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_SET;
}

void buttonAOnHoldRepeated() {
    if (height < UINT8_MAX) {
        height++;
    }
}

bool buttonBReader() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_SET;
}

bool buttonCReader() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_SET;
}

void buttonCOnHoldRepeated() {
    if (height > 0) {
        height--;
    }
}

bool buttonDReader() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_SET;
}

PE_Button buttonA = PE_Button(buttonAReader);
PE_Button buttonB = PE_Button(buttonBReader);
PE_Button buttonC = PE_Button(buttonCReader);
PE_Button buttonD = PE_Button(buttonDReader);

void MX_BTN_Init() {
    buttonA.setOnHoldRepeated(buttonAOnHoldRepeated);
    buttonC.setOnHoldRepeated(buttonCOnHoldRepeated);
}