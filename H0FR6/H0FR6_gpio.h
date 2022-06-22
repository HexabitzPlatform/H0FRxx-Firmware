/*
 BitzOS (BOS) V0.2.7 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H0FR6_gpio.h
 Description   : Header file contains all the functions prototypes for
 the GPIO .

 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __H0FR6_gpio_H
#define __H0FR6_gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"


extern void GPIO_Init(void);
extern void IND_LED_Init(void);
extern void Switch_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__H0FR6_gpio_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
