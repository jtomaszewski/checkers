################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../classes/pieces/Nothing.cpp \
../classes/pieces/Pawn.cpp \
../classes/pieces/Piece.cpp \
../classes/pieces/Queen.cpp 

OBJS += \
./classes/pieces/Nothing.o \
./classes/pieces/Pawn.o \
./classes/pieces/Piece.o \
./classes/pieces/Queen.o 

CPP_DEPS += \
./classes/pieces/Nothing.d \
./classes/pieces/Pawn.d \
./classes/pieces/Piece.d \
./classes/pieces/Queen.d 


# Each subdirectory must supply rules for building sources it contributes
classes/pieces/%.o: ../classes/pieces/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


