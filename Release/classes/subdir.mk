################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../classes/Board.cpp \
../classes/ComputerPlayer.cpp \
../classes/Display.cpp \
../classes/Game.cpp \
../classes/HumanPlayer.cpp \
../classes/Player.cpp \
../classes/Square.cpp 

OBJS += \
./classes/Board.o \
./classes/ComputerPlayer.o \
./classes/Display.o \
./classes/Game.o \
./classes/HumanPlayer.o \
./classes/Player.o \
./classes/Square.o 

CPP_DEPS += \
./classes/Board.d \
./classes/ComputerPlayer.d \
./classes/Display.d \
./classes/Game.d \
./classes/HumanPlayer.d \
./classes/Player.d \
./classes/Square.d 


# Each subdirectory must supply rules for building sources it contributes
classes/%.o: ../classes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


