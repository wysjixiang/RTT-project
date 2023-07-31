################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include rtthread/src/subdir.mk
-include rtthread/libcpu/risc-v/common/subdir.mk
-include rtthread/components/finsh/subdir.mk
-include rtthread/components/drivers/serial/subdir.mk
-include rtthread/components/drivers/misc/subdir.mk
-include rtthread/subdir.mk
-include drivers/subdir.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
RT-thread-for-project.hex \

SECONDARY_LIST += \
RT-thread-for-project.lst \

SECONDARY_SIZE += \
RT-thread-for-project.siz \


# All Target
all: RT-thread-for-project.elf secondary-outputs

# Tool invocations
RT-thread-for-project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU RISC-V Cross C Linker'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Ld/Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"RT-thread-for-project.map" --specs=nano.specs --specs=nosys.specs -o "RT-thread-for-project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RT-thread-for-project.hex: RT-thread-for-project.elf
	@echo 'Invoking: GNU RISC-V Cross Create Flash Image'
	riscv-none-embed-objcopy -O ihex "RT-thread-for-project.elf"  "RT-thread-for-project.hex"
	@echo 'Finished building: $@'
	@echo ' '

RT-thread-for-project.lst: RT-thread-for-project.elf
	@echo 'Invoking: GNU RISC-V Cross Create Listing'
	riscv-none-embed-objdump --all-headers --demangle --disassemble "RT-thread-for-project.elf" > "RT-thread-for-project.lst"
	@echo 'Finished building: $@'
	@echo ' '

RT-thread-for-project.siz: RT-thread-for-project.elf
	@echo 'Invoking: GNU RISC-V Cross Print Size'
	riscv-none-embed-size --format=berkeley "RT-thread-for-project.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) RT-thread-for-project.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
