/*
 BitzOS (BOS) V0.2.5 - Copyright (C) 2017-2021 Hexabitz
 All rights reserved

 File Name     : H0FR6_adc.h
 Description   : Header file provides configuration of the ADC instances.

 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC_Init(void);
void ADC_Channel_config(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
