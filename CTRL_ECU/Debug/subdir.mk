################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CTRL_main.c \
../buzzer.c \
../dc_motor.c \
../delay.c \
../external_eeprom.c \
../gpio.c \
../timer.c \
../twi.c \
../uart.c 

OBJS += \
./CTRL_main.o \
./buzzer.o \
./dc_motor.o \
./delay.o \
./external_eeprom.o \
./gpio.o \
./timer.o \
./twi.o \
./uart.o 

C_DEPS += \
./CTRL_main.d \
./buzzer.d \
./dc_motor.d \
./delay.d \
./external_eeprom.d \
./gpio.d \
./timer.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


