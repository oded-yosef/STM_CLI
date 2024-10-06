################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/SavorEat/Utils/Source/ADC_Mgr.c \
../Middlewares/SavorEat/Utils/Source/I2C_Mgr.c \
../Middlewares/SavorEat/Utils/Source/Utils.c 

OBJS += \
./Middlewares/SavorEat/Utils/Source/ADC_Mgr.o \
./Middlewares/SavorEat/Utils/Source/I2C_Mgr.o \
./Middlewares/SavorEat/Utils/Source/Utils.o 

C_DEPS += \
./Middlewares/SavorEat/Utils/Source/ADC_Mgr.d \
./Middlewares/SavorEat/Utils/Source/I2C_Mgr.d \
./Middlewares/SavorEat/Utils/Source/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SavorEat/Utils/Source/%.o Middlewares/SavorEat/Utils/Source/%.su Middlewares/SavorEat/Utils/Source/%.cyclo: ../Middlewares/SavorEat/Utils/Source/%.c Middlewares/SavorEat/Utils/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"C:/Projects/SavorEat/SavorEat_STM_CLI/SavorEat_STM_CLI/Middlewares/SavorEat/Main_Task_Mgr/Include" -I"C:/Projects/SavorEat/SavorEat_STM_CLI/SavorEat_STM_CLI/Middlewares/SavorEat/Syslog_Mgr/Include" -I"C:/Projects/SavorEat/SavorEat_STM_CLI/SavorEat_STM_CLI/Middlewares/SavorEat/Utils/Include" -I"C:/Projects/SavorEat/SavorEat_STM_CLI/SavorEat_STM_CLI/Middlewares/SavorEat/CLI_Mgr/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-SavorEat-2f-Utils-2f-Source

clean-Middlewares-2f-SavorEat-2f-Utils-2f-Source:
	-$(RM) ./Middlewares/SavorEat/Utils/Source/ADC_Mgr.cyclo ./Middlewares/SavorEat/Utils/Source/ADC_Mgr.d ./Middlewares/SavorEat/Utils/Source/ADC_Mgr.o ./Middlewares/SavorEat/Utils/Source/ADC_Mgr.su ./Middlewares/SavorEat/Utils/Source/I2C_Mgr.cyclo ./Middlewares/SavorEat/Utils/Source/I2C_Mgr.d ./Middlewares/SavorEat/Utils/Source/I2C_Mgr.o ./Middlewares/SavorEat/Utils/Source/I2C_Mgr.su ./Middlewares/SavorEat/Utils/Source/Utils.cyclo ./Middlewares/SavorEat/Utils/Source/Utils.d ./Middlewares/SavorEat/Utils/Source/Utils.o ./Middlewares/SavorEat/Utils/Source/Utils.su

.PHONY: clean-Middlewares-2f-SavorEat-2f-Utils-2f-Source

