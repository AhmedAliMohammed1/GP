################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC.c \
../MCAL/CAN.c \
../MCAL/EEPROM.c \
../MCAL/EXTI_Driver.c \
../MCAL/GPIO_Driver.c \
../MCAL/GP_Timers.c \
../MCAL/I2C.c \
../MCAL/RCC.c \
../MCAL/SPI.c \
../MCAL/Timer.c \
../MCAL/Timer1_8.c \
../MCAL/USART_Driver.c 

OBJS += \
./MCAL/ADC.o \
./MCAL/CAN.o \
./MCAL/EEPROM.o \
./MCAL/EXTI_Driver.o \
./MCAL/GPIO_Driver.o \
./MCAL/GP_Timers.o \
./MCAL/I2C.o \
./MCAL/RCC.o \
./MCAL/SPI.o \
./MCAL/Timer.o \
./MCAL/Timer1_8.o \
./MCAL/USART_Driver.o 

C_DEPS += \
./MCAL/ADC.d \
./MCAL/CAN.d \
./MCAL/EEPROM.d \
./MCAL/EXTI_Driver.d \
./MCAL/GPIO_Driver.d \
./MCAL/GP_Timers.d \
./MCAL/I2C.d \
./MCAL/RCC.d \
./MCAL/SPI.d \
./MCAL/Timer.d \
./MCAL/Timer1_8.d \
./MCAL/USART_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/ADC.o: ../MCAL/ADC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/ADC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/CAN.o: ../MCAL/CAN.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/CAN.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/EEPROM.o: ../MCAL/EEPROM.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/EEPROM.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/EXTI_Driver.o: ../MCAL/EXTI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/EXTI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/GPIO_Driver.o: ../MCAL/GPIO_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GPIO_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/GP_Timers.o: ../MCAL/GP_Timers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/GP_Timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/I2C.o: ../MCAL/I2C.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/I2C.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/RCC.o: ../MCAL/RCC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/SPI.o: ../MCAL/SPI.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/SPI.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/Timer.o: ../MCAL/Timer.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/Timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/Timer1_8.o: ../MCAL/Timer1_8.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/Timer1_8.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCAL/USART_Driver.o: ../MCAL/USART_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCAL/USART_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

