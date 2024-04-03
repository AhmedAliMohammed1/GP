################################################################################
# Automatically-generated file. Do not edit!
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
HAL/DMS.o: ../HAL/DMS.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/DMS.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/KEYPAD.o: ../HAL/KEYPAD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/KEYPAD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LCD.o: ../HAL/LCD.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LUNA_LIDAR.o: ../HAL/LUNA_LIDAR.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LUNA_LIDAR.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/SPI_EEPROM.o: ../HAL/SPI_EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/SPI_EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/Servo.o: ../HAL/Servo.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/Servo.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/TFT.o: ../HAL/TFT.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/TFT.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

