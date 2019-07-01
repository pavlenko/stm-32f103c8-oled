#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef i2c1;
extern I2C_HandleTypeDef i2c2;

void MX_I2C1_Init(void);
void MX_I2C2_Init(void);

#ifdef __cplusplus
}
#endif

#endif //I2C_H
