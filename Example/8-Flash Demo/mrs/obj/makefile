################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
SECONDARY_FLASH += \
8-Flash\ Demo.hex \

SECONDARY_LIST += \
8-Flash\ Demo.lst \

SECONDARY_SIZE += \
8-Flash\ Demo.siz \


# All Target
all: 8-Flash\ Demo.elf secondary-outputs

# Tool invocations
8-Flash\ Demo.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -Wl,-Map,"8-Flash Demo.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "8-Flash Demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
8-Flash\ Demo.hex: 8-Flash\ Demo.elf
	@	riscv-none-embed-objcopy -O ihex "8-Flash Demo.elf"  "8-Flash Demo.hex"
	@	@
8-Flash\ Demo.lst: 8-Flash\ Demo.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "8-Flash Demo.elf" > "8-Flash Demo.lst"
	@	@
8-Flash\ Demo.siz: 8-Flash\ Demo.elf
	@	riscv-none-embed-size --format=berkeley "8-Flash Demo.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) "8-Flash Demo.elf"
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
