################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Task/AudioPlayerTaskManager.cpp \
../Task/PlayerTask.cpp 

CPP_DEPS += \
./Task/AudioPlayerTaskManager.d \
./Task/PlayerTask.d 

OBJS += \
./Task/AudioPlayerTaskManager.o \
./Task/PlayerTask.o 


# Each subdirectory must supply rules for building sources it contributes
Task/%.o: ../Task/%.cpp Task/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D_WIN64 -D__SONIK_x86_64__ -D_RELEASE -D__cplusplus=202002L -DHAVE_FSEEKO -DFLAC__NO_DLL -I"D:\MyLibrary\include\Audio\SoundSystem\Task" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Task

clean-Task:
	-$(RM) ./Task/AudioPlayerTaskManager.d ./Task/AudioPlayerTaskManager.o ./Task/PlayerTask.d ./Task/PlayerTask.o

.PHONY: clean-Task

