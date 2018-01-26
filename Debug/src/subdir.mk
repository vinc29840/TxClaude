################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/adc.c \
../src/dma.c \
../src/gpio.c \
../src/i2c.c \
../src/main.c \
../src/spi.c \
../src/stm32f1xx_hal_msp.c \
../src/stm32f1xx_it.c \
../src/syscalls.c \
../src/system_stm32f1xx.c \
../src/u8g_com_arm_stm32.c \
../src/usart.c 

OBJS += \
./src/adc.o \
./src/dma.o \
./src/gpio.o \
./src/i2c.o \
./src/main.o \
./src/spi.o \
./src/stm32f1xx_hal_msp.o \
./src/stm32f1xx_it.o \
./src/syscalls.o \
./src/system_stm32f1xx.o \
./src/u8g_com_arm_stm32.o \
./src/usart.o 

C_DEPS += \
./src/adc.d \
./src/dma.d \
./src/gpio.d \
./src/i2c.d \
./src/main.d \
./src/spi.d \
./src/stm32f1xx_hal_msp.d \
./src/stm32f1xx_it.d \
./src/syscalls.d \
./src/system_stm32f1xx.d \
./src/u8g_com_arm_stm32.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DDEBUG -DSTM32F103xB -DUSE_HAL_DRIVER -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc/Legacy" -I"C:/Users/VINC_MSI/workspace/test/inc" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/device" -I"C:/Users/VINC_MSI/workspace/test/CMSIS/core" -I"C:/Users/VINC_MSI/workspace/test/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


