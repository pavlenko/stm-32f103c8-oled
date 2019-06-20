#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>

extern ADC_HandleTypeDef adc1;
extern DMA_HandleTypeDef adc1DMA;

void MX_ADC1_Init(void);

/**
 * Start ADC measurements
 */
void ADC_Start();

/**
 * Fetch result to passed pointers
 *
 * @param channel0
 * @param channel1
 */
void ADC_Fetch(uint16_t *channel0, uint16_t *channel1);

#ifdef __cplusplus
}
#endif

#endif //__ADC_H
