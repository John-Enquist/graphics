################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../proj1StarterCode/glsupport.o \
../proj1StarterCode/my_scan_converter.o \
../proj1StarterCode/scan_convert_test.o \
../proj1StarterCode/screen_buffer.o 

CPP_SRCS += \
../proj1StarterCode/glsupport.cpp \
../proj1StarterCode/my_scan_converter.cpp \
../proj1StarterCode/scan_convert_test.cpp \
../proj1StarterCode/screen_buffer.cpp 

OBJS += \
./proj1StarterCode/glsupport.o \
./proj1StarterCode/my_scan_converter.o \
./proj1StarterCode/scan_convert_test.o \
./proj1StarterCode/screen_buffer.o 

CPP_DEPS += \
./proj1StarterCode/glsupport.d \
./proj1StarterCode/my_scan_converter.d \
./proj1StarterCode/scan_convert_test.d \
./proj1StarterCode/screen_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
proj1StarterCode/%.o: ../proj1StarterCode/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


