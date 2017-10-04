/*
    BitzOS (BOS) V0.1.1 - Copyright (C) 2017 Hexabitz
    All rights reserved
		
    File Name     : H09R0.h
    Description   : Header file for module H09R0.
										Solid state relay (AQH3213A) 
*/
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef H09R0_H
#define H09R0_H

/* Includes ------------------------------------------------------------------*/
#include "BOS.h"
#include "H09R0_uart.h"	
#include "H09R0_gpio.h"	
#include "H09R0_dma.h"	
	
	
/* Exported definitions -------------------------------------------------------*/

#define	modulePN		_H09R0

/* Port-related definitions */
#define	NumOfPorts		5
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
#define	USART1_TX_PORT	GPIOA
#define	USART1_RX_PORT	GPIOA
#define	USART1_AF				GPIO_AF1_USART1

#define	USART2_TX_PIN		GPIO_PIN_2
#define	USART2_RX_PIN		GPIO_PIN_3
#define	USART2_TX_PORT	GPIOA
#define	USART2_RX_PORT	GPIOA
#define	USART2_AF				GPIO_AF1_USART2

#define	USART3_TX_PIN		GPIO_PIN_10
#define	USART3_RX_PIN		GPIO_PIN_11
#define	USART3_TX_PORT	GPIOB
#define	USART3_RX_PORT	GPIOB
#define	USART3_AF				GPIO_AF4_USART3

#define	USART5_TX_PIN		GPIO_PIN_3
#define	USART5_RX_PIN		GPIO_PIN_4
#define	USART5_TX_PORT	GPIOB
#define	USART5_RX_PORT	GPIOB
#define	USART5_AF				GPIO_AF4_USART5

#define	USART6_TX_PIN		GPIO_PIN_4
#define	USART6_RX_PIN		GPIO_PIN_5
#define	USART6_TX_PORT	GPIOA
#define	USART6_RX_PORT	GPIOA
#define	USART6_AF				GPIO_AF5_USART6

/* Module-specific Definitions */
#define	_SSR_PIN						GPIO_PIN_0
#define	_SSR_PORT						GPIOB
#define _SSR_TIM_CH					TIM_CHANNEL_3
#define _SSR_GPIO_CLK()			__GPIOB_CLK_ENABLE();
#define PWM_TIMER_CLOCK			16000000
#define SSR_PWM_DEF_FREQ				24000
#define SSR_PWM_DEF_PERIOD			((float) (1/SSR_PWM_FREQ) )
	
typedef enum  { STATE_OFF, STATE_ON, STATE_PWM } SSR_state_t; 

/* H01R0_Status Type Definition */  
typedef enum 
{
  H09R0_OK = 0,
	H09R0_ERR_UnknownMessage = 1,
	H09R0_ERR_Wrong_Value = 2,
	H09R0_ERROR = 255
} Module_Status;

/* Indicator LED */
#define _IND_LED_PORT		GPIOC
#define _IND_LED_PIN		GPIO_PIN_14


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

extern SSR_state_t SSR_State; 
extern uint8_t SSRindMode;

/* -----------------------------------------------------------------------
	|														Message Codes	 														 	|
   ----------------------------------------------------------------------- 
*/

#define	CODE_H09R0_ON							900
#define	CODE_H09R0_OFF						901
#define	CODE_H09R0_TOGGLE					902
#define	CODE_H09R0_PWM						903

	
/* -----------------------------------------------------------------------
	|																APIs	 																 	|
   ----------------------------------------------------------------------- 
*/

extern Module_Status SSR_on(uint32_t timeout);
extern Module_Status SSR_off(void);
extern Module_Status SSR_toggle(void);
extern Module_Status SSR_PWM(float dutyCycle);

/* -----------------------------------------------------------------------
	|															Commands																 	|
   ----------------------------------------------------------------------- 
*/

extern const CLI_Command_Definition_t onCommandDefinition;
extern const CLI_Command_Definition_t offCommandDefinition;
extern const CLI_Command_Definition_t toggleCommandDefinition;
extern const CLI_Command_Definition_t ledModeCommandDefinition;
extern const CLI_Command_Definition_t pwmCommandDefinition;


#endif /* H09R0_H */

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
