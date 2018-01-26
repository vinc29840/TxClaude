################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fntsrc/u8g_font_courb10.c \
../src/fntsrc/u8g_font_profont12.c 

OBJS += \
./src/fntsrc/u8g_font_courb10.o \
./src/fntsrc/u8g_font_profont12.o 

C_DEPS += \
./src/fntsrc/u8g_font_courb10.d \
./src/fntsrc/u8g_font_profont12.d 


# Each subdirectory must supply rules for building sources it contributes
src/fntsrc/%.o: ../src/fntsrc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc/Legacy" -I"C:/Users/VINC_MSI/workspace/test/inc" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/device" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/core" -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


