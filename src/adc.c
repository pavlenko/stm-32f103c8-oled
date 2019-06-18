#include "adc.h"
#include "main.h"

volatile uint32_t adc1_value;

ADC_HandleTypeDef adc1;

uint32_t example()
{
    HAL_ADC_Start(&adc1);

    HAL_ADC_PollForConversion(&adc1, 100);

    uint32_t adcResult = HAL_ADC_GetValue(&adc1);

    HAL_ADC_Stop(&adc1);

    return adcResult;
}

void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig;

    // Common config
    adc1.Instance                   = ADC1;
    adc1.Init.ScanConvMode          = ADC_SCAN_DISABLE;
    adc1.Init.ContinuousConvMode    = ENABLE;
    adc1.Init.DiscontinuousConvMode = DISABLE;
    adc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    adc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    adc1.Init.NbrOfConversion       = 1;

    if (HAL_ADC_Init(&adc1) != HAL_OK) {
        Error_Handler();
    }

    /**Configure Regular Channel
    */
    sConfig.Channel      = ADC_CHANNEL_0;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;

    if (HAL_ADC_ConfigChannel(&adc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *adc) {
    GPIO_InitTypeDef GPIO_InitStruct;

    if (adc->Instance == ADC1) {
        /* ADC1 clock enable */
        __HAL_RCC_ADC1_CLK_ENABLE();

        /**
         * ADC1 GPIO Configuration
         * PA0-WKUP ------> ADC1_IN0
         */
        GPIO_InitStruct.Pin  = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *adc) {
    if (adc->Instance == ADC1) {
        /* Peripheral clock disable */
        __HAL_RCC_ADC1_CLK_DISABLE();

        /**
         * ADC1 GPIO Configuration
         * PA0-WKUP ------> ADC1_IN0
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc) {
    if (adc->Instance == ADC1) {
        adc1_value = HAL_ADC_GetValue(adc);

        // Re-Start ADC1 under Interrupt, this is necessary because we don'use the Continuos Conversion Mode
        HAL_ADC_Start_IT(adc);
    }
}