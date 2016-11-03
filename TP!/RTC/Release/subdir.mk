################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Arret.cpp \
../Auxiliaires.cpp \
../Coordonnees.cpp \
../Gestionnaire.cpp \
../Ligne.cpp \
../Station.cpp \
../Voyage.cpp \
../main.cpp \
../reseau.cpp 

OBJS += \
./Arret.o \
./Auxiliaires.o \
./Coordonnees.o \
./Gestionnaire.o \
./Ligne.o \
./Station.o \
./Voyage.o \
./main.o \
./reseau.o 

CPP_DEPS += \
./Arret.d \
./Auxiliaires.d \
./Coordonnees.d \
./Gestionnaire.d \
./Ligne.d \
./Station.d \
./Voyage.d \
./main.d \
./reseau.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


