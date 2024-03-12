################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DMS.c \
../HAL/KEYPAD.c \
../HAL/LCD.c \
../HAL/LUNA_LIDAR.c \
../HAL/SPI_EEPROM.c \
../HAL/Servo.c \
../HAL/TFT.c 

OBJS += \
./HAL/DMS.o \
./HAL/KEYPAD.o \
./HAL/LCD.o \
./HAL/LUNA_LIDAR.o \
./HAL/SPI_EEPROM.o \
./HAL/Servo.o \
./HAL/TFT.o 

C_DEPS += \
./HAL/DMS.d \
./HAL/KEYPAD.d \
./HAL/LCD.d \
./HAL/LUNA_LIDAR.d \
./HAL/SPI_EEPROM.d \
./HAL/Servo.d \
./HAL/TFT.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/medoo/Desktop/WorkSpace/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/medoo/Desktop/WorkSpace/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/medoo/Desktop/WorkSpace/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/medoo/Desktop/WorkSpace/Graduation_Project_Finall/HAL/inc" -I"C:/Users/medoo/Desktop/WorkSpace/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/DMS.cyclo ./HAL/DMS.d ./HAL/DMS.o ./HAL/DMS.su ./HAL/KEYPAD.cyclo ./HAL/KEYPAD.d ./HAL/KEYPAD.o ./HAL/KEYPAD.su ./HAL/LCD.cyclo ./HAL/LCD.d ./HAL/LCD.o ./HAL/LCD.su ./HAL/LUNA_LIDAR.cyclo ./HAL/LUNA_LIDAR.d ./HAL/LUNA_LIDAR.o ./HAL/LUNA_LIDAR.su ./HAL/SPI_EEPROM.cyclo ./HAL/SPI_EEPROM.d ./HAL/SPI_EEPROM.o ./HAL/SPI_EEPROM.su ./HAL/Servo.cyclo ./HAL/Servo.d ./HAL/Servo.o ./HAL/Servo.su ./HAL/TFT.cyclo ./HAL/TFT.d ./HAL/TFT.o ./HAL/TFT.su

.PHONY: clean-HAL

