################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f103xb.s 

OBJS += \
./startup/startup_stm32f103xb.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc/Legacy" -I"C:/Users/VINC_MSI/workspace/test/inc" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/device" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/core" -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


