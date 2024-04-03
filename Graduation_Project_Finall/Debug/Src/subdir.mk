################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/HAL/inc" -I"C:/Users/Ahmed/Desktop/EmbeddedSys/Mastering-Embedded-System-Diploma/GRAD_Project/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

