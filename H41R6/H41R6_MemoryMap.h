/*
 BitzOS (BOS) V0.2.9 - Copyright (C) 2017-2023 Hexabitz
 All rights reserved

 File Name     : H41R6_MemoryMap.h
 Description   : Module MCU memory map header file.

 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H41R6_MEMORYMAP_H
#define H41R6_MEMORYMAP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Memory map: - STM32F091CB
 - Application: 0x08000000 - 0x0801D7FF >> 118 KB
 - Read-only (RO): 0x0801D800 - 0x0801DFFF >> 2 KB, used to store topology information and Command Snippets
 - Emulated EEPROM: 0x0801E000 - 0x0801FFFF >> 8 KB, fits 1024 16-bit variables in 2 main-duplicate pages (A and B)
 */
 /* Define the size of the sectors to be used */
 #define PAGE_SIZE               (uint32_t)0x4000  /* Page size = 16KByte */

 /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
    be done by word  */
 #define VOLTAGE_RANGE           (uint8_t)VOLTAGE_RANGE_3


#define APP_START_ADDRESS  			((uint32_t)0x08000000)
#define RO_START_ADDRESS  			((uint32_t)0x0801D800)
#define RO_MID_ADDRESS  			((uint32_t)0x0801DC00) 			// Snippets are stored here
//#define EEPROM_START_ADDRESS  		((uint32_t)0x0801E000)
#define FLASH_SIZE					((uint32_t)0x20000)				// All sizes in bytes
#define SRAM_SIZE					((uint32_t)0x8000)
//#define PAGE_SIZE             		((uint32_t)0x0800)  		/* Page size = 2KByte for STM32F07x and STM32F09x devices */
#define NumOfPages					(FLASH_SIZE/PAGE_SIZE)


#ifdef __cplusplus
}
#endif

#endif /* H41R6_MEMORYMAP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
