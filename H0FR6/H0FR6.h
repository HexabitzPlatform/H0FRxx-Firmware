/*
    BitzOS (BOS) V0.2.4 - Copyright (C) 2017-2021 Hexabitz
    All rights reserved
		
    File Name     : H0FR6.h
    Description   : Header file for module H0FR1 SPDT mechanical DC relay
										and module H0FR6 Solid state AC relay (AQH3213A).
*/
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H0FR6_H
#define H0FR6_H

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H0FR6_MemoryMap.h"	
#include "H0FR6_uart.h"	
#include "H0FR6_gpio.h"	
#include "H0FR6_dma.h"
#include "H0FR6_adc.h"
	
	
/* Exported definitions -------------------------------------------------------*/
#ifdef H0FR1
	#define	modulePN		_H0FR1
#endif
#ifdef H0FR6
	#define	modulePN		_H0FR6
#endif

/* Port-related definitions */
#define	NumOfPorts			5
#define P_PROG 				P2						/* ST factory bootloader UART */

/* Define available ports */
#define _P1 
#define _P2 
#define _P3 
#define _P4 
#define _P5 

/* Define available USARTs */
#define _Usart1 1
#define _Usart2 1
#define _Usart3 1
#define _Usart5 1
#define _Usart6 1

/* Port-UART mapping */
#define P1uart &huart5
#define P2uart &huart2	
#define P3uart &huart6	
#define P4uart &huart3
#define P5uart &huart1

/* Port Definitions */
#define	USART1_TX_PIN		GPIO_PIN_9
#define	USART1_RX_PIN		GPIO_PIN_10
#define	USART1_TX_PORT		GPIOA
#define	USART1_RX_PORT		GPIOA
#define	USART1_AF			GPIO_AF1_USART1

#define	USART2_TX_PIN		GPIO_PIN_2
#define	USART2_RX_PIN		GPIO_PIN_3
#define	USART2_TX_PORT		GPIOA
#define	USART2_RX_PORT		GPIOA
#define	USART2_AF			GPIO_AF1_USART2

#define	USART3_TX_PIN		GPIO_PIN_10
#define	USART3_RX_PIN		GPIO_PIN_11
#define	USART3_TX_PORT		GPIOB
#define	USART3_RX_PORT		GPIOB
#define	USART3_AF			GPIO_AF4_USART3

#define	USART5_TX_PIN		GPIO_PIN_3
#define	USART5_RX_PIN		GPIO_PIN_4
#define	USART5_TX_PORT		GPIOB
#define	USART5_RX_PORT		GPIOB
#define	USART5_AF			GPIO_AF4_USART5

#define	USART6_TX_PIN		GPIO_PIN_4
#define	USART6_RX_PIN		GPIO_PIN_5
#define	USART6_TX_PORT		GPIOA
#define	USART6_RX_PORT		GPIOA
#define	USART6_AF			GPIO_AF5_USART6

/* Module-specific Definitions */
#if defined(H0FR1) || defined(H0FR7)
	#define	_Relay_PIN						GPIO_PIN_0
	#define	_Relay_PORT						GPIOB
	#define _Relay_GPIO_CLK()				__GPIOB_CLK_ENABLE();
#endif
#if defined(H0FR1) || defined(H0FR7)
	#define	_Relay_PIN						GPIO_PIN_0
	#define	_Relay_PORT						GPIOB
	#define _Relay_TIM_CH					TIM_CHANNEL_3
	#define _Relay_GPIO_CLK()				__GPIOB_CLK_ENABLE();
	#define PWM_TIMER_CLOCK					16000000
	#define Relay_PWM_DEF_FREQ				24000
	#define Relay_PWM_DEF_PERIOD			((float) (1/Relay_PWM_FREQ) )
#endif

#ifdef H0FR7
	#define ADC_CONVERSION 0.00595
#endif

#define NUM_MODULE_PARAMS		1

typedef enum  { STATE_OFF, STATE_ON, STATE_PWM } Relay_state_t; 

/* H01R0_Status Type Definition */  
typedef enum 
{
	H0FR6_OK = 0,
	H0FR6_ERR_UnknownMessage = 1,
	H0FR6_ERR_Wrong_Value = 2,
	H0FR6_ERROR = 255
} Module_Status;

/* Indicator LED */
#if defined(H0FR1) || defined(H0FR7)
	#define _IND_LED_PORT		GPIOA
	#define _IND_LED_PIN		GPIO_PIN_11
#endif
#ifdef H0FR6
	#define _IND_LED_PORT		GPIOC
	#define _IND_LED_PIN		GPIO_PIN_14
#endif

/* Export UART variables */
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

/* Define UART Init prototypes */
extern void MX_USART1_UART_Init(void);
extern void MX_USART2_UART_Init(void);
extern void MX_USART3_UART_Init(void);
extern void MX_USART5_UART_Init(void);
extern void MX_USART6_UART_Init(void);

extern Relay_state_t Relay_State; 
extern uint8_t RelayindMode;
	
/* -----------------------------------------------------------------------
	|		        		    	APIs	 							|									 	|
   ----------------------------------------------------------------------- 
*/

extern Module_Status Relay_on(uint32_t timeout);
extern Module_Status Relay_off(void);
extern Module_Status Relay_toggle(void);
#if defined(H0FR1) || defined(H0FR7)
	extern Module_Status Relay_PWM(float dutyCycle);
#endif
#ifdef H0FR7
	extern void Read_Current(float *result);
#endif

/* -----------------------------------------------------------------------
	|			    			 Commands								|								 	|
   ----------------------------------------------------------------------- 
*/

extern const CLI_Command_Definition_t onCommandDefinition;
extern const CLI_Command_Definition_t offCommandDefinition;
extern const CLI_Command_Definition_t toggleCommandDefinition;
extern const CLI_Command_Definition_t ledModeCommandDefinition;
#if defined(H0FR1) || defined(H0FR7)
	extern const CLI_Command_Definition_t pwmCommandDefinition;
#endif

#endif /* H0FR6_H */

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
