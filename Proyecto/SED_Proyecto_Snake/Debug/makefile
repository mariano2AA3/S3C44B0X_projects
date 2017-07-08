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
SED_Proyecto_Snake.hex \

SECONDARY_LIST += \
SED_Proyecto_Snake.lst \

SECONDARY_SIZE += \
SED_Proyecto_Snake.siz \


# All Target
all: SED_Proyecto_Snake.elf secondary-outputs

# Tool invocations
SED_Proyecto_Snake.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\SED_Proyecto_Snake\commonUart\ram_ice.ld" -nostartfiles -L"C:\hlocal\EclipseARMwspace\SED_Proyecto_Snake\commonUart" -Wl,-Map,SED_Proyecto_Snake.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "SED_Proyecto_Snake.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SED_Proyecto_Snake.hex: SED_Proyecto_Snake.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary SED_Proyecto_Snake.elf  "SED_Proyecto_Snake.hex"
	@echo 'Finished building: $@'
	@echo ' '

SED_Proyecto_Snake.lst: SED_Proyecto_Snake.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S SED_Proyecto_Snake.elf > "SED_Proyecto_Snake.lst"
	@echo 'Finished building: $@'
	@echo ' '

SED_Proyecto_Snake.siz: SED_Proyecto_Snake.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley SED_Proyecto_Snake.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) SED_Proyecto_Snake.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
