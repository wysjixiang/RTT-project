################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtthread/components/finsh/cmd.c \
../rtthread/components/finsh/msh.c \
../rtthread/components/finsh/msh_cmd.c \
../rtthread/components/finsh/msh_file.c \
../rtthread/components/finsh/shell.c \
../rtthread/components/finsh/symbol.c 

OBJS += \
./rtthread/components/finsh/cmd.o \
./rtthread/components/finsh/msh.o \
./rtthread/components/finsh/msh_cmd.o \
./rtthread/components/finsh/msh_file.o \
./rtthread/components/finsh/shell.o \
./rtthread/components/finsh/symbol.o 

C_DEPS += \
./rtthread/components/finsh/cmd.d \
./rtthread/components/finsh/msh.d \
./rtthread/components/finsh/msh_cmd.d \
./rtthread/components/finsh/msh_file.d \
./rtthread/components/finsh/shell.d \
./rtthread/components/finsh/symbol.d 


# Each subdirectory must supply rules for building sources it contributes
rtthread/components/finsh/%.o: ../rtthread/components/finsh/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Debug" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Core" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/User" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Peripheral/inc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/drivers" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include/libc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v/common" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/src" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/misc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/serial" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


