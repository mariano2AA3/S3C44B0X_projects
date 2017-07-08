################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonEclipse/subdir.mk
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
Practica3_parteA.hex \

SECONDARY_LIST += \
Practica3_parteA.lst \

SECONDARY_SIZE += \
Practica3_parteA.siz \


# All Target
all: Practica3_parteA.elf secondary-outputs

# Tool invocations
Practica3_parteA.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\Practica3_ParteA\commonEclipse\ld_script_iic.ld" -nostartfiles -L"C:\hlocal\EclipseARMwspace\Practica3_parteA\commonEclipse" -L"C:\hlocal\EclipseARMwspace\Practica3_parteA\commonEclipse" -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/arm-none-eabi/lib" -L"C:\software\electronica\ARM\EclipseARM\eclipse\/../sourcery-g++-lite-arm-2011.03/lib/gcc/arm-none-eabi/4.5.2" -Wl,-Map,Practica3_parteA.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "Practica3_parteA.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Practica3_parteA.hex: Practica3_parteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary Practica3_parteA.elf  "Practica3_parteA.hex"
	@echo 'Finished building: $@'
	@echo ' '

Practica3_parteA.lst: Practica3_parteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Practica3_parteA.elf > "Practica3_parteA.lst"
	@echo 'Finished building: $@'
	@echo ' '

Practica3_parteA.siz: Practica3_parteA.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Practica3_parteA.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Practica3_parteA.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
