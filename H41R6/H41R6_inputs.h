/*
 BitzOS (BOS) V0.2.9 - Copyright (C) 2017-2023 Hexabitz
 All rights reserved

 File Name     : H41R6_inputs.h
 Description   : header file for Bitz digital and analog inputs.
 
 */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef H41R6_INPUTS_H
#define H41R6_INPUTS_H
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_adc_ex.h"
#include "string.h"
/* Private and global variables ----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* -----------------------------------------------------------------------
 |												Exported  Functions	 														|
 -----------------------------------------------------------------------
 */
extern BOS_Status GetPortGPIOs(uint8_t port,uint32_t *TX_Port,uint16_t *TX_Pin,uint32_t *RX_Port,uint16_t *RX_Pin);
extern void ReadTempAndVref(float *temp,float *Vref);
extern void ReadADCChannel(uint8_t Port,char *side,float *ADC_Value);
extern void ADCSelectChannel(uint8_t ADC_port,char *side);
extern float GetReadPrecentage(uint8_t port,float *precentageValue);
extern void Deinit_ADC_Channel(uint8_t port);

/*-----------------------------------------------------------*/
#endif
/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
