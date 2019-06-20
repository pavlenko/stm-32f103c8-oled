/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
uint32_t CAN_GetFreeMailBox();
/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 9;
  hcan.Init.Mode = CAN_MODE_SILENT_LOOPBACK;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = ENABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = ENABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    GPIO_InitStruct.Pin = CAN_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(CAN_RX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = CAN_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(CAN_TX_GPIO_Port, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */
	  
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
  
    /**CAN GPIO Configuration    
    PA11     ------> CAN_RX
    PA12     ------> CAN_TX 
    */
    HAL_GPIO_DeInit(GPIOA, CAN_RX_Pin|CAN_TX_Pin);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
/**
  * @brief  Configure an inbox filter
  * @note   Filter by sender id list
  * @retval None
  */
void CAN_ConfigureFilter()
{
	CAN_FilterTypeDef canFilterConfig;
	canFilterConfig.FilterBank = 0;
	canFilterConfig.SlaveStartFilterBank = 0;
	canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
	canFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	canFilterConfig.FilterIdHigh		= CAN_CMD_Test_Send << 5;
	canFilterConfig.FilterIdLow			= CAN_CMD_Test_Ok << 5;
	canFilterConfig.FilterMaskIdHigh	= 0x0000 << 5;
	canFilterConfig.FilterMaskIdLow		= 0x0000 << 5;
	canFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
	if (HAL_CAN_ConfigFilter(&hcan, &canFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief  Sending a test message to the bus
  * @retval None
  */
void CAN_Send_Test()
{
	if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0)
	{
		uint8_t txData[] = { 0x33, 0x34, 0x35 };

		CAN_TxHeaderTypeDef txMessage;
		txMessage.StdId = CAN_CMD_Test_Send;
		txMessage.ExtId = 0x00;
		txMessage.IDE = CAN_ID_STD;
		txMessage.RTR = CAN_RTR_DATA;
		txMessage.DLC = COUNTOF(txData);
		txMessage.TransmitGlobalTime = DISABLE;

		uint32_t canTxMailBox = CAN_GetFreeMailBox();

		if (HAL_CAN_AddTxMessage(&hcan, &txMessage, txData, &canTxMailBox) != HAL_OK)
		{
			Error_Handler();
		}
	}
}

/**
  * @brief  Get free mailbox id
  * @note   Returns 0 if there are no free mailboxes
  * @retval Free mailbox id
  */
uint32_t CAN_GetFreeMailBox()
{
	uint32_t canTxMailBox = 0;
	if (HAL_CAN_IsTxMessagePending(&hcan, CAN_TX_MAILBOX0) == 0)
	{
		canTxMailBox = CAN_TX_MAILBOX0;
	} else if (HAL_CAN_IsTxMessagePending(&hcan, CAN_TX_MAILBOX1) == 0)
	{
		canTxMailBox = CAN_TX_MAILBOX1;
	} else if (HAL_CAN_IsTxMessagePending(&hcan, CAN_TX_MAILBOX2) == 0)
	{
		canTxMailBox = CAN_TX_MAILBOX2;
	}
	return canTxMailBox;
}

/**
  * @brief  Send confirmation of receipt of the test command to the bus
  * @note   Send only the command without data
  * @retval None
  */
void CAN_Send_Ok()
{
	if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0)
	{
		CAN_TxHeaderTypeDef txMessage;
		txMessage.StdId = CAN_CMD_Test_Ok;
		txMessage.ExtId = 0x00;
		txMessage.IDE = CAN_ID_STD;
		txMessage.RTR = CAN_RTR_DATA;
		txMessage.DLC = 0;
		uint8_t freeData = 0;

		uint32_t canTxMailBox = CAN_GetFreeMailBox();
		if (HAL_CAN_AddTxMessage(&hcan, &txMessage, &freeData, &canTxMailBox) != HAL_OK)
		{
			Error_Handler();
		}
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
