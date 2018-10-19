################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Arachne.c \
../Arachne_Message.c \
../Serial_port.c \
../UartInterface.c \
../ert_main.c 

OBJS += \
./Arachne.o \
./Arachne_Message.o \
./Serial_port.o \
./UartInterface.o \
./ert_main.o 

C_DEPS += \
./Arachne.d \
./Arachne_Message.d \
./Serial_port.d \
./UartInterface.d \
./ert_main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	/usr/local/cuda-8.0/bin/nvcc -DDebug_Test=1 -G -g -O0 -ccbin aarch64-linux-gnu-g++ -gencode arch=compute_50,code=sm_50 -m64 -odir "." -M -o "$(@:%.o=%.d)" "$<"
	/usr/local/cuda-8.0/bin/nvcc -DDebug_Test=1 -G -g -O0 --compile -m64 -ccbin aarch64-linux-gnu-g++  -x c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


