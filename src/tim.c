#include "tim.h"

TIM_HandleTypeDef tim4;

TIM_OC_InitTypeDef sConfigOC;

void MX_TIM4_Init() {
    TIM_MasterConfigTypeDef sMasterConfig;

    tim4.Instance           = TIM4;
    tim4.Init.Prescaler     = (uint32_t) (SystemCoreClock / 1000000) - 1;
    tim4.Init.CounterMode   = TIM_COUNTERMODE_UP;
    tim4.Init.Period        = 20000;
    tim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(&tim4);

    sConfigOC.OCMode     = TIM_OCMODE_PWM1;
    sConfigOC.Pulse      = 1500;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&tim4, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_ConfigChannel(&tim4, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_ConfigChannel(&tim4, &sConfigOC, TIM_CHANNEL_3);
    HAL_TIM_PWM_ConfigChannel(&tim4, &sConfigOC, TIM_CHANNEL_4);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_ENABLE;

    HAL_TIMEx_MasterConfigSynchronization(&tim4, &sMasterConfig);

    HAL_TIM_PWM_Start(&tim4, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&tim4, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&tim4, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&tim4, TIM_CHANNEL_4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* timPWM)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    if (timPWM->Instance == TIM4) {
        /**
         * TIM4 GPIO Configuration
         * PB6 --> TIM4_CH1
         * PB7 --> TIM4_CH1
         * PB8 --> TIM4_CH1
         * PB9 --> TIM4_CH1
         */
        GPIO_InitStruct.Pin   = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
        GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
        //GPIO_InitStruct.Pull  = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        /* Peripheral interrupt init */
        HAL_NVIC_SetPriority(TIM4_IRQn, 2, 2);
        HAL_NVIC_EnableIRQ(TIM4_IRQn);

        /* Peripheral clock enable */
        __HAL_RCC_TIM4_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* timPWM)
{
    if (timPWM->Instance == TIM4) {
        /* Peripheral clock disable */
        __HAL_RCC_TIM4_CLK_DISABLE();

        /**
         * TIM4 GPIO Configuration
         * PB6 --> TIM4_CH1
         * PB7 --> TIM4_CH1
         * PB8 --> TIM4_CH1
         * PB9 --> TIM4_CH1
         */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

        /* Peripheral interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM4_IRQn);
    }
}

/*
void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&tim4);
}*/
