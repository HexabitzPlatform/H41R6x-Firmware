/*
 BitzOS (BOS) V0.2.7 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H41R6_uart.c
 Description   : Source Code provides configuration for USART instances.

 */

/* Includes ------------------------------------------------------------------*/
#include "H41R6_uart.h"


#ifndef __N
uint16_t arrayPortsDir[MaxNumOfModules]; /* Array ports directions */
#else
uint16_t arrayPortsDir[__N ];
#endif

/* USART1 init function */

void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = DEF_ARRAY_BAUDRATE;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);
}

/* USART2 init function */

void MX_USART2_UART_Init(void) {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = DEF_ARRAY_BAUDRATE;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);
}
/* USART3 init function */
void MX_USART3_UART_Init(void) {
	huart3.Instance = USART3;
	huart3.Init.BaudRate = DEF_ARRAY_BAUDRATE;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart3);

}
/* UART4 init function */
void MX_UART4_UART_Init(void) {

	huart4.Instance = UART4;
	huart4.Init.BaudRate = DEF_ARRAY_BAUDRATE;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart4);

}
/* UART5 init function */
void MX_UART5_UART_Init(void) {

	huart5.Instance = UART5;
	huart5.Init.BaudRate = DEF_ARRAY_BAUDRATE;
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.Mode = UART_MODE_TX_RX;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart5);

}

/* USART6 init function */

void MX_USART6_UART_Init(void) {

	huart6.Instance = USART6;
	huart6.Init.BaudRate = DEF_ARRAY_BAUDRATE;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart6);

}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	if (uartHandle->Instance == USART1) {
		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		 PA9     ------> USART1_TX
		 PA10     ------> USART1_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}

	else if (uartHandle->Instance == USART2) {
		/* USART2 clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
		 PA2     ------> USART2_TX
		 PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	} else if (uartHandle->Instance == USART3) {
		/* USART3 clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**USART3 GPIO Configuration
		 PB10     ------> USART3_TX
		 PB11     ------> USART3_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	} else if (uartHandle->Instance == UART4) {
		/* UART4 clock enable */
		__HAL_RCC_UART4_CLK_ENABLE();
		/* DMA controller clock enable */
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**UART4 GPIO Configuration
		 PA0/WKUP     ------> UART4_TX
		 PA1     ------> UART4_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	} else if (uartHandle->Instance == UART5) {
		/* UART5 clock enable */
		__HAL_RCC_UART5_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**UART5 GPIO Configuration
		 PC12     ------> UART5_TX
		 PD2     ------> UART5_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}

	else if (uartHandle->Instance == USART6) {
		/* USER CODE BEGIN USART6_MspInit 0 */

		/* USER CODE END USART6_MspInit 0 */
		/* USART6 clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();
		/**USART6 GPIO Configuration
		 PC6     ------> USART6_TX
		 PC7     ------> USART6_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

	if (uartHandle->Instance == UART4) {
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
		 PA0/WKUP     ------> UART4_TX
		 PA1     ------> UART4_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);

		/* UART4 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN UART4_MspDeInit 1 */

		/* USER CODE END UART4_MspDeInit 1 */
	} else if (uartHandle->Instance == UART5) {
		/* USER CODE BEGIN UART5_MspDeInit 0 */

		/* USER CODE END UART5_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART5_CLK_DISABLE();

		/**UART5 GPIO Configuration
		 PC12     ------> UART5_TX
		 PD2     ------> UART5_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

		/* UART5 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN UART5_MspDeInit 1 */

		/* USER CODE END UART5_MspDeInit 1 */
	} else if (uartHandle->Instance == USART1) {
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		 PA9     ------> USART1_TX
		 PA10     ------> USART1_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	} else if (uartHandle->Instance == USART2) {
		/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
		 PA2     ------> USART2_TX
		 PA3     ------> USART2_RX
		 */
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

		/* USART2 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	} else if (uartHandle->Instance == USART3) {
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		 PB10     ------> USART3_TX
		 PB11     ------> USART3_RX
		 */
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10 | GPIO_PIN_11);

		/* USART3 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	} else if (uartHandle->Instance == USART6) {
		/* USER CODE BEGIN USART6_MspDeInit 0 */

		/* USER CODE END USART6_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART6_CLK_DISABLE();

		/**USART6 GPIO Configuration
		 PC6     ------> USART6_TX
		 PC7     ------> USART6_RX
		 */
		HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);

		/* USART6 DMA DeInit */
		HAL_DMA_DeInit(uartHandle->hdmarx);
		HAL_DMA_DeInit(uartHandle->hdmatx);
		/* USER CODE BEGIN USART6_MspDeInit 1 */

		/* USER CODE END USART6_MspDeInit 1 */
	}
}
BOS_Status UpdateBaudrate(uint8_t port, uint32_t baudrate) {
	BOS_Status result = BOS_OK;
	UART_HandleTypeDef *huart = GetUart(port);

	huart->Init.BaudRate = baudrate;
	HAL_UART_Init(huart);

	return result;
}
/* --- Blocking (polling-based) read protected with a semaphore ---
 */
HAL_StatusTypeDef readPxMutex(uint8_t port, char *buffer, uint16_t n,
		uint32_t mutexTimeout, uint32_t portTimeout) {
	HAL_StatusTypeDef result = HAL_ERROR;

	if (GetUart(port) != NULL) {
		/* Wait for the semaphore to be available. */
		if (osSemaphoreWait(PxRxSemaphoreHandle[port], mutexTimeout) == osOK) {
			while (result != HAL_OK && result != HAL_TIMEOUT) {
				result = HAL_UART_Receive(GetUart(port), (uint8_t*) buffer, n,
						portTimeout);
			}
			/* Give back the semaphore. */
			osSemaphoreRelease(PxRxSemaphoreHandle[port]);
		}
	}

	return result;
}

/* --- Blocking (polling-based) write protected with a semaphore ---
 */
HAL_StatusTypeDef writePxMutex(uint8_t port, char *buffer, uint16_t n,
		uint32_t mutexTimeout, uint32_t portTimeout) {
	HAL_StatusTypeDef result = HAL_ERROR;

	if (GetUart(port) != NULL) {
		/*/ Wait for the semaphore to be available. */
		if (osSemaphoreWait(PxTxSemaphoreHandle[port], mutexTimeout) == osOK) {
			while (result != HAL_OK && result != HAL_TIMEOUT) {
				result = HAL_UART_Transmit(GetUart(port), (uint8_t*) buffer, n,
						portTimeout);
			}
			/* Give back the semaphore. */
			osSemaphoreRelease(PxTxSemaphoreHandle[port]);
		}
	}

	return result;
}

/* --- Non-blocking (interrupt-based) read protected with a semaphore ---
 */
HAL_StatusTypeDef readPxITMutex(uint8_t port, char *buffer, uint16_t n,
		uint32_t mutexTimeout) {
	HAL_StatusTypeDef result = HAL_ERROR;

	if (GetUart(port) != NULL) {
		/* Wait for the mutex to be available. */
		if (osSemaphoreWait(PxRxSemaphoreHandle[port], mutexTimeout) == osOK) {
			result = HAL_UART_Receive_IT(GetUart(port), (uint8_t*) buffer, n);
		}
	}

	return result;
}

/* --- Non-blocking (interrupt-based) write protected with a semaphore ---
 */
HAL_StatusTypeDef writePxITMutex(uint8_t port, char *buffer, uint16_t n,
		uint32_t mutexTimeout) {
	HAL_StatusTypeDef result = HAL_ERROR;

	if (GetUart(port) != NULL) {
		/* Wait for the mutex to be available. */
		if (osSemaphoreWait(PxTxSemaphoreHandle[port], mutexTimeout) == osOK) {
			result = HAL_UART_Transmit_IT(GetUart(port), (uint8_t*) buffer, n);
		}
	}

	return result;
}

/* --- Non-blocking (DMA-based) write protected with a semaphore ---
 */
HAL_StatusTypeDef writePxDMAMutex(uint8_t port, char *buffer, uint16_t n,
		uint32_t mutexTimeout) {
	HAL_StatusTypeDef result = HAL_ERROR;
	UART_HandleTypeDef *hUart = GetUart(port);

	if (hUart != NULL) {
		/* Wait for the mutex to be available. */
		if (osSemaphoreWait(PxTxSemaphoreHandle[port], mutexTimeout) == osOK) {

			/* Transmit the message */
			result = HAL_UART_Transmit_DMA(hUart, (uint8_t*) buffer, n);
		}
	}

	return result;
}

/* --- Get the UART for a given port.
 */
UART_HandleTypeDef* GetUart(uint8_t port) {
	switch (port) {
#ifdef _P1
	case P1:
		return P1uart;
#endif
#ifdef _P2
	case P2:
		return P2uart;
#endif
#ifdef _P3
	case P3:
		return P3uart;
#endif
#ifdef _P4
	case P4:
		return P4uart;
#endif
#ifdef _P5
	case P5:
		return P5uart;
#endif
#ifdef _P6
	case P6:
		return P6uart;
#endif
#ifdef _P7
		case P7 :
			return P7uart;
	#endif
#ifdef _P8
		case P8 :
			return P8uart;
	#endif
#ifdef _P9
		case P9 :
			return P9uart;
	#endif
#ifdef _P10
		case P10 :
			return P10uart;
	#endif
	default:
		return 0;
	}
}

/*-----------------------------------------------------------*/

/* --- Read Ports directions when a pre-defined topology file is used ---
 */
BOS_Status ReadPortsDir(void) {
	BOS_Status result = BOS_OK;
	/* Ask all other modules for their ports directions */
	for (uint8_t i = 1; i <= N; i++) {
		if (i != myID) {
			SendMessageToModule(i, CODE_READ_PORT_DIR, 0);
			Delay_ms_no_rtos(50);
			if (responseStatus != BOS_OK) {
				result = BOS_ERR_NoResponse;
			}
		} else {
			/* Check my own ports */
			for (uint8_t p = 1; p <= NumOfPorts; p++) {
				arrayPortsDir[myID - 1] |= (0x0000); /* Set bit to 1 */
			}
		}
	}

	return result;
}

/* --- Read Ports directions when a pre-defined topology file is used ---
 */
BOS_Status ReadPortsDirMSG(uint8_t SourceModule) {
	BOS_Status result = BOS_OK;
	uint16_t temp =0;
	/* Check my own ports */
//	for (p = 1; p <= NumOfPorts; p++) {
//		if (GetUart(p)->AdvancedInit.Swap== UART_ADVFEATURE_SWAP_ENABLE) {
//			messageParams[temp++] = p;
//		}
//	}
	/* Send response */
	SendMessageToModule(SourceModule, CODE_READ_PORT_DIR_RESPONSE, temp);
	return result;
}
/*-----------------------------------------------------------*/
#ifndef __N
/* --- Update module port directions based on what is stored in eeprom ---
 */
BOS_Status UpdateMyPortsDir(void) {
	BOS_Status result = BOS_OK;
	for (uint8_t p = 1; p <= NumOfPorts; p++) {
		/* Port is normal */
		SwapUartPins(GetUart(p), NORMAL);
	}
	return result;
}
#endif

/*-----------------------------------------------------------*/

/* --- Swap UART pins ( NORMAL | REVERSED )---
 */
void SwapUartPins(UART_HandleTypeDef *huart, uint8_t direction) {
	if (huart != NULL) {
		if (direction == REVERSED) {
//			arrayPortsDir[myID - 1] |= (0x8000 >> (GetPort(huart) - 1)); /* Set bit to one */
//			huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
//			huart->AdvancedInit.Swap = UART_ADVFEATURE_SWAP_ENABLE;
//			HAL_UART_Init(huart);
		} else if (direction == NORMAL) {
//			arrayPortsDir[myID - 1] &=(~(0x8000 >> (GetPort(huart) - 1))); /* Set bit to zero */
//			huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_SWAP_INIT;
//			huart->AdvancedInit.Swap = UART_ADVFEATURE_SWAP_DISABLE;
//			HAL_UART_Init(huart);
		}
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
