################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f446zetx.s 

OBJS += \
./Core/Startup/startup_stm32f446zetx.o 

S_DEPS += \
./Core/Startup/startup_stm32f446zetx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"D:/Especialidad sistemas embebidos UBA/Programacion_de_microcontroladores/Encendido LED/PdM_workspace/Ejercicio_5/Drivers/API/Inc" -I"D:/Especialidad sistemas embebidos UBA/Programacion_de_microcontroladores/Encendido LED/PdM_workspace/Ejercicio_5/Drivers/API" -I"D:/Especialidad sistemas embebidos UBA/Programacion_de_microcontroladores/Encendido LED/PdM_workspace/Ejercicio_5/Drivers/API/Src" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f446zetx.d ./Core/Startup/startup_stm32f446zetx.o

.PHONY: clean-Core-2f-Startup

