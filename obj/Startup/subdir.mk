################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Startup/startup_ch32v30x.S 

OBJS += \
./Startup/startup_ch32v30x.o 

S_UPPER_DEPS += \
./Startup/startup_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross Assembler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Startup" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/drivers" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include/libc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v/common" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/src" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/misc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/serial" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/finsh" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


