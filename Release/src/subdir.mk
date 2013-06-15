################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board.cpp \
../src/ComputerPlayer.cpp \
../src/Display.cpp \
../src/Game.cpp \
../src/GameHandler.cpp \
../src/GameView.cpp \
../src/HumanPlayer.cpp \
../src/Move.cpp \
../src/Player.cpp \
../src/Square.cpp 

OBJS += \
./src/Board.o \
./src/ComputerPlayer.o \
./src/Display.o \
./src/Game.o \
./src/GameHandler.o \
./src/GameView.o \
./src/HumanPlayer.o \
./src/Move.o \
./src/Player.o \
./src/Square.o 

CPP_DEPS += \
./src/Board.d \
./src/ComputerPlayer.d \
./src/Display.d \
./src/Game.d \
./src/GameHandler.d \
./src/GameView.d \
./src/HumanPlayer.d \
./src/Move.d \
./src/Player.d \
./src/Square.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


