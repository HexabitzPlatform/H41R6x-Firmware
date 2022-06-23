/*
 BitzOS (BOS) V0.2.7 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H41R6_timers.c
 Description   : Peripheral timers setup source file.

 Required MCU resources :

 >> Timer 14 for micro-sec delay.
 >> Timer 15 for milli-sec delay.

 */

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "stm32f4xx_hal.h"
/*----------------------------------------------------------------------------*/
/* Configure Timers                                                              */
/*----------------------------------------------------------------------------*/

/* Variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim14; /* micro-second delay counter */
TIM_HandleTypeDef htim11; /* milli-second delay counter */

/*  Micro-seconds timebase init function - TIM14 (16-bit)
 */
void TIM_USEC_Init(void){
	TIM_MasterConfigTypeDef sMasterConfig;

	/* Peripheral clock enable */
	__TIM14_CLK_ENABLE();

	/* Peripheral configuration */
	htim14.Instance = TIM14;
	htim14.Init.Prescaler =HAL_RCC_GetPCLK1Freq() / 1000000;
	htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim14.Init.Period =0xFFFF;
	HAL_TIM_Base_Init(&htim14);

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim14,&sMasterConfig);

	HAL_TIM_Base_Start(&htim14);
}

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

/*  Milli-seconds timebase init function - TIM11 (16-bit)
 */
void TIM_MSEC_Init(void){
  TIM_MasterConfigTypeDef sMasterConfig;

	/* Peripheral clock enable */
	__TIM11_CLK_ENABLE();

	/* Peripheral configuration */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = HAL_RCC_GetPCLK1Freq()/1000;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 0xFFFF;
  HAL_TIM_Base_Init(&htim11);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim11, &sMasterConfig);

	HAL_TIM_Base_Start(&htim11);
}

/*-----------------------------------------------------------*/

/* --- Load and start micro-second delay counter ---
 */
void StartMicroDelay(uint16_t Delay){
	uint32_t t0 =0;

	portENTER_CRITICAL();

	if(Delay) {
		t0 =htim14.Instance->CNT;

		while(htim14.Instance->CNT - t0 <= Delay) {
		};
	}

	portEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

/* --- Load and start milli-second delay counter ---
 */
void StartMilliDelay(uint16_t Delay){
	uint32_t t0 =0;

	portENTER_CRITICAL();

	if(Delay) {
		t0 =htim11.Instance->CNT;

		while(htim11.Instance->CNT - t0 <= Delay) {
		};
	}

	portEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
