################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/pieces/Pawn.cpp \
../src/pieces/Queen.cpp 

OBJS += \
./src/pieces/Pawn.o \
./src/pieces/Queen.o 

CPP_DEPS += \
./src/pieces/Pawn.d \
./src/pieces/Queen.d 


# Each subdirectory must supply rules for building sources it contributes
src/pieces/%.o: ../src/pieces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


