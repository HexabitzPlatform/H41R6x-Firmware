/* BitzOS (BOS) V0.2.9 - Copyright (C) 2017-2023 Hexabitz
 All rights reserved

 File Name     : H41R6_gpio.h
 Description   : Header file contains all the functions prototypes for
 the GPIO .

 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H41R6_gpio_H
#define H41R6_gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


extern void GPIO_Init(void);
extern void IND_LED_Init(void);



#ifdef __cplusplus
}
#endif
#endif /*H41R6_gpio_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
