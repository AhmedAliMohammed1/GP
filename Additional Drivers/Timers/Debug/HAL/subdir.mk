################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD.c \
../HAL/LCD.c \
../HAL/SPI_EEPROM.c \
../HAL/Servo_Motor.c 

OBJS += \
./HAL/KEYPAD.o \
./HAL/LCD.o \
./HAL/SPI_EEPROM.o \
./HAL/Servo_Motor.o 

C_DEPS += \
./HAL/KEYPAD.d \
./HAL/LCD.d \
./HAL/SPI_EEPROM.d \
./HAL/Servo_Motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/medoo/Desktop/WorkSpace/Timers/HAL/inc" -I"C:/Users/medoo/Desktop/WorkSpace/Timers/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/KEYPAD.cyclo ./HAL/KEYPAD.d ./HAL/KEYPAD.o ./HAL/KEYPAD.su ./HAL/LCD.cyclo ./HAL/LCD.d ./HAL/LCD.o ./HAL/LCD.su ./HAL/SPI_EEPROM.cyclo ./HAL/SPI_EEPROM.d ./HAL/SPI_EEPROM.o ./HAL/SPI_EEPROM.su ./HAL/Servo_Motor.cyclo ./HAL/Servo_Motor.d ./HAL/Servo_Motor.o ./HAL/Servo_Motor.su

.PHONY: clean-HAL

