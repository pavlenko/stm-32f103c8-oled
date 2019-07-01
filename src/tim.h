#ifndef TIM_H
#define TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f1xx_hal.h>

extern TIM_HandleTypeDef tim1;

void MX_TIM4_Init(void);

#ifdef __cplusplus
}
#endif

#endif //TIM_H
