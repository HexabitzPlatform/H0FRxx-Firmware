################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/startup_stm32f091xc.s 

C_SRCS += \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_adc.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_dma.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_gpio.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_it.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_rtc.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_timers.c \
C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_uart.c 

OBJS += \
./H0FR6/H0FR6.o \
./H0FR6/H0FR6_adc.o \
./H0FR6/H0FR6_dma.o \
./H0FR6/H0FR6_gpio.o \
./H0FR6/H0FR6_it.o \
./H0FR6/H0FR6_rtc.o \
./H0FR6/H0FR6_timers.o \
./H0FR6/H0FR6_uart.o \
./H0FR6/startup_stm32f091xc.o 

S_DEPS += \
./H0FR6/startup_stm32f091xc.d 

C_DEPS += \
./H0FR6/H0FR6.d \
./H0FR6/H0FR6_adc.d \
./H0FR6/H0FR6_dma.d \
./H0FR6/H0FR6_gpio.d \
./H0FR6/H0FR6_it.d \
./H0FR6/H0FR6_rtc.d \
./H0FR6/H0FR6_timers.d \
./H0FR6/H0FR6_uart.d 


# Each subdirectory must supply rules for building sources it contributes
H0FR6/H0FR6.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_adc.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_adc.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_dma.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_dma.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_gpio.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_gpio.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_it.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_it.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_rtc.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_rtc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_rtc.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_timers.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_timers.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/H0FR6_uart.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/H0FR6_uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=1' -DH0FR1 -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"H0FR6/H0FR6_uart.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
H0FR6/startup_stm32f091xc.o: C:/Users/Root/Desktop/Current\ work/H0FRxx-Firmware/H0FR6/startup_stm32f091xc.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -c -x assembler-with-cpp -MMD -MP -MF"H0FR6/startup_stm32f091xc.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@" "$<"

