################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RTCTP3/investigation.cpp \
../RTCTP3/main.cpp \
../RTCTP3/reseau.cpp 

OBJS += \
./RTCTP3/investigation.o \
./RTCTP3/main.o \
./RTCTP3/reseau.o 

CPP_DEPS += \
./RTCTP3/investigation.d \
./RTCTP3/main.d \
./RTCTP3/reseau.d 


# Each subdirectory must supply rules for building sources it contributes
RTCTP3/%.o: ../RTCTP3/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


