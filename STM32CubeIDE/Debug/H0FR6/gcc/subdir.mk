################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
D:/Hexabitz/Hexabitz\ Modules\ firmware/H0FRxx/H0FR6/gcc/startup_stm32f091xc.s 

OBJS += \
./H0FR6/gcc/startup_stm32f091xc.o 


# Each subdirectory must supply rules for building sources it contributes
H0FR6/gcc/startup_stm32f091xc.o: D:/Hexabitz/Hexabitz\ Modules\ firmware/H0FRxx/H0FR6/gcc/startup_stm32f091xc.s
	arm-none-eabi-gcc -mcpu=cortex-m0 -g3 -c -x assembler-with-cpp  -mfloat-abi=soft -mthumb -o "$@" "$<"
