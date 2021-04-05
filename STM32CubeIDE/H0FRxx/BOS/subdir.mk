################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_CLI.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_CLIcommands.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_dma.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_eeprom.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_freertos.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_inputs.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_messaging.c \
W:/Current\ work/H0FRxx-Firmware/BOS/BOS_msgparser.c 

OBJS += \
./BOS/BOS.o \
./BOS/BOS_CLI.o \
./BOS/BOS_CLIcommands.o \
./BOS/BOS_dma.o \
./BOS/BOS_eeprom.o \
./BOS/BOS_freertos.o \
./BOS/BOS_inputs.o \
./BOS/BOS_messaging.o \
./BOS/BOS_msgparser.o 

C_DEPS += \
./BOS/BOS.d \
./BOS/BOS_CLI.d \
./BOS/BOS_CLIcommands.d \
./BOS/BOS_dma.d \
./BOS/BOS_eeprom.d \
./BOS/BOS_freertos.d \
./BOS/BOS_inputs.d \
./BOS/BOS_messaging.d \
./BOS/BOS_msgparser.d 


# Each subdirectory must supply rules for building sources it contributes
BOS/BOS.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_CLI.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_CLI.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_CLI.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_CLIcommands.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_CLIcommands.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_CLIcommands.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_dma.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_dma.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_eeprom.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_eeprom.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_eeprom.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_freertos.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_freertos.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_freertos.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_inputs.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_inputs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_inputs.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_messaging.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_messaging.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_messaging.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"
BOS/BOS_msgparser.o: W:/Current\ work/H0FRxx-Firmware/BOS/BOS_msgparser.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=c99 -g -DUSE_HAL_DRIVER -DH0FR1 -DDEBUG -DSTM32F091xB -DSTM32F091xC '-D_module=2' -DH0FR7 -c -I../../Thirdparty/CMSIS/Include -I../../Thirdparty/CMSIS/Device/ST/STM32F0xx/Include -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Thirdparty/STM32F0xx_HAL_Driver/Inc -I../../Thirdparty/Middleware/FreeRTOS/Source/include -I../../Thirdparty/Middleware/FreeRTOS/Source/portable/GCC/ARM_CM0 -I../../Thirdparty/Middleware/FreeRTOS/Source/CMSIS_RTOS -I../../BOS -I../../User -I../../H0FR6 -O1 -ffunction-sections -fdata-sections -fstack-usage -MMD -MP -MF"BOS/BOS_msgparser.d" -MT"$@"  -mfloat-abi=soft -mthumb -o "$@"

