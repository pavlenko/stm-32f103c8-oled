#include "adc.h"
#include "main.h"

uint32_t result[2], buffer[2];

volatile uint32_t adc1_value0;
volatile uint32_t adc1_value1;

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
    //adc1.Init.NbrOfConversion       = 1;

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

    ADC_ChannelConfTypeDef chConfig;

    // Configure channel 0
    chConfig.Channel      = ADC_CHANNEL_0;
    chConfig.Rank         = ADC_REGULAR_RANK_1;
    chConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;

    if (HAL_ADC_ConfigChannel(&adc1, &chConfig) != HAL_OK) {
        Error_Handler();
    }

    // Configure channel 1
    chConfig.Channel      = ADC_CHANNEL_1;
    chConfig.Rank         = ADC_REGULAR_RANK_1;
    chConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;

    if (HAL_ADC_ConfigChannel(&adc1, &chConfig) != HAL_OK) {
        Error_Handler();
    }

    // Configure ADC GPIO
    GPIO_InitTypeDef gpioADC;

    // Enable ADC & GPIO clock
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /**
     * ADC1 GPIO Configuration
     * PA0 ------> ADC1_IN0
     * PA1 ------> ADC1_IN1
     */
    gpioADC.Pin  = GPIO_PIN_0 | GPIO_PIN_1;
    gpioADC.Mode = GPIO_MODE_ANALOG;

    HAL_GPIO_Init(GPIOA, &gpioADC);

    //TODO
    /*__HAL_RCC_DMA2_CLK_ENABLE();

    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);*/

    // Start conversion in DMA mode
    HAL_ADC_Start_DMA(&adc1, buffer, 2);
}

void ADC_IRQHandler() {
    HAL_ADC_IRQHandler(&adc1);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc) {
    if (adc->Instance == ADC1) {
        for (uint8_t i = 0; i < 2; i++) {
            result[i] = buffer[i];
        }
    }
}