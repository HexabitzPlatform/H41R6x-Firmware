/*
 BitzOS (BOS) V0.2.9 - Copyright (C) 2017-2023 Hexabitz
 All rights reserved

 File Name     : main.c
 Description   : Main program body.
 */
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Main function ------------------------------------------------------------*/
uint8_t w[10],a[10]={'a','w'};
uint32_t z ;
int main(void){

	Module_Init();		//Initialize Module &  BitzOS

	//Don't place your code here.
	for(;;){}
}

/*-----------------------------------------------------------*/
/* User Task */
void UserTask(void *argument) {
	// put your code here, to run repeatedly.
	HAL_UART_Receive_DMA(&huart2, w, 10);
	while (1) {
//		HAL_UART_Receive_DMA(&huart2, w, 10);
		z=HAL_RCC_GetHCLKFreq();
//		HAL_Delay(1000);
//		HAL_UART_Receive(&huart6,w,5,0xffff);
//		HAL_UART_Transmit(&huart6, a, 2, 0xffff);

	}
}

/*-----------------------------------------------------------*/
