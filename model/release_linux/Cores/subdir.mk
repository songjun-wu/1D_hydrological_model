################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cores/init.cpp \
../Cores/Canopy.cpp \
../Cores/SoilProfile.cpp \
../Cores/Tracking.cpp

OBJS += \
./Cores/init.o \
./Cores/Canopy.o \
./Cores/SoilProfile.o \
./Cores/Tracking.o

CPP_DEPS += \
./Cores/init.d \
./Cores/Canopy.d \
./Cores/SoilProfile.d \
./Cores/Tracking.d


# Each subdirectory must supply rules for building sources it contributes
Cores/%.o: ../Cores/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -ggdb -DCPU_LITTLE_ENDIAN -I"../includes" -O3 -ggdb -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


