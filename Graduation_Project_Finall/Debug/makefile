################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include FreeRTOS/portable/MemMang/subdir.mk
-include FreeRTOS/portable/ARM_CM3/subdir.mk
-include FreeRTOS/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Graduation_Project_Finall.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Graduation_Project_Finall.list \

OBJCOPY_HEX += \
Graduation_Project_Finall.hex \

OBJCOPY_BIN += \
Graduation_Project_Finall.bin \


# All Target
all: Graduation_Project_Finall.axf secondary-outputs

# Tool invocations
Graduation_Project_Finall.axf: $(OBJS) $(USER_OBJS) C:\Users\Ahmed\Desktop\GP\Graduation_Project_Finall\STM32F103CBTX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "Graduation_Project_Finall.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Ahmed\Desktop\GP\Graduation_Project_Finall\STM32F103CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Graduation_Project_Finall.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Graduation_Project_Finall.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Graduation_Project_Finall.list"
	@echo 'Finished building: $@'
	@echo ' '

Graduation_Project_Finall.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Graduation_Project_Finall.hex"
	@echo 'Finished building: $@'
	@echo ' '

Graduation_Project_Finall.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Graduation_Project_Finall.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
