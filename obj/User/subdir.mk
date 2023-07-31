################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Func.c \
../User/Peripheral.c \
../User/ch32v30x_it.c \
../User/lcd.c \
../User/main.c \
../User/peri_config.c \
../User/system_ch32v30x.c \
../User/user_thread.c 

OBJS += \
./User/Func.o \
./User/Peripheral.o \
./User/ch32v30x_it.o \
./User/lcd.o \
./User/main.o \
./User/peri_config.o \
./User/system_ch32v30x.o \
./User/user_thread.o 

C_DEPS += \
./User/Func.d \
./User/Peripheral.d \
./User/ch32v30x_it.d \
./User/lcd.d \
./User/main.d \
./User/peri_config.d \
./User/system_ch32v30x.d \
./User/user_thread.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Debug" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Core" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/User" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/Peripheral/inc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/drivers" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/include/libc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/libcpu/risc-v/common" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/src" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/include" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/misc" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/drivers/serial" -I"/home/jixiang/mrs_community-workspace/EmbeddedSystem/RTT-project/RT-thread-for-project/rtthread/components/finsh" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


