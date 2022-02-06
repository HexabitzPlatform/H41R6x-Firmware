/*
 BitzOS (BOS) V0.2.6 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H41R6_dma.h
 Description   : Header file contains Peripheral DMA setup.

 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H41R6_dma_H
#define H41R6_dma_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "stm32f4xx_hal.h"

/* DMA memory to memory transfer handles -------------------------------------*/
#define HAL_DMA_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((__HANDLE__)->LISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/* Export DMA structs */
extern DMA_HandleTypeDef msgRxDMA[6];
extern DMA_HandleTypeDef msgTxDMA[6];
extern DMA_HandleTypeDef streamDMA[6];
extern CRC_HandleTypeDef hcrc;


extern void DMA_Init(void);
extern void DMA_STREAM_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);
extern void DMA_MSG_RX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);
extern void DMA_MSG_TX_CH_Init(DMA_HandleTypeDef *hDMA, DMA_Stream_TypeDef *ch);
extern void SetupMessagingRxDMAs(void);
extern void DMA_MSG_RX_Setup(UART_HandleTypeDef *huart,DMA_HandleTypeDef *hDMA);
extern void DMA_MSG_TX_Setup(UART_HandleTypeDef *huart);
extern void DMA_MSG_TX_UnSetup(UART_HandleTypeDef *huart);
extern void CRC_Init(void);
extern uint8_t CalculateCRC8(uint8_t pBuffer[], uint16_t size);
void StopMsgDMA(uint8_t port);
#ifdef __cplusplus
}
#endif

#endif /* H41R6_dma_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
