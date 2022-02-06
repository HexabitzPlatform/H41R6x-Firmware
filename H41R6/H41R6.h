/*
 BitzOS (BOS) V0.2.6 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H41R6.h
 Description   : Header file for module H41R6.
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H41R6_H
#define H41R6_H

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H41R6_MemoryMap.h"
#include "H41R6_uart.h"
#include "H41R6_gpio.h"
#include "H41R6_dma.h"
#include "H41R6_eeprom.h"
#include "H41R6_inputs.h"
/* Exported definitions -------------------------------------------------------*/

#define	modulePN		_H41R6

/* Port-related definitions */

#define	NumOfPorts		6


#define P_PROG 				P5						/* ST factory bootloader UART */

/* Define available ports */
#define _P1
#define _P2
#define _P3
#define _P4
#define _P5
#define _P6

/* Define available USARTs */
#define _Usart1 1
#define _Usart2 1
#define _Usart3 1
#define _Uart4  1
#define _Uart5  1
#define _Usart6	1

/* Port-UART mapping */
#define P1uart &huart4
#define P2uart &huart2
#define P3uart &huart3
#define P4uart &huart6
#define P5uart &huart1
#define P6uart &huart5

/* Port Definitions */
#define	USART1_TX_PIN		GPIO_PIN_9
#define	USART1_RX_PIN		GPIO_PIN_10
#define	USART1_TX_PORT		GPIOA
#define	USART1_RX_PORT		GPIOA
#define	USART1_AF			GPIO_AF7_USART1

#define	USART2_TX_PIN		GPIO_PIN_2
#define	USART2_RX_PIN		GPIO_PIN_3
#define	USART2_TX_PORT		GPIOA
#define	USART2_RX_PORT		GPIOA
#define	USART2_AF			GPIO_AF7_USART2

#define	USART3_TX_PIN		GPIO_PIN_8
#define	USART3_RX_PIN		GPIO_PIN_9
#define	USART3_TX_PORT		GPIOD
#define	USART3_RX_PORT		GPIOD
#define	USART3_AF			GPIO_AF7_USART3

#define	USART4_TX_PIN		GPIO_PIN_0
#define	USART4_RX_PIN		GPIO_PIN_1
#define	USART4_TX_PORT		GPIOA
#define	USART4_RX_PORT		GPIOA
#define	USART4_AF			GPIO_AF8_UART4

#define	USART5_TX_PIN		GPIO_PIN_5
#define	USART5_RX_PIN		GPIO_PIN_6
#define	USART5_TX_PORT		GPIOB
#define	USART5_RX_PORT		GPIOB
#define	USART5_AF			GPIO_AF8_UART5

#define	USART6_TX_PIN		GPIO_PIN_6
#define	USART6_RX_PIN		GPIO_PIN_7
#define	USART6_TX_PORT		GPIOC
#define	USART6_RX_PORT		GPIOC
#define	USART6_AF			GPIO_AF8_USART6

/* Module-specific Definitions */



#define NUM_MODULE_PARAMS						1

/* Module EEPROM Variables */

// Module Addressing Space 500 - 599
#define _EE_MODULE							500

/* Module_Status Type Definition */
typedef enum {
	H41R6_OK =0, H41R6_ERR_UnknownMessage, H41R6_ERR_WrongColor, H41R6_ERR_WrongIntensity, H41R6_ERR_WrongMode, H41R6_ERROR =255
} Module_Status;

/* Indicator LED */
#define _IND_LED_PORT		GPIOB
#define _IND_LED_PIN		GPIO_PIN_10

/* Export UART variables */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

/* Define UART Init prototypes */
extern void MX_USART1_UART_Init(void);
extern void MX_USART2_UART_Init(void);
extern void MX_USART3_UART_Init(void);
extern void MX_UART4_UART_Init(void);
extern void MX_UART5_UART_Init(void);
extern void MX_USART6_UART_Init(void);
extern void SystemClock_Config(void);
extern void ExecuteMonitor(void);
void Module_Peripheral_Init(void);
uint8_t GetPort(UART_HandleTypeDef *huart);



/* -----------------------------------------------------------------------
 |																APIs	 																 	|
 -----------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------
 |															Commands																 	|
 -----------------------------------------------------------------------
 */

#endif /* H41R6_H */

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
