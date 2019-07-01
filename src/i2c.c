#include "i2c.h"

#include "main.h"

I2C_HandleTypeDef i2c1;
I2C_HandleTypeDef i2c2;

void MX_I2C1_Init(void)
{
    i2c1.Instance             = I2C1;
    i2c1.Init.ClockSpeed      = 400000;
    i2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    i2c1.Init.OwnAddress1     = 0;
    i2c1.Init.OwnAddress2     = 0;
    i2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    i2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&i2c1) != HAL_OK) {
        Error_Handler();
    }
}

void MX_I2C2_Init(void)
{
    i2c2.Instance             = I2C2;
    i2c2.Init.ClockSpeed      = 400000;
    i2c2.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    i2c2.Init.OwnAddress1     = 0;
    i2c2.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    i2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c2.Init.OwnAddress2     = 0;
    i2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c2.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&i2c2);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2c)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (i2c->Instance == I2C1) {
        /* GPIOB clock enable */
        __HAL_RCC_GPIOB_CLK_ENABLE();

        /* I2C1 clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();

        /**
         * I2C1 GPIO Configuration
         * PB6 ------> I2C1_SCL
         * PB7 ------> I2C1_SDA
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* I2C1 interrupt Init */
//        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 1, 1);
//        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
//
//        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 1, 0);
//        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
    }

    if (i2c->Instance == I2C2) {
        /**
         * I2C2 GPIO Configuration
         * PB10 ------> I2C2_SCL
         * PB11 ------> I2C2_SDA
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_10|GPIO_PIN_11;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();
    }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2c)
{
    if (i2c->Instance == I2C1) {
        /* I2C2 clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**
         * I2C1 GPIO Configuration
         * PB6 ------> I2C1_SCL
         * PB7 ------> I2C1_SDA
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);

        /* I2C1 interrupt Deinit */
//        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
//        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
    }

    if (i2c->Instance == I2C2) {
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**
         * I2C2 GPIO Configuration
         * PB10 ------> I2C2_SCL
         * PB11 ------> I2C2_SDA
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);
    }
}