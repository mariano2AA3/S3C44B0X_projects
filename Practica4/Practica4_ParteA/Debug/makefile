################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonUart/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Practica4_ParteA.hex \

SECONDARY_LIST += \
Practica4_ParteA.lst \

SECONDARY_SIZE += \
Practica4_ParteA.siz \


# All Target
all: Practica4_ParteA.elf secondary-outputs

# Tool invocations
Practica4_ParteA.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\Practica4_ParteA\commonUart\ram_ice.ld" -nostartfiles -L"C:\hlocal\EclipseARMwspace\Practica4_ParteA\commonUart" -Wl,-Map,Practica4_ParteA.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "Practica4_ParteA.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Practica4_ParteA.hex: Practica4_ParteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary Practica4_ParteA.elf  "Practica4_ParteA.hex"
	@echo 'Finished building: $@'
	@echo ' '

Practica4_ParteA.lst: Practica4_ParteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Practica4_ParteA.elf > "Practica4_ParteA.lst"
	@echo 'Finished building: $@'
	@echo ' '

Practica4_ParteA.siz: Practica4_ParteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Practica4_ParteA.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Practica4_ParteA.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
