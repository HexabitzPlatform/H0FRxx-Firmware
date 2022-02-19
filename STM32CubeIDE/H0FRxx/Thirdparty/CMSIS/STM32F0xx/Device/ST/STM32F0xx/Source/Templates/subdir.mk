################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Hexabitz\ release/H0FRxx/Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c 

OBJS += \
./Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.o 

C_DEPS += \
./Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.o: D:/Hexabitz\ release/H0FRxx/Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xC '-D_module=1' -DH0FR1 -c -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../BOS -I../../User -I../../H0FR6 -I../../Thirdparty/Middleware/STM32F0xx/FreeRTOS/Source/include -I../../Thirdparty/Middleware/STM32F0xx/FreeRTOS/Source/CMSIS_RTOS -I../../Thirdparty/CMSIS/STM32F0xx/Include -I../../Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Include -I../../Thirdparty/Middleware/STM32F0xx/FreeRTOS/Source/portable/GCC/ARM_CM0 -O2 -ffunction-sections -fstack-usage -MMD -MP -MF"Thirdparty/CMSIS/STM32F0xx/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

