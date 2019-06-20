/**
  ******************************************************************************
  * File Name          : ADC.h
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adc_H
#define __adc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */
/******************************************************************************
 * ќбъ€влени€ глобальных определений
 ******************************************************************************/
#define ADC_U_REF 3300.0 // mV
#define ADC_MAX_BIT 4095 // bit
#define ADC_U_ACC_R21 1000 // Ohm  <--[_R21_]--u--[_R24_]--|
#define ADC_U_ACC_R24 3300 // Ohm
#define ADC_U_ACC_K ((ADC_U_REF * (ADC_U_ACC_R24 + ADC_U_ACC_R21)) / (ADC_MAX_BIT * ADC_U_ACC_R24))
#define ADC_I_RSH 0.002 // Ohm --[~~~]--
#define ADC_I_R12 39000.0 // Ohm (out)--[_R12_]--(in-)
#define ADC_I_R14 1000 // Ohm  (in-)--[_R14_]--|
#define ADC_I_K ((ADC_U_REF * ADC_I_R14) / (ADC_MAX_BIT * ADC_I_R12 * ADC_I_RSH))
#define ADC_I_R6 82000.0 // Ohm  <--[_R6_]--(in+)
#define ADC_I_ZERO_BIT ((ADC_MAX_BIT * ADC_I_R12) / ADC_I_R6) // I = (ADC_BIT - ADC_I_ZERO_BIT) * ADC_I_K;
/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void startADCConversion();
bool getADCData(uint16_t *channel0, uint16_t *channel7);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ adc_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
