################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SonikCAS/SonikAtomicLock.cpp 

CPP_DEPS += \
./SonikCAS/SonikAtomicLock.d 

OBJS += \
./SonikCAS/SonikAtomicLock.o 


# Each subdirectory must supply rules for building sources it contributes
SonikCAS/%.o: ../SonikCAS/%.cpp SonikCAS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	clang++ -std=c++20 -D__SONIK_x86_64__=1 -D_DEBUG -D__cplusplus=202002L -D_WIN64 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-SonikCAS

clean-SonikCAS:
	-$(RM) ./SonikCAS/SonikAtomicLock.d ./SonikCAS/SonikAtomicLock.o

.PHONY: clean-SonikCAS

