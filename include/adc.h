#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef adc1;

void MX_ADC1_Init(void);

#ifdef __cplusplus
}
#endif

#endif //__ADC_H
