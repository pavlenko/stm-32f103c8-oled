/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "memoryMA.h"
#include <string.h>

/******************************************************************************
 * Объявления локальных определений
 ******************************************************************************/
#define TX_BUFFER_SIZE   128
#define RX_BUFFER_SIZE   8
#define Index_Of_Command_byte 0
#define PACKAGE_SIZE     8 // Размер посылки, байт
#define COMMAND_SIZE     1
#define MIN_PACKAGE_SIZE COMMAND_SIZE
#define MAX_PACKAGE_SIZE PACKAGE_SIZE

#define UART_Command_State_Data_Pos           (7U)                               
#define UART_Command_State_Data_Msk           (0x1U << UART_Command_State_Data_Pos)           /*!< 0x80 */
#define UART_Command_State_Data               UART_Command_State_Data_Msk                     /*!< Command_State Data */

/******************************************************************************
 * Объявления локальных переменных
 ******************************************************************************/
volatile bool isUART_TxReady = true;
uint8_t transmitBuffer[TX_BUFFER_SIZE];
uint8_t txBufferOfPackage[PACKAGE_SIZE];
uint8_t txBufferHead = 0;
uint8_t txBufferTail = 0;
volatile uint8_t countOfUnsentBytes = 0;
//------------------------------------------
volatile bool isWaitingIncomingPackageSize = true;
uint8_t incomingPackageSize = 0;
uint8_t receiveBuffer[RX_BUFFER_SIZE];

/******************************************************************************
 * Объявления локальных прототипов функций
 ******************************************************************************/
void UART_Transmit(uint8_t *pData, const uint16_t size);
void UART_Receive(uint8_t *pData, const uint16_t size);
void UART_TransmitCommand(const UART_Command command);
void UART_TransmitNextPackage();
bool UART_SaveReceivedData();
bool executeTheCommand(const UART_Command command);

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = USART_BAUD_RATE;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = USART_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(USART_TX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(USART_RX_GPIO_Port, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmatx);
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
void UART_Transmit(uint8_t *pData, const uint16_t size)
{
	if (HAL_UART_Transmit_DMA(&huart1, pData, size) != HAL_OK)
	{
		Error_Handler();
	}
}

void UART_Receive(uint8_t *pData, const uint16_t size)
{
	if (HAL_UART_Receive_DMA(&huart1, pData, size) != HAL_OK)
	{
		Error_Handler();
	}
}

void UART_TransmitCommand(const UART_Command command)
{
	UART_TransmitData((uint8_t*)&command, sizeof(uint8_t));
}

// Обработчик прерывания после окончания отправки сообщения
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		if(countOfUnsentBytes == 0)
		{
			isUART_TxReady = true;
		} else
		{
			UART_TransmitNextPackage();
		}
	}
}

void UART_TransmitNextPackage()
{
	uint8_t numberOfUnsentBytes;
	if (countOfUnsentBytes <= PACKAGE_SIZE)
	{
		numberOfUnsentBytes = countOfUnsentBytes;
	} else
	{
		numberOfUnsentBytes = PACKAGE_SIZE;
	}
	for (int i = 0; i < numberOfUnsentBytes; i++)
	{
		txBufferOfPackage[i] = transmitBuffer[txBufferHead];
		txBufferHead = (uint8_t)((txBufferHead + 1) & (TX_BUFFER_SIZE - 1));
	}
	countOfUnsentBytes -= numberOfUnsentBytes;
	UART_Transmit(txBufferOfPackage, numberOfUnsentBytes);
}

bool UART_TransmitData(uint8_t *data, const uint8_t size)
{
	bool isDataBufferedTX = false;
	const uint16_t txCount = countOfUnsentBytes + size;
	if (txCount <= TX_BUFFER_SIZE)
	{
		for (int i = 0; i < size; i++)
		{
			transmitBuffer[txBufferTail] = data[i];
			txBufferTail = (uint8_t)((txBufferTail + 1) & (TX_BUFFER_SIZE - 1));
		}
		countOfUnsentBytes = (uint8_t)txCount;
		if (isUART_TxReady == true)
		{
			isUART_TxReady = false;
			UART_TransmitNextPackage();
		}
		isDataBufferedTX = true;
	}
	return isDataBufferedTX;
}

// Обработчик прерывания после окончания принятия всех заявленных байт
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == &huart1)
	{
		if (isWaitingIncomingPackageSize == true)
		{
			if (incomingPackageSize >= MIN_PACKAGE_SIZE && incomingPackageSize <= MAX_PACKAGE_SIZE)
			{
				isWaitingIncomingPackageSize = false;
				UART_Receive(receiveBuffer, incomingPackageSize);
			} else
			{
				UART_ReceiveIncomingPackageSize();
				UART_TransmitCommand(UART_COMMAND_MA_ERROR); // Ошибка в канале связи, нужно повторить отправку
			}
		} else
		{
			if ((receiveBuffer[Index_Of_Command_byte] & UART_Command_State_Data_Msk) == UART_Command_State_Data)
			{
				if (UART_SaveReceivedData() == true)
				{
					UART_ReceiveIncomingPackageSize();
					UART_TransmitCommand(UART_COMMAND_MA_OK);
				} else
				{
					UART_ReceiveIncomingPackageSize();
					UART_TransmitCommand(UART_COMMAND_MA_ERROR);
				}
			} else
			{
				if (incomingPackageSize - COMMAND_SIZE > 0)
				{
					UART_ReceiveIncomingPackageSize();
					UART_TransmitCommand(UART_COMMAND_MA_ERROR); // Неправильное сообщение (в пакете должен быть только 1 байт команды)
				} else
				{
					if (executeTheCommand(receiveBuffer[Index_Of_Command_byte]) == true)
					{
						UART_ReceiveIncomingPackageSize();
						UART_TransmitCommand(UART_COMMAND_MA_OK); // Команда исполнена
					} else
					{
						UART_ReceiveIncomingPackageSize();
						UART_TransmitCommand(UART_COMMAND_MA_ERROR); // Такой команды не существует (возможно ошибка в канале связи)
					}
				}
			}
		}
	}
}

void UART_ReceiveIncomingPackageSize()
{
	isWaitingIncomingPackageSize = true;
	UART_Receive(&incomingPackageSize, sizeof(incomingPackageSize));
}

bool UART_SaveReceivedData()
{
	const uint8_t addressOfSavingData = receiveBuffer[Index_Of_Command_byte] & ~UART_Command_State_Data;
	return writeDataToSettingsArray(receiveBuffer + COMMAND_SIZE, incomingPackageSize - COMMAND_SIZE, addressOfSavingData);
}

bool executeTheCommand(const UART_Command command)
{
	bool isCommandCompleted = true;
	switch (command)
	{
	case UART_COMMAND_MK_BALANCING_IN_ENABLE:
		setBalanceState(BalancingIn_ENABLE);
		break;
	case UART_COMMAND_MK_BALANCING_OUT_ENABLE:
		setBalanceState(BalancingOut_ENABLE);
		break;
	case UART_COMMAND_MK_BALANCING_DISABLE:
		setBalanceState(Balancing_DISABLE);
		break;
	case UART_COMMAND_MK_SEND_MEASUREMENTS:
		sendMeasurements();
		break;
	case UART_COMMAND_MK_WAIT_SETTINGS:
		setBalanceState(Balancing_DISABLE);
		break;
	case UART_COMMAND_MK_SEND_SETTINGS_CHECKSUM:
		sendSettingsChecksum();
		break;
	case UART_COMMAND_MK_UPDATE_SETTINGS:
		updateSettings();
		break;
	default:
		isCommandCompleted = false;
	}
	return isCommandCompleted;
}

void UART_SendString(char *str)
{
	UART_TransmitData((uint8_t*) str, strlen(str));
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
