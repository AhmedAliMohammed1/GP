################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/portable/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/portable/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/portable/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/ARM_CM3/%.o FreeRTOS/portable/ARM_CM3/%.su FreeRTOS/portable/ARM_CM3/%.cyclo: ../FreeRTOS/portable/ARM_CM3/%.c FreeRTOS/portable/ARM_CM3/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F103CBTx -DSTM32F1 -c -I../Inc -I"C:/Users/medoo/Desktop/GP/Graduation_Project_Finall/FreeRTOS/include" -I"C:/Users/medoo/Desktop/GP/Graduation_Project_Finall/FreeRTOS/portable/ARM_CM3" -I"C:/Users/medoo/Desktop/GP/Graduation_Project_Finall/FreeRTOS/portable/MemMang" -I"C:/Users/medoo/Desktop/GP/Graduation_Project_Finall/HAL/inc" -I"C:/Users/medoo/Desktop/GP/Graduation_Project_Finall/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-FreeRTOS-2f-portable-2f-ARM_CM3

clean-FreeRTOS-2f-portable-2f-ARM_CM3:
	-$(RM) ./FreeRTOS/portable/ARM_CM3/port.cyclo ./FreeRTOS/portable/ARM_CM3/port.d ./FreeRTOS/portable/ARM_CM3/port.o ./FreeRTOS/portable/ARM_CM3/port.su

.PHONY: clean-FreeRTOS-2f-portable-2f-ARM_CM3

