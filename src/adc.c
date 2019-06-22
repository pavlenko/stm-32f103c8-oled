#include "adc.h"

#include "main.h"

#define NUMBER_OF_ADC_CHANNELS 2
#define NUMBER_OF_MEASUREMENTS 10

volatile uint8_t  adcConversionReady = 0;
volatile uint16_t adcConversionArray[NUMBER_OF_ADC_CHANNELS];

volatile uint8_t  adcMeasurementIndex = 0;
volatile uint16_t adcMeasurementValue0;
volatile uint16_t adcMeasurementArray0[NUMBER_OF_MEASUREMENTS];
volatile uint16_t adcMeasurementValue1;
volatile uint16_t adcMeasurementArray1[NUMBER_OF_MEASUREMENTS];

ADC_HandleTypeDef adc1;
DMA_HandleTypeDef adc1DMA;

void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef chConfig;

    /** Common config */
    adc1.Instance                   = ADC1;
    adc1.Init.ScanConvMode          = ADC_SCAN_ENABLE;
    adc1.Init.ContinuousConvMode    = DISABLE;
    adc1.Init.DiscontinuousConvMode = DISABLE;
    adc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    adc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    adc1.Init.NbrOfConversion       = 2;

    if (HAL_ADC_Init(&adc1) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Regular Channel */
    chConfig.Channel      = ADC_CHANNEL_0;
    chConfig.Rank         = ADC_REGULAR_RANK_1;
    chConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;

    if (HAL_ADC_ConfigChannel(&adc1, &chConfig) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Regular Channel */
    chConfig.Channel      = ADC_CHANNEL_1;
    chConfig.Rank         = ADC_REGULAR_RANK_2;
    chConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;

    if (HAL_ADC_ConfigChannel(&adc1, &chConfig) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adc) {
    GPIO_InitTypeDef adcGPIO;

    if (adc->Instance == ADC1) {
        /* ADC1 clock enable */
        __HAL_RCC_ADC1_CLK_ENABLE();

        /* GPIOA clock enable */
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /**
         * ADC1 GPIO Configuration
         * PA0 ------> ADC1_IN0
         * PA1 ------> ADC1_IN1
         */
        adcGPIO.Pin  = GPIO_PIN_1|GPIO_PIN_0;
        adcGPIO.Mode = GPIO_MODE_ANALOG;

        HAL_GPIO_Init(GPIOA, &adcGPIO);

        /* ADC1 DMA Init */
        adc1DMA.Instance                 = DMA1_Channel1;
        adc1DMA.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        adc1DMA.Init.PeriphInc           = DMA_PINC_DISABLE;
        adc1DMA.Init.MemInc              = DMA_MINC_ENABLE;
        adc1DMA.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        adc1DMA.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
        adc1DMA.Init.Mode                = DMA_CIRCULAR;
        adc1DMA.Init.Priority            = DMA_PRIORITY_MEDIUM;

        if (HAL_DMA_Init(&adc1DMA) != HAL_OK) {
            Error_Handler();
        }

        __HAL_LINKDMA(adc, DMA_Handle, adc1DMA);
    }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adc)
{
    if (adc->Instance == ADC1) {
        /* Peripheral clock disable */
        __HAL_RCC_ADC1_CLK_DISABLE();

        /**
         * ADC1 GPIO Configuration
         * PA0 ------> ADC1_IN0
         * PA1 ------> ADC1_IN1
         */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_0);

        /* ADC1 DMA DeInit */
        HAL_DMA_DeInit(adc->DMA_Handle);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc)
{
    uint16_t tmpMeasurementValue0;
    uint16_t tmpMeasurementValue1;

    if (adc->Instance == ADC1) {
        // Handle multiple measurements for get avg result
        if (adcMeasurementIndex < NUMBER_OF_MEASUREMENTS) {
            adcMeasurementArray0[adcMeasurementIndex] = adcConversionArray[0] >> 1u;
            adcMeasurementArray1[adcMeasurementIndex] = adcConversionArray[1] >> 1u;

            adcMeasurementIndex++;

            HAL_ADC_Start_DMA(&adc1, (uint32_t*) &adcConversionArray, sizeof(adcConversionArray) / sizeof(*(adcConversionArray)));
        } else {
            tmpMeasurementValue0 = 0;
            tmpMeasurementValue1 = 0;

            for (uint8_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
                tmpMeasurementValue0 += adcMeasurementArray0[i];
                tmpMeasurementValue1 += adcMeasurementArray1[i];
            }

            adcMeasurementValue0 = tmpMeasurementValue0 / NUMBER_OF_MEASUREMENTS;
            adcMeasurementValue1 = tmpMeasurementValue1 / NUMBER_OF_MEASUREMENTS;

            adcMeasurementIndex = 0;
            adcConversionReady  = 1;
        }
    }
}

void ADC_Start()
{
    HAL_ADCEx_Calibration_Start(&adc1);
    adcConversionReady = 0;
    HAL_ADC_Start_DMA(&adc1, (uint32_t*) &adcConversionArray, sizeof(adcConversionArray) / sizeof(*(adcConversionArray)));
}

void ADC_Fetch(uint16_t *channel0, uint16_t *channel1)
{
    *channel0 = adcMeasurementValue0;
    *channel1 = adcMeasurementValue1;
}