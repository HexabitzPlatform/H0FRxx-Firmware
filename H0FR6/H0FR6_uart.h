/*
 BitzOS (BOS) V0.2.6 - Copyright (C) 2017-2022 Hexabitz
 All rights reserved

 File Name     : H0FR6_uart.h
 Description   : Header file provides configuration for USART instances.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __H0FR6_uart_H
#define __H0FR6_uart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* External variables -----------------------------------------------*/
extern FlagStatus UartRxReady;
extern FlagStatus UartTxReady;
extern uint8_t PcPort;

#ifndef __N
	extern uint16_t arrayPortsDir[MaxNumOfModules];									/* Array ports directions */
#else
	extern uint16_t arrayPortsDir[__N];
#endif 
	 
// Blocking (polling-based) read
#define readPx(port, buffer, n, timeout) while(HAL_UART_Receive(GetUart(port), (uint8_t *)buffer, n, timeout) != HAL_OK) {}
	
// Blocking (polling-based) write
#define writePx(port, buffer, timeout) while(HAL_UART_Transmit(GetUart(port), (uint8_t *)buffer, strlen(buffer), timeout) != HAL_OK) {}

/* Check which UART interrupt occured */	 
#define HAL_UART_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((__HANDLE__)->Instance->ISR & (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/* External function prototypes -----------------------------------------------*/

extern HAL_StatusTypeDef readPxMutex(uint8_t port, char *buffer, uint16_t n, uint32_t mutexTimeout, uint32_t portTimeout);
extern HAL_StatusTypeDef writePxMutex(uint8_t port, char *buffer, uint16_t n, uint32_t mutexTimeout, uint32_t portTimeout);
extern HAL_StatusTypeDef readPxITMutex(uint8_t port, char *buffer, uint16_t n, uint32_t mutexTimeout);
extern HAL_StatusTypeDef writePxITMutex(uint8_t port, char *buffer, uint16_t n, uint32_t mutexTimeout);
extern HAL_StatusTypeDef writePxDMAMutex(uint8_t port, char *buffer, uint16_t n, uint32_t mutexTimeout);



#ifdef __cplusplus
}
#endif
#endif /*__H0FR6_uart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
