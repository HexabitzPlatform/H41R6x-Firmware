/*
 BitzOS (BOS) V0.2.6 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H41R6_dma.c
 Description   : source file Contains Peripheral DMA setup .

 */

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H41R6_dma.h"
#include "H41R6_uart.h"
/* DMA structs. Number of structs depends on available DMA channels and array ports where some channels might be reconfigured.
 - Update for non-standard MCUs
 */
DMA_HandleTypeDef msgRxDMA[6] = { 0 };
DMA_HandleTypeDef msgTxDMA[6] = { 0 };
DMA_HandleTypeDef streamDMA[6] = { 0 };
CRC_HandleTypeDef hcrc;

extern uint8_t UARTRxBuf[NumOfPorts][MSG_RX_BUF_SIZE];

/*function prototypes -----------------------------------------------*/
void DMA_MSG_RX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
void DMA_STREAM_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);
void DMA_MSG_RX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);
void DMA_MSG_TX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);

/* Private function prototypes -----------------------------------------------*/
void SetupDMAInterrupts(DMA_HandleTypeDef *hDMA, uint8_t priority);
void UnSetupDMAInterrupts(DMA_HandleTypeDef *hDMA);
void RemapAndLinkDMAtoUARTRx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
void RemapAndLinkDMAtoUARTTx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA);
uint32_t SelectDMAchannel(DMA_Stream_TypeDef *hDMA);
/* DMA Handlers definitions -----------------------------------------------*/
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;

DMA_HandleTypeDef hdma_uart5_rx;
DMA_HandleTypeDef hdma_uart5_tx;

DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/**
 * Enable DMA controller clock
 */
void DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	/* Initialize messaging RX DMAs x 6 - Update for non-standard MCUs */
#ifdef _P1
	DMA_MSG_RX_CH_Init(&msgRxDMA[0], DMA1_Stream2); /* Initialize messaging Port 1 RX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[0], DMA1_Stream4); /* Initialize messaging Port 1 TX DMA*/
#endif
#ifdef _P2
	DMA_MSG_RX_CH_Init(&msgRxDMA[1], DMA1_Stream5); /* Initialize messaging Port 2 RX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[1], DMA1_Stream6); /* Initialize messaging Port 2 TX DMA*/
#endif
#ifdef _P3
	DMA_MSG_RX_CH_Init(&msgRxDMA[2], DMA2_Stream1); /* Initialize messaging Port 3 RX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[2], DMA2_Stream6); /* Initialize messaging Port 3 TX DMA*/
#endif
#ifdef _P4
	DMA_MSG_RX_CH_Init(&msgRxDMA[3], DMA1_Stream1); /* Initialize messaging Port 4 TX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[3], DMA1_Stream3); /* Initialize messaging Port 4 TX DMA*/
#endif
#ifdef _P5
	DMA_MSG_RX_CH_Init(&msgRxDMA[4], DMA2_Stream2); /* Initialize messaging Port 5 RX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[4], DMA2_Stream7); /* Initialize messaging Port 5 TX DMA*/
#endif
#ifdef _P6
	DMA_MSG_RX_CH_Init(&msgRxDMA[5], DMA1_Stream0); /* Initialize messaging Port 6 RX DMA*/
	DMA_MSG_TX_CH_Init(&msgTxDMA[5], DMA1_Stream7); /* Initialize messaging Port 6 TX DMA*/
#endif
}

/* Initialize a messaging RX DMA channel  */
void DMA_MSG_RX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch) {
	hDMA->Instance = ch;
	hDMA->Init.Channel = SelectDMAchannel(ch);
	hDMA->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_ENABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_CIRCULAR;
	hDMA->Init.Priority = MSG_DMA_PRIORITY;
	hDMA->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(hDMA);
}

/* Initialize a messaging TX DMA channel  */
void DMA_MSG_TX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch) {
	hDMA->Instance = ch;
	hDMA->Init.Channel = SelectDMAchannel(ch);
	hDMA->Init.Direction = DMA_MEMORY_TO_PERIPH;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_ENABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_NORMAL;
	hDMA->Init.Priority = MSG_DMA_PRIORITY;
	hDMA->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(hDMA);

}

/* Initialize a streaming DMA channel (RX only)
 */
void DMA_STREAM_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch) {

	hDMA->Instance = ch;
	hDMA->Init.Channel = SelectDMAchannel(ch);
	hDMA->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hDMA->Init.PeriphInc = DMA_PINC_DISABLE;
	hDMA->Init.MemInc = DMA_MINC_DISABLE;
	hDMA->Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hDMA->Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hDMA->Init.Mode = DMA_CIRCULAR;
	hDMA->Init.Priority = STREAM_DMA_PRIORITY;
	hDMA->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(hDMA);
}

uint32_t SelectDMAchannel(DMA_Stream_TypeDef *hDMA) {
//	if (hDMA == DMA2_Stream6 || hDMA == DMA2_Stream1) {
//		return DMA_CHANNEL_5;
//	} else {
//		return DMA_CHANNEL_4;
//	}

	if(hDMA==DMA1_Stream2)
		return DMA_CHANNEL_1;
	else if(hDMA==DMA1_Stream5)
		return DMA_CHANNEL_2;
	else if(hDMA==DMA2_Stream1)
		return DMA_CHANNEL_3;
	else if(hDMA==DMA1_Stream1)
		return DMA_CHANNEL_4;
	else if(hDMA==DMA2_Stream2)
		return DMA_CHANNEL_5;
	else if(hDMA==DMA1_Stream0)
		return DMA_CHANNEL_6;

}
/*-----------------------------------------------------------*/
/* Setup and control functions ------------------------------*/
/*-----------------------------------------------------------*/

/* Setup and start Messaging DMAs
 */
void SetupMessagingRxDMAs(void) {
#ifdef _P1
	if (portStatus[P1] == FREE)
		DMA_MSG_RX_Setup(P1uart, &msgRxDMA[0]);
#endif
#ifdef _P2
	if (portStatus[P2] == FREE)
		DMA_MSG_RX_Setup(P2uart, &msgRxDMA[1]);
#endif
#ifdef _P3
	if (portStatus[P3] == FREE)
    	DMA_MSG_RX_Setup(P3uart, &msgRxDMA[2]);
#endif
#ifdef _P4
	if (portStatus[P4] == FREE)
		DMA_MSG_RX_Setup(P4uart, &msgRxDMA[3]);
#endif
#ifdef _P5
	if (portStatus[P5] == FREE)
		DMA_MSG_RX_Setup(P5uart, &msgRxDMA[4]);
#endif
#ifdef _P6
	if (portStatus[P6] == FREE)
		DMA_MSG_RX_Setup(P6uart, &msgRxDMA[5]);
#endif
}
/*-----------------------------------------------------------*/

/* Messaging DMA RX setup (port-to-memory)
 */
void DMA_MSG_RX_Setup(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA) {
	/* Remap and link to UART Rx */
	RemapAndLinkDMAtoUARTRx(huart, hDMA);
//	  __HAL_LINKDMA(huart, hdmarx, hDMA);

	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, MSG_DMA_INT_PRIORITY);

	/* Start DMA stream	*/
	HAL_UART_Receive_DMA(huart, (uint8_t*) &UARTRxBuf[GetPort(huart) - 1],MSG_RX_BUF_SIZE);
}

/*-----------------------------------------------------------*/

/* Messaging DMA TX setup (memory-to-port)
 */
void DMA_MSG_TX_Setup(UART_HandleTypeDef *huart) {
	DMA_HandleTypeDef *hDMA;

	/* Remap and link to UART Tx */
	RemapAndLinkDMAtoUARTTx(huart, hDMA);

	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, MSG_DMA_INT_PRIORITY);

}

/*-----------------------------------------------------------*/

/* Unsetup messaging DMA TX (memory-to-port) since TX DMAs are shared
 */
void DMA_MSG_TX_UnSetup(UART_HandleTypeDef *huart) {
	/* Setup DMA interrupts */
	UnSetupDMAInterrupts(huart->hdmatx);

	/* Unlink the TX DMA and UART */
	huart->hdmatx->Parent = NULL;
	huart->hdmatx = NULL;
}

/* Streaming DMA setup (port-to-port)
 */
void DMA_STREAM_Setup(UART_HandleTypeDef *huartSrc,
		UART_HandleTypeDef *huartDst, uint16_t num) {
	DMA_HandleTypeDef *hDMA;
	uint8_t port = GetPort(huartSrc);

	/* Select DMA struct */
	hDMA = &streamDMA[port - 1];

	/* Remap and link to UART RX */
	RemapAndLinkDMAtoUARTRx(huartSrc, hDMA);

	/* Setup DMA interrupts */
	SetupDMAInterrupts(hDMA, STREAM_DMA_INT_PRIORITY);

	/* Start DMA stream	*/
	huartSrc->gState = HAL_UART_STATE_READY;
	HAL_UART_Receive_DMA(huartSrc, (uint8_t*) (&(huartDst->Instance->DR)), num);
}

/*-----------------------------------------------------------*/
/* Private functions ----------------------------------------*/
/*-----------------------------------------------------------*/

/* --- Stop a streaming DMA ---
 */
void StopStreamDMA(uint8_t port) {
	DMA_HandleTypeDef *hDMA;

	/* Select DMA struct */
	hDMA = &streamDMA[port - 1];

	HAL_DMA_Abort(hDMA);
	hDMA->Instance->NDTR = 0;
	dmaStreamCount[port - 1] = 0;
	dmaStreamTotal[port - 1] = 0;

}


/* --- Stop a messaging DMA ---
 */
void StopMsgDMA(uint8_t port){
	DMA_HandleTypeDef *hDMA;

	/* Select DMA struct */
	hDMA =&msgRxDMA[port - 1];

	HAL_DMA_Abort(hDMA);
	hDMA->Instance->NDTR =0;
}


/*-----------------------------------------------------------*/

/* Switch messaging DMA channels to streaming
 */
void SwitchMsgDMAToStream(uint8_t port) {
	// TODO - Make sure all messages in the RX buffer have been parsed?

	// Stop the messaging DMA
	StopMsgDMA(port);

	// Initialize a streaming DMA using same channel
	DMA_STREAM_CH_Init(&streamDMA[port - 1], msgRxDMA[port - 1].Instance);
}

/*-----------------------------------------------------------*/

/* Switch streaming DMA channel to messaging
 */
void SwitchStreamDMAToMsg(uint8_t port) {
	// Stop the streaming DMA
	StopStreamDMA(port);

	// Initialize a messaging DMA using same channels
	DMA_MSG_RX_CH_Init(&msgRxDMA[port - 1], streamDMA[port - 1].Instance);

	// Remove stream DMA and change port status
	portStatus[GetPort(streamDMA[port - 1].Parent)] = FREE;
	streamDMA[port - 1].Instance = 0;
	dmaStreamDst[port - 1] = 0;

	// Read this port again in messaging mode
	DMA_MSG_RX_Setup(GetUart(port), &msgRxDMA[port - 1]);

}

/* Setup DMA interrupts
 */
void SetupDMAInterrupts(DMA_HandleTypeDef *hDMA, uint8_t priority) {
	switch ((uint32_t) hDMA->Instance) {

	case (uint32_t) DMA1_Stream0:
		HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
		break;
	case (uint32_t) DMA1_Stream1:
		HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
		break;
	case (uint32_t) DMA1_Stream2:
		HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);
		break;
	case (uint32_t) DMA1_Stream3:
		HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
		break;
	case (uint32_t) DMA1_Stream4:
		HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
		break;
	case (uint32_t) DMA1_Stream5:
		HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
		break;
	case (uint32_t) DMA1_Stream6:
		HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
		break;
	case (uint32_t) DMA1_Stream7:
		HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
		break;
	case (uint32_t) DMA2_Stream1:
		HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
		break;
	case (uint32_t) DMA2_Stream2:
		HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
		break;
	case (uint32_t) DMA2_Stream6:
		HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
		break;
	case (uint32_t) DMA2_Stream7:
		HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, priority, 0);
		HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
		break;

	default:
		break;
	}

}

/*-----------------------------------------------------------*/

/* UnSetup DMA interrupts
 */
void UnSetupDMAInterrupts(DMA_HandleTypeDef *hDMA) {

	switch ((uint32_t) hDMA->Instance) {

	case (uint32_t) DMA1_Stream0:
		HAL_NVIC_DisableIRQ(DMA1_Stream0_IRQn);
		break;
	case (uint32_t) DMA1_Stream1:
		HAL_NVIC_DisableIRQ(DMA1_Stream1_IRQn);
		break;
	case (uint32_t) DMA1_Stream2:
		HAL_NVIC_DisableIRQ(DMA1_Stream2_IRQn);
		break;
	case (uint32_t) DMA1_Stream3:
		HAL_NVIC_DisableIRQ(DMA1_Stream3_IRQn);
		break;
	case (uint32_t) DMA1_Stream4:
		HAL_NVIC_DisableIRQ(DMA1_Stream4_IRQn);
		break;
	case (uint32_t) DMA1_Stream5:
		HAL_NVIC_DisableIRQ(DMA1_Stream5_IRQn);
		break;
	case (uint32_t) DMA1_Stream6:
		HAL_NVIC_DisableIRQ(DMA1_Stream6_IRQn);
		break;
	case (uint32_t) DMA1_Stream7:
		HAL_NVIC_DisableIRQ(DMA1_Stream7_IRQn);
		break;
	case (uint32_t) DMA2_Stream1:
		HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);
		break;
	case (uint32_t) DMA2_Stream2:
		HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);
		break;
	case (uint32_t) DMA2_Stream6:
		HAL_NVIC_DisableIRQ(DMA2_Stream6_IRQn);
		break;
	case (uint32_t) DMA2_Stream7:
		HAL_NVIC_DisableIRQ(DMA2_Stream7_IRQn);
		break;

	default:
		break;

	}
}

/* Remap and link the UART RX and DMA structs
 */
void RemapAndLinkDMAtoUARTRx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA) {
	// USART 1
	if (huart->Instance == USART1) {
		/* USART1 DMA & RX Init */
		__HAL_LINKDMA(P1uart, hdmarx,  msgRxDMA[0]);
	}
	/* USART2 DMA & RX Init */
	else if (huart->Instance == USART2) {
		__HAL_LINKDMA(P2uart, hdmarx, msgRxDMA[1]);
	}
	/* USART3 DMA & RX Init */
	else if (huart->Instance == USART3) {
		__HAL_LINKDMA(P3uart, hdmarx, msgRxDMA[2]);
	}
	/* USART4 DMA & RX Init */
	else if (huart->Instance == UART4) {
		__HAL_LINKDMA(P4uart, hdmarx, msgRxDMA[3]);
	}
	/* UART5 DMA & RX Init */
	else if (huart->Instance == UART5) {
		__HAL_LINKDMA(P5uart, hdmarx, msgRxDMA[4]);
	}
	/* UART6 DMA & RX Init */
	else if (huart->Instance == USART6) {
		__HAL_LINKDMA(P6uart, hdmarx, msgRxDMA[5]);
	}

}

/* Remap and link the UART TX and DMA structs
 */
void RemapAndLinkDMAtoUARTTx(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hDMA) {

	/* USART1 DMA & TX Init */
	if (huart->Instance == USART1 && hDMA->Instance == DMA2_Stream7) {
		__HAL_LINKDMA(huart, hdmatx, hdma_usart1_tx);
	}
	/* USART2 DMA & TX Init */
	else if (huart->Instance == USART2 && hDMA->Instance == DMA1_Stream6) {
		__HAL_LINKDMA(huart, hdmatx, hdma_usart2_tx);
	}
	/* USART3 DMA & TX Init */
	else if (huart->Instance == USART3 && hDMA->Instance == DMA1_Stream3) {
		/* USART4 DMA & TX Init */
		__HAL_LINKDMA(huart, hdmatx, hdma_usart3_tx);
	}
	/* UART4 DMA & TX Init */
	else if (huart->Instance == UART4 && hDMA->Instance == DMA1_Stream4) {
		__HAL_LINKDMA(huart, hdmatx, hdma_uart4_tx);
	}
	/* UART5 DMA & TX Init */
	else if (huart->Instance == UART5 && hDMA->Instance == DMA1_Stream7) {
		__HAL_LINKDMA(huart, hdmatx, hdma_uart5_tx);
	}
	/* UART6 DMA & TX Init */
	else if (huart->Instance == USART6 && hDMA->Instance == DMA2_Stream6) {
		__HAL_LINKDMA(huart, hdmatx, hdma_usart6_tx);
	}
}

/*-----------------------------------------------------------*/
/* Hardware CRC ---------------------------------------------*/
/*-----------------------------------------------------------*/

/* CRC init function */
void CRC_Init(void) {
	hcrc.Instance = CRC;
	HAL_CRC_Init(&hcrc);

}
void HAL_CRC_MspInit(CRC_HandleTypeDef *crcHandle) {

	if (crcHandle->Instance == CRC) {
		/* CRC clock enable */
		__HAL_RCC_CRC_CLK_ENABLE();
	}
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef *crcHandle) {

	if (crcHandle->Instance == CRC) {
		/* Peripheral clock disable */
		__HAL_RCC_CRC_CLK_DISABLE();
	}
}

/*
 * calculate CRC8 byte for a data buffer
 */
uint8_t CalculateCRC8(uint8_t pBuffer[], uint16_t size) {
	uint8_t pTemp;
	/* check if the passed variables are null */
	if (NULL != pBuffer && 0 != size) {
		pTemp = HAL_CRC_Calculate(&hcrc, (uint32_t*) pBuffer, size / 4);
		if ((size % 4) != 0) {
			pTemp = HAL_CRC_Accumulate(&hcrc,
					(uint32_t*) &pBuffer[(size / 4) * 4], 1);
		}
		return pTemp;
	} else
		return 0;
}

/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
