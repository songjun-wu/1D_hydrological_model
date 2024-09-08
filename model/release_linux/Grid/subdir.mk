################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Grid/dataType.cpp \
../Grid/constant_functions.cpp \
../Grid/IO_function.cpp \
../Grid/readClimateInputs.cpp \
../Grid/sortGridLDD.cpp \
../Grid/readConfigFile.cpp \
../Grid/report.cpp


OBJS += \
./Grid/dataType.o \
./Grid/constant_functions.o \
./Grid/IO_function.o \
./Grid/readClimateInputs.o \
./Grid/sortGridLDD.o \
./Grid/readConfigFile.o \
./Grid/report.o


CPP_DEPS += \
./Grid/dataType.d \
./Grid/constant_functions.d \
./Grid/IO_function.d \
./Grid/readClimateInputs.d \
./Grid/sortGridLDD.d \
./Grid/readConfigFile.d \
./Grid/report.d



# Each subdirectory must supply rules for building sources it contributes
Grid/%.o: ../Grid/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -ggdb -DCPU_LITTLE_ENDIAN -I"../includes" -O3 -ggdb -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


