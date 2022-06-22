/*
 BitzOS (BOS) V0.2.7 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H0FR6_adc.c
 Description   : Source Code provides configuration of the ADC instances.

 */

/* Includes ------------------------------------------------------------------*/
#include "H0FR6_adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

//ADC_HandleTypeDef hadc;


/* ADC init function */
//void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
//{
//  ADC_ChannelConfTypeDef sConfig = {0};
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  /** Configure for the selected ADC regular channel to be converted.
//  */
//  sConfig.Channel = ADC_CHANNEL_0;
//  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
//  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
//  HAL_ADC_ConfigChannel(hadc, &sConfig);
//
//  /**ADC GPIO Configuration
//  PA0     ------> ADC_IN0
//  */
//  GPIO_InitStruct.Pin = GPIO_PIN_0;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//
//}
void ADC_Channel_config(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
