#ifndef TIM_H
#define TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>

extern TIM_HandleTypeDef tim4;

void MX_TIM2_Init(void);

#ifdef __cplusplus
}
#endif

#endif //TIM_H
