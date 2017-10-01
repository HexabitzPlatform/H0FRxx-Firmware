/*
    BitzOS (BOS) V0.1.1 - Copyright (C) 2017 Hexabitz
    All rights reserved

    File Name     : H09R0.c
    Description   : Source code for module H09R0.
										Solid state relay (AQH3213A) 
		
		Required MCU resources : 
		
			>> USARTs 1,2,3,5,6 for module ports.
			>> Timer 3 (Ch3) for SSR PWM.
			>> GPIOB 0 for SSR.
			
*/
	
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"


/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

TIM_HandleTypeDef htim3;

SSR_state_t SSR_State = STATE_OFF, SSR_OldState = STATE_ON; uint8_t SSRindMode = 0;
uint32_t temp32; float SSR_OldDC;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/	
void SSRTimerCallback( TimerHandle_t xTimer );
Module_Status Set_SSR_PWM(uint32_t freq, float dutycycle);
void TIM3_Init(void);
void TIM3_DeInit(void);

/* Create CLI commands --------------------------------------------------------*/

portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE offCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE ledModeCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );

/* CLI command structure : on */
const CLI_Command_Definition_t onCommandDefinition =
{
	( const int8_t * ) "on", /* The command string to type. */
	( const int8_t * ) "(H09R0) on:\r\n Turn solid state relay on with a timeout (ms) (1st par.). Use 'inf' to turn on constantly\r\n\r\n",
	onCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : off */
const CLI_Command_Definition_t offCommandDefinition =
{
	( const int8_t * ) "off", /* The command string to type. */
	( const int8_t * ) "(H09R0) off:\r\n Turn solid state relay off\r\n\r\n",
	offCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : toggle */
const CLI_Command_Definition_t toggleCommandDefinition =
{
	( const int8_t * ) "toggle", /* The command string to type. */
	( const int8_t * ) "(H09R0) toggle:\r\n Toggle solid state relay\r\n\r\n",
	toggleCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : ledMode */
const CLI_Command_Definition_t ledModeCommandDefinition =
{
	( const int8_t * ) "ledMode", /* The command string to type. */
	( const int8_t * ) "(H09R0) ledMode:\r\n Set solid state relay indicator LED mode ('on' or 'off') (1st par.)\r\n\r\n",
	ledModeCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|												 Private Functions	 														|
   ----------------------------------------------------------------------- 
*/

/* --- H09R0 module initialization --- 
*/
void Module_Init(void)
{	
	
	/* Array ports */
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART5_UART_Init();
	MX_USART6_UART_Init();
	
	/* SSR PWM Timer - define in Set_SSR_PWM */
	//TIM3_Init();
	
	/* SSR GPIO */
	SSR_Init();
  
}

/*-----------------------------------------------------------*/

/* --- H09R0 message processing task. 
*/
Module_Status Module_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst)
{
	Module_Status result = H09R0_OK; 
	
	switch (code)
	{
		case CODE_H09R0_ON :
			temp32 = ( (uint32_t) cMessage[port-1][4] << 24 ) + ( (uint32_t) cMessage[port-1][5] << 16 ) + ( (uint32_t) cMessage[port-1][6] << 8 ) + cMessage[port-1][7];						
			SSR_on(temp32);
			break;
		
		case CODE_H09R0_OFF :
			SSR_off();
			break;
		
		case CODE_H09R0_TOGGLE :
			SSR_toggle();
			break;
			
		default:
			result = H09R0_ERR_UnknownMessage;
			break;
	}			

	return result;	
}

/*-----------------------------------------------------------*/

/* --- Get the port for a given UART. 
*/
uint8_t GetPort(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART5)
			return P1;
	else if (huart->Instance == USART2)
			return P2;
	else if (huart->Instance == USART6)
			return P3;
	else if (huart->Instance == USART3)
			return P4;
	else if (huart->Instance == USART1)
			return P5;
		
	return 0;
}

/*-----------------------------------------------------------*/

/* --- Solid State Relay timer callback --- 
*/
void SSRTimerCallback( TimerHandle_t xTimer )
{
	SSR_off();
}

/*-----------------------------------------------------------*/	

/* TIM3 init function - SSR PWM Timer 16-bit 
*/
void TIM3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	
	/* Peripheral clock enable */
  __TIM3_CLK_ENABLE();
	
	/**TIM3 GPIO Configuration    
	*/
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Pin = _SSR_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_SSR_PORT, &GPIO_InitStruct);
	
	/* Peripheral interrupt init */
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	/* Timer base configuration - 1 MHz */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = (uint32_t)(HAL_RCC_GetSysClockFreq()/PWM_TIMER_CLOCK) - 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

	/* Timer PWM configuration */
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);
  HAL_TIM_PWM_Init(&htim3);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

	/* Timer PWM channels */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _SSR_TIM_CH);

}

/*-----------------------------------------------------------*/	

/* TIM3 Deinit function - SSR PWM Timer 16-bit 
*/
void TIM3_DeInit(void)
{
	HAL_NVIC_DisableIRQ(TIM3_IRQn);
	HAL_TIM_Base_DeInit(&htim3);
	HAL_TIM_PWM_DeInit(&htim3);
	__TIM3_CLK_DISABLE();
}

/*-----------------------------------------------------------*/

/* --- Set SSR PWM frequency and dutycycle ---
*/
Module_Status Set_SSR_PWM(uint32_t freq, float dutycycle)
{	
	Module_Status result = H09R0_OK;	
	uint32_t ARR = PWM_TIMER_CLOCK / freq;
	
	if (SSR_State != STATE_PWM)	TIM3_Init();
	
	/* PWM period */
	htim3.Instance->ARR = ARR - 1;
	
	/* PWM duty cycle */
	htim3.Instance->CCR3 = ((float)dutycycle/100.0f) * ARR;

	if (HAL_TIM_PWM_Start(&htim3, _SSR_TIM_CH) != HAL_OK)	
		return	H09R0_ERROR;
	
	return result;
}

/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|																APIs	 																 	|
   ----------------------------------------------------------------------- 
*/

/* --- Turn on the solid state relay ---
*/
Module_Status SSR_on(uint32_t timeout)
{	
	Module_Status result = H09R0_OK;	
	TimerHandle_t xTimer = NULL;

	/* Turn off PWM and re-initialize GPIO if needed */
	if (SSR_State == STATE_PWM) 
	{
		HAL_TIM_PWM_Stop(&htim3, _SSR_TIM_CH);
		TIM3_DeInit();
		SSR_Init();
	}	
	
	/* Turn on */
	HAL_GPIO_WritePin(_SSR_PORT,_SSR_PIN,GPIO_PIN_SET);
	
	/* Indicator LED */
	if (SSRindMode) IND_ON();
	
	/* Timeout */
	if (timeout != portMAX_DELAY) {
		/* Create a timeout timer */
		xTimer = xTimerCreate( "SSRTimer", pdMS_TO_TICKS(timeout), pdFALSE, ( void * ) 1, SSRTimerCallback );	
		/* Start the timeout timer */
		xTimerStart( xTimer, portMAX_DELAY );
	}
	
	/* Update SSR state */
	SSR_State = STATE_ON; SSR_OldState = SSR_State;	
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Turn off the solid state relay ---
*/
Module_Status SSR_off(void)
{	
	Module_Status result = H09R0_OK;	
	
	/* Turn off PWM and re-initialize GPIO if needed */
	if (SSR_State == STATE_PWM) 
	{
		HAL_TIM_PWM_Stop(&htim3, _SSR_TIM_CH);
		TIM3_DeInit();
		SSR_Init();
	}	
	
	/* Turn off */
	HAL_GPIO_WritePin(_SSR_PORT,_SSR_PIN,GPIO_PIN_RESET);
	
	/* Indicator LED */
	if (SSRindMode) IND_OFF();

	/* Update SSR state */
	SSR_State = STATE_OFF;
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Toggle the solid state relay ---
*/
Module_Status SSR_toggle(void)
{	
	Module_Status result = H09R0_OK;	
	
	if (SSR_State) 
	{
		result = SSR_off();
	}
	else 
	{
		if (SSR_OldState == STATE_ON)
			result = SSR_on(portMAX_DELAY);
		else if (SSR_OldState == STATE_PWM)
			result = SSR_PWM(SSR_OldDC);
	}
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Turn-on SSR with pulse-width modulation (PWM) ---
				dutyCycle: PWM duty cycle in precentage (0 to 100)
*/
Module_Status SSR_PWM(float dutyCycle)
{	
	Module_Status result = H09R0_OK;	
	
	if ( dutyCycle < 0 || dutyCycle > 100 )
		return H09R0_ERR_Wrong_Value;
	
	/* Start the PWM */
	result = Set_SSR_PWM(SSR_PWM_DEF_FREQ, dutyCycle);
	
	if (result == H09R0_OK)
	{
		SSR_OldDC = dutyCycle;
		/* Update SSR state */
		SSR_State = STATE_PWM; SSR_OldState = SSR_State;			
		/* Indicator LED */
		if (SSRindMode) IND_ON();
	}
	
	return result;
}

/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|															Commands																 	|
   ----------------------------------------------------------------------- 
*/

portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H09R0_OK;
	
	int8_t *pcParameterString1; portBASE_TYPE xParameterStringLength1 = 0; 
	uint32_t timeout = 0;
	static const int8_t *pcOKMessage = ( int8_t * ) "Solid state relay is turned on with timeout %d ms\r\n";
	static const int8_t *pcOKMessageInf = ( int8_t * ) "Solid state relay is turned on without timeout\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength1	/* Store the parameter string length. */
								);
	
	if (!strcmp( ( char * ) pcParameterString1, "inf") || !strcmp( ( char * ) pcParameterString1, "INF"))
		timeout = portMAX_DELAY;
	else
		timeout = ( uint32_t ) atol( ( char * ) pcParameterString1 );
	
	result = SSR_on(timeout);	
	
	/* Respond to the command */
	if (result == H09R0_OK) {
		if (timeout != portMAX_DELAY) {
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOKMessage, timeout);
		} else {
			strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOKMessageInf);
		}
	}
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE offCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H09R0_OK;
	
	static const int8_t *pcMessage = ( int8_t * ) "Solid state relay is turned off\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	result = SSR_off();
	
	/* Respond to the command */
	if (result == H09R0_OK) {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcMessage);
	}
		
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H09R0_OK;
	
	static const int8_t *pcOK1Message = ( int8_t * ) "Solid state relay is turned on\r\n";
	static const int8_t *pcOK0Message = ( int8_t * ) "Solid state relay is turned off\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	result = SSR_toggle();	
	
	/* Respond to the command */
	if (result == H09R0_OK) {
		if (SSR_State) {
			strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK1Message);
		} else {
			strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK0Message);
		}
	}
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE ledModeCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	int8_t *pcParameterString1; portBASE_TYPE xParameterStringLength1 = 0; 
	
	static const int8_t *pcOK1Message = ( int8_t * ) "Solid state relay indicator LED is enabled\r\n";
	static const int8_t *pcOK0Message = ( int8_t * ) "Solid state relay indicator LED is disabled\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	/* Obtain the 1st parameter string. */
	pcParameterString1 = ( int8_t * ) FreeRTOS_CLIGetParameter
								(
									pcCommandString,		/* The command string itself. */
									1,						/* Return the first parameter. */
									&xParameterStringLength1	/* Store the parameter string length. */
								);
	if (!strcmp( ( char * ) pcParameterString1, "on") || !strcmp( ( char * ) pcParameterString1, "ON"))
		SSRindMode = 1;
	else if (!strcmp( ( char * ) pcParameterString1, "off") || !strcmp( ( char * ) pcParameterString1, "OFF"))
		SSRindMode = 0;
	
	/* Respond to the command */
	if (SSRindMode) {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK1Message);
	} else {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK0Message);
	}

	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/


/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
