/*
 BitzOS (BOS) V0.2.6 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/
uint8_t Buffer[4]={'A','B','C','D'};
uint8_t *Buffer1;

/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/

int main(void){

	Module_Init();		//Initialize Module &  BitzOS
	//Don't place your code here.
	for(;;){}
}

/*-----------------------------------------------------------*/

/* User Task */
void UserTask(void *argument) {
	// put your code here, to run repeatedly.
//	HAL_UART_DeInit(&huart3);
//	MX_USART3_UART_Init();

//	HAL_UART_Receive_IT(&huart3, Buffer1,1);

	while (1) {
//		HAL_UART_Receive(&huart3, Buffer1, 1, 100);
//		Delay_ms(10);
//		HAL_UART_Transmit(&huart3, Buffer, 1, 100);
//		Delay_ms(10);
//		IND_ON();
	//	HAL_UART_Receive(&huart3, (uint8_t *)&Buffer1,1,10);
//		IND_OFF();
	}
}

/*-----------------------------------------------------------*/
