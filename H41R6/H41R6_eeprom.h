/*
 BitzOS (BOS) V0.2.9 - Copyright (C) 2017-2023 Hexabitz
 All rights reserved

 File Name     : H41R6_eeprom.h
 Description   : Header file contains all the functions prototypes for the EEPROM
 	 	 	 	 emulation firmware library.

 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __H41R6_EEPROM_H
#define __H41R6_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* Exported constants --------------------------------------------------------*/
/* EEPROM emulation firmware error codes */
#define EE_OK      (uint32_t)HAL_OK
#define EE_ERROR   (uint32_t)HAL_ERROR
#define EE_BUSY    (uint32_t)HAL_BUSY
#define EE_TIMEOUT (uint32_t)HAL_TIMEOUT

/* EEPROM start address in Flash */
#define EEPROM_START_ADDRESS  ((uint32_t)0x08008000) /* EEPROM emulation start address:
                                                  from sector2 : after 16KByte of used
                                                  Flash memory */

/* Pages 0 and 1 base and end addresses */
#define PAGE0_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x0000))
#define PAGE0_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (PAGE_SIZE - 1)))
#define PAGE0_ID               FLASH_SECTOR_2

#define PAGE1_BASE_ADDRESS    ((uint32_t)(EEPROM_START_ADDRESS + 0x4000))
#define PAGE1_END_ADDRESS     ((uint32_t)(EEPROM_START_ADDRESS + (2 * PAGE_SIZE - 1))-1)
#define PAGE1_ID               FLASH_SECTOR_3

/* Used Flash pages for EEPROM emulation */
#define PAGE0                 ((uint16_t)0x0000)
#define PAGE1                 ((uint16_t)0x0001) /* Page nb between PAGE0_BASE_ADDRESS & PAGE1_BASE_ADDRESS*/

/* No valid page define */
#define NO_VALID_PAGE         ((uint16_t)0x00AB)

/* Page status definitions */
#define ERASED                ((uint16_t)0xFFFF)     /* Page is empty */
#define RECEIVE_DATA          ((uint16_t)0xEEEE)     /* Page is marked to receive data */
#define VALID_PAGE            ((uint16_t)0x0000)     /* Page containing valid data */

/* Valid pages in read and write defines */
#define READ_FROM_VALID_PAGE  ((uint8_t)0x00)
#define WRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Page full define */
#define PAGE_FULL             ((uint8_t)0x80)

/* Variables' number */
#define NB_OF_VAR             ((uint8_t)1024)

/* EEPROM virtual addresses - Consider MaxNumOfModules is 25 */
// BOS Addressing Space 1 - 499
#define _EE_NBASE							1
#define _EE_PORT_DIR_BASE					2				// Todo: Move to RO - 25 modules - 25 variables
#define _EE_ALIAS_BASE						28				// 25 modules/10 chars - 125 variables
#define _EE_GROUP_ALIAS_BASE			    153				// 10 groups/10 chars - 50 variables
#define _EE_GROUP_MODULES_BASE		   		203				// 25 modules - 25 variables
#define _EE_DMA_STREAM_BASE					228				// 8 variables
#define _EE_BUTTON_BASE						236				// 4 * MaxNumOfPorts (10) variables for buttons: port(4 bits), type (4 bits), events (8 bits)
															// pressed_for_x_1 (8 bits), released_for_y_1 (8 bits), etc.
#define _EE_PARAMS_BASE						276				// Parameter base: BOS trace (MSB) | BOS response - 1 variable 
#define _EE_PARAMS_DEBOUNCE					277				// Parameter: Button debounce - 1 variable
#define _EE_PARAMS_SINGLE_CLICK				278				// Parameter: Button single click - 1 variable
#define _EE_PARAMS_DBL_CLICK				279				// Parameter: Button double click (inter-click min and max) - 1 variable
#define _EE_CLI_BAUD						280				// Parameter: CLI baudrate - LSB halfword, MSB halfword - 2 variables
#define _EE_PARAMS_RTC						282				// Parameter: RTC hourformat | RTC daylightsaving - 1 variable
#define _EE_PARAMS_DISABLE_CLI				283				// Parameter: Disable CLI - 1 variable
#define _EE_PARAMS_Messaging			    284				// Parameter base: BOSMessaging Acknowledgment (MSB) | BOS trial - 1 variable

// Module Addressing Space 500 - 599
#define _EE_MODULE_BASE						500

// User Addressing Space 600 - 1024
#define _EE_EMPTY_VAR_BASE					600

#if MaxNumOfModules > 26						// Update
 #warning "Data for 26 modules only will be stored in EEPROM."
#endif

/* Exported variables --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t EE_Init(void);
uint16_t EE_Format(void);
uint16_t EE_ReadVariable(uint16_t VirtAddress,uint16_t *Data);
uint16_t EE_WriteVariable(uint16_t VirtAddress,uint16_t Data);
uint16_t Flash_WriteVariable(uint32_t Address,uint16_t Data);
BOS_Status EraseSector(uint32_t sector );
#endif /* __BOS_EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
