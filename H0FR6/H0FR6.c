/*
    BitzOS (BOS) V0.2.4 - Copyright (C) 2017-2021 Hexabitz
    All rights reserved

    File Name     : H0FR6.c
    Description   : Source code for module H0FR1 SPDT mechanical DC relay
										and module H0FR6 Solid state AC relay (AQH3213A).
										 
		
		Required MCU resources : 
		
			>> USARTs 1,2,3,5,6 for module ports.
			>> Timer 3 (Ch3) for Relay PWM (H0FR6 only).
			>> GPIOB 0 for Relay.
			
*/
	
/* Includes ------------------------------------------------------------------*/
#include "BOS.h"


/* Define UART variables */
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart6;

/* Module exported parameters ------------------------------------------------*/
module_param_t modParam[NUM_MODULE_PARAMS] = {{.paramPtr=NULL, .paramFormat=FMT_FLOAT, .paramName=""}};

/* Exported variables */
extern FLASH_ProcessTypeDef pFlash;
extern uint8_t numOfRecordedSnippets;


TIM_HandleTypeDef htim3;
TimerHandle_t xTimerRelay = NULL;
	
Relay_state_t Relay_state = STATE_OFF, Relay_Oldstate = STATE_ON; uint8_t RelayindMode = 0;
uint32_t temp32; float tempFloat, Relay_OldDC;

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/	
void RelayTimerCallback( TimerHandle_t xTimerRelay );
Module_Status Set_Relay_PWM(uint32_t freq, float dutycycle);
void TIM3_Init(void);
void TIM3_DeInit(void);

/* Create CLI commands --------------------------------------------------------*/

portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE offCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
portBASE_TYPE ledModeCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
#ifdef H0FR6
	portBASE_TYPE pwmCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
#endif

/* CLI command structure : on */
const CLI_Command_Definition_t onCommandDefinition =
{
	( const int8_t * ) "on", /* The command string to type. */
	( const int8_t * ) "on:\r\n Turn solid state relay on with a timeout (ms) (1st par.). Use 'inf' to turn on constantly\r\n\r\n",
	onCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : off */
const CLI_Command_Definition_t offCommandDefinition =
{
	( const int8_t * ) "off", /* The command string to type. */
	( const int8_t * ) "off:\r\n Turn solid state relay off\r\n\r\n",
	offCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : toggle */
const CLI_Command_Definition_t toggleCommandDefinition =
{
	( const int8_t * ) "toggle", /* The command string to type. */
	( const int8_t * ) "toggle:\r\n Toggle solid state relay\r\n\r\n",
	toggleCommand, /* The function to run. */
	0 /* No parameters are expected. */
};
/*-----------------------------------------------------------*/
/* CLI command structure : ledMode */
const CLI_Command_Definition_t ledModeCommandDefinition =
{
	( const int8_t * ) "ledmode", /* The command string to type. */
	( const int8_t * ) "ledMode:\r\n Set solid state relay indicator LED mode ('on' or 'off') (1st par.)\r\n\r\n",
	ledModeCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
/*-----------------------------------------------------------*/
#ifdef H0FR6
/* CLI command structure : pwm */
const CLI_Command_Definition_t pwmCommandDefinition =
{
	( const int8_t * ) "pwm", /* The command string to type. */
	( const int8_t * ) "pwm:\r\n Control the solid state relay with pulse-width modulation (PWM) signal with a percentage duty cycle (0-100) (1st par.)\r\n\r\n",
	pwmCommand, /* The function to run. */
	1 /* One parameter is expected. */
};
#endif
/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|												 Private Functions	 														|
   ----------------------------------------------------------------------- 
*/

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_USART3;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);
	
	__HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_HSE_DIV32;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	

	__SYSCFG_CLK_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
	
}

/*-----------------------------------------------------------*/
/* --- Save array topology and Command Snippets in Flash RO --- 
*/
uint8_t SaveToRO(void)
{
	BOS_Status result = BOS_OK; 
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	uint16_t add = 2, temp = 0;
	uint8_t snipBuffer[sizeof(snippet_t)+1] = {0};
	
	HAL_FLASH_Unlock();
	
	/* Erase RO area */
	FLASH_PageErase(RO_START_ADDRESS);
	FlashStatus = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 
	if(FlashStatus != HAL_OK) {
		return pFlash.ErrorCode;
	} else {			
		/* Operation is completed, disable the PER Bit */
		CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	}	
	
	/* Save number of modules and myID */
	if (myID)
	{
		temp = (uint16_t) (N<<8) + myID;
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, RO_START_ADDRESS, temp);
		FlashStatus = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 
		if (FlashStatus != HAL_OK) {
			return pFlash.ErrorCode;
		} else {
			/* If the program operation is completed, disable the PG Bit */
			CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
		}			
	
	/* Save topology */
		for(uint8_t i=1 ; i<=N ; i++)
		{
			for(uint8_t j=0 ; j<=MaxNumOfPorts ; j++)
			{
				if (array[i-1][0]) {
					HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, RO_START_ADDRESS+add, array[i-1][j]);
					add += 2;
					FlashStatus = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 
					if (FlashStatus != HAL_OK) {
						return pFlash.ErrorCode;
					} else {
						/* If the program operation is completed, disable the PG Bit */
						CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
					}		
				}				
			}
		}
	}
	
	// Save Command Snippets
	int currentAdd = RO_MID_ADDRESS;
	for(uint8_t s=0 ; s<numOfRecordedSnippets ; s++) 
	{
		if (snippets[s].cond.conditionType) 
		{
			snipBuffer[0] = 0xFE;		// A marker to separate Snippets
			memcpy( (uint8_t *)&snipBuffer[1], (uint8_t *)&snippets[s], sizeof(snippet_t));
			// Copy the snippet struct buffer (20 x numOfRecordedSnippets). Note this is assuming sizeof(snippet_t) is even.
			for(uint8_t j=0 ; j<(sizeof(snippet_t)/2) ; j++)
			{		
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, currentAdd, *(uint16_t *)&snipBuffer[j*2]);
				FlashStatus = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 
				if (FlashStatus != HAL_OK) {
					return pFlash.ErrorCode;
				} else {
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
					currentAdd += 2;
				}				
			}			
			// Copy the snippet commands buffer. Always an even number. Note the string termination char might be skipped
			for(uint8_t j=0 ; j<((strlen(snippets[s].cmd)+1)/2) ; j++)
			{
				HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, currentAdd, *(uint16_t *)(snippets[s].cmd+j*2));
				FlashStatus = FLASH_WaitForLastOperation((uint32_t)HAL_FLASH_TIMEOUT_VALUE); 
				if (FlashStatus != HAL_OK) {
					return pFlash.ErrorCode;
				} else {
					/* If the program operation is completed, disable the PG Bit */
					CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
					currentAdd += 2;
				}				
			}				
		}	
	}
	
	HAL_FLASH_Lock();
	
	return result;
}

/* --- Clear array topology in SRAM and Flash RO --- 
*/
uint8_t ClearROtopology(void)
{
	// Clear the array 
	memset(array, 0, sizeof(array));
	N = 1; myID = 0;
	
	return SaveToRO();
}
/* --- H0FR6 module initialization --- 
*/
void Module_Init(void)
{	
	
	/* Array ports */
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART5_UART_Init();
	MX_USART6_UART_Init();
	
	/* Create a timeout timer for Relay_on() API */
	xTimerRelay = xTimerCreate( "RelayTimer", pdMS_TO_TICKS(1000), pdFALSE, ( void * ) 1, RelayTimerCallback );	
	
	/* Relay GPIO */
	Relay_Init();
  
}

/*-----------------------------------------------------------*/

/* --- H0FR6 message processing task. 
*/
Module_Status Module_MessagingTask(uint16_t code, uint8_t port, uint8_t src, uint8_t dst, uint8_t shift)
{
	Module_Status result = H0FR6_OK; 
	
	switch (code)
	{
		case CODE_H0FR6_ON :
			temp32 = ( (uint32_t) cMessage[port-1][shift] << 24 ) + ( (uint32_t) cMessage[port-1][1+shift] << 16 ) + ( (uint32_t) cMessage[port-1][2+shift] << 8 ) + cMessage[port-1][3+shift];						
			Relay_on(temp32);
			break;
		
		case CODE_H0FR6_OFF :
			Relay_off();
			break;
		
		case CODE_H0FR6_TOGGLE :
			Relay_toggle();
			break;

#ifdef H0FR6		
		case CODE_H0FR6_PWM :
			tempFloat = (float)( ((uint64_t)cMessage[port-1][shift]<<24) + ((uint64_t)cMessage[port-1][1+shift]<<16) + ((uint64_t)cMessage[port-1][2+shift]<<8) + ((uint64_t)cMessage[port-1][3+shift]) );
			Relay_PWM(tempFloat);
			break;
#endif
			
		default:
			result = H0FR6_ERR_UnknownMessage;
			break;
	}			

	return result;	
}

/*-----------------------------------------------------------*/

/* --- Register this module CLI Commands 
*/
void RegisterModuleCLICommands(void)
{
	FreeRTOS_CLIRegisterCommand( &onCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &offCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &toggleCommandDefinition );
	FreeRTOS_CLIRegisterCommand( &ledModeCommandDefinition );
#ifdef H0FR6
	FreeRTOS_CLIRegisterCommand( &pwmCommandDefinition );
#endif
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
void RelayTimerCallback( TimerHandle_t xTimerRelay )
{
	Relay_off();
}

/*-----------------------------------------------------------*/	
#ifdef H0FR6
/* TIM3 init function - Relay PWM Timer 16-bit 
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
	GPIO_InitStruct.Pin = _Relay_PIN;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM3;
	HAL_GPIO_Init(_Relay_PORT, &GPIO_InitStruct);
	
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
  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, _Relay_TIM_CH);

}

/*-----------------------------------------------------------*/	

/* TIM3 Deinit function - Relay PWM Timer 16-bit 
*/
void TIM3_DeInit(void)
{
	HAL_NVIC_DisableIRQ(TIM3_IRQn);
	HAL_TIM_Base_DeInit(&htim3);
	HAL_TIM_PWM_DeInit(&htim3);
	__TIM3_CLK_DISABLE();
}

/*-----------------------------------------------------------*/

/* --- Set Relay PWM frequency and dutycycle ---
*/
Module_Status Set_Relay_PWM(uint32_t freq, float dutycycle)
{	
	Module_Status result = H0FR6_OK;	
	uint32_t ARR = PWM_TIMER_CLOCK / freq;
	
	if (Relay_state != STATE_PWM)	TIM3_Init();
	
	/* PWM period */
	htim3.Instance->ARR = ARR - 1;
	
	/* PWM duty cycle */
	htim3.Instance->CCR3 = ((float)dutycycle/100.0f) * ARR;

	if (HAL_TIM_PWM_Start(&htim3, _Relay_TIM_CH) != HAL_OK)	
		return	H0FR6_ERROR;
	
	return result;
}
#endif
/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|																APIs	 																 	|
   ----------------------------------------------------------------------- 
*/

/* --- Turn on the solid state relay ---
*/
Module_Status Relay_on(uint32_t timeout)
{	
	Module_Status result = H0FR6_OK;	

#ifdef H0FR6
	/* Turn off PWM and re-initialize GPIO if needed */
	if (Relay_state == STATE_PWM) 
	{
		HAL_TIM_PWM_Stop(&htim3, _Relay_TIM_CH);
		TIM3_DeInit();
		Relay_Init();
	}	
#endif
	
	/* Turn on */
	HAL_GPIO_WritePin(_Relay_PORT,_Relay_PIN,GPIO_PIN_SET);
	
	/* Indicator LED */
	if (RelayindMode) IND_ON();
	
	/* Timeout */
	if (timeout != portMAX_DELAY) 
	{		
		/* Stop the timer if it's already running */
		if( xTimerIsTimerActive(xTimerRelay) ) xTimerStop( xTimerRelay, 100 );
		/* Update timer timeout - This also restarts the timer */
		xTimerChangePeriod( xTimerRelay, pdMS_TO_TICKS(timeout), 100 );
	}
	
	/* Update Relay state */
	Relay_state = STATE_ON; Relay_Oldstate = Relay_state;	
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Turn off the solid state relay ---
*/
Module_Status Relay_off(void)
{	
	Module_Status result = H0FR6_OK;	

#ifdef H0FR6	
	/* Turn off PWM and re-initialize GPIO if needed */
	if (Relay_state == STATE_PWM) 
	{
		HAL_TIM_PWM_Stop(&htim3, _Relay_TIM_CH);
		TIM3_DeInit();
		Relay_Init();
	}	
#endif
	
	/* Turn off */
	HAL_GPIO_WritePin(_Relay_PORT,_Relay_PIN,GPIO_PIN_RESET);
	
	/* Indicator LED */
	if (RelayindMode) IND_OFF();

	/* Update Relay state */
	Relay_state = STATE_OFF;
	
	return result;
}

/*-----------------------------------------------------------*/

/* --- Toggle the solid state relay ---
*/
Module_Status Relay_toggle(void)
{	
	Module_Status result = H0FR6_OK;	
	
	if (Relay_state) 
	{
		result = Relay_off();
	}
	else 
	{
		if (Relay_Oldstate == STATE_ON)
			result = Relay_on(portMAX_DELAY);
	#ifdef H0FR6
		else if (Relay_Oldstate == STATE_PWM)
			result = Relay_PWM(Relay_OldDC);
	#endif
	}
	
	return result;
}

/*-----------------------------------------------------------*/
#ifdef H0FR6
/* --- Turn-on Relay with pulse-width modulation (PWM) ---
				dutyCycle: PWM duty cycle in precentage (0 to 100)
*/
Module_Status Relay_PWM(float dutyCycle)
{	
	Module_Status result = H0FR6_OK;	
	
	if ( dutyCycle < 0 || dutyCycle > 100 )
		return H0FR6_ERR_Wrong_Value;
	
	/* Start the PWM */
	result = Set_Relay_PWM(Relay_PWM_DEF_FREQ, dutyCycle);
	
	if (result == H0FR6_OK)
	{
		Relay_OldDC = dutyCycle;
		/* Update Relay state */
		Relay_state = STATE_PWM; Relay_Oldstate = Relay_state;			
		/* Indicator LED */
		if (RelayindMode) IND_ON();
	}
	
	return result;
}
#endif
/*-----------------------------------------------------------*/

/* -----------------------------------------------------------------------
	|															Commands																 	|
   ----------------------------------------------------------------------- 
*/

portBASE_TYPE onCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H0FR6_OK;
	
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
	
	result = Relay_on(timeout);	
	
	/* Respond to the command */
	if (result == H0FR6_OK) {
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
	Module_Status result = H0FR6_OK;
	
	static const int8_t *pcMessage = ( int8_t * ) "Solid state relay is turned off\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	result = Relay_off();
	
	/* Respond to the command */
	if (result == H0FR6_OK) {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcMessage);
	}
		
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/

portBASE_TYPE toggleCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H0FR6_OK;
	
	static const int8_t *pcOK1Message = ( int8_t * ) "Solid state relay is turned on\r\n";
	static const int8_t *pcOK0Message = ( int8_t * ) "Solid state relay is turned off\r\n";
	
	/* Remove compile time warnings about unused parameters, and check the
	write buffer is not NULL.  NOTE - for simplicity, this example assumes the
	write buffer length is adequate, so does not check for buffer overflows. */
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );
	
	result = Relay_toggle();	
	
	/* Respond to the command */
	if (result == H0FR6_OK) {
		if (Relay_state) {
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
		RelayindMode = 1;
	else if (!strcmp( ( char * ) pcParameterString1, "off") || !strcmp( ( char * ) pcParameterString1, "OFF"))
		RelayindMode = 0;
	
	/* Respond to the command */
	if (RelayindMode) {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK1Message);
	} else {
		strcpy( ( char * ) pcWriteBuffer, ( char * ) pcOK0Message);
	}

	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}

/*-----------------------------------------------------------*/
#ifdef H0FR6
portBASE_TYPE pwmCommand( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	Module_Status result = H0FR6_OK;
	
	int8_t *pcParameterString1; portBASE_TYPE xParameterStringLength1 = 0; 
	float dutycycle = 0;
	static const int8_t *pcOKMessage = ( int8_t * ) "Solid state relay is pulse-width modulated with %.1f%% duty cycle\r\n";
	static const int8_t *pcWrongValue = ( int8_t * ) "Wong duty cycle value. Acceptable range is 0 to 100\r\n";
	
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
	
	dutycycle = ( float ) atof( ( char * ) pcParameterString1 );
	
	if (dutycycle < 0.0f || dutycycle > 100.0f)
		result = H0FR6_ERR_Wrong_Value;
	else
		result = Relay_PWM(dutycycle);	
	
	/* Respond to the command */
	if (result == H0FR6_OK) {
			sprintf( ( char * ) pcWriteBuffer, ( char * ) pcOKMessage, dutycycle);
	} else if (result == H0FR6_ERR_Wrong_Value) {
			strcpy( ( char * ) pcWriteBuffer, ( char * ) pcWrongValue);
	}
	
	/* There is no more data to return after this single string, so return
	pdFALSE. */
	return pdFALSE;
}
#endif
/*-----------------------------------------------------------*/

/************************ (C) COPYRIGHT HEXABITZ *****END OF FILE****/
