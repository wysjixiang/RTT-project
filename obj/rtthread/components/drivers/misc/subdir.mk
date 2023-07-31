################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtthread/components/drivers/misc/pin.c \
../rtthread/components/drivers/misc/user_timer.c 

OBJS += \
./rtthread/components/drivers/misc/pin.o \
./rtthread/components/drivers/misc/user_timer.o 

C_DEPS += \
./rtthread/components/drivers/misc/pin.d \
./rtthread/components/drivers/misc/user_timer.d 


# Each subdirectory must supply rules for building sources it contributes
rtthread/components/drivers/misc/%.o: ../rtthread/components/drivers/misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Debug" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Core" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/User" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Peripheral/inc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/drivers" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include/libc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v/common" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/src" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/misc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/serial" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


