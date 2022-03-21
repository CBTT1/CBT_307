################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_adc.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_delay.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_dvp.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_encoder.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_exti.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_flash.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_gpio.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_pit.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_pwm.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_soft_iic.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_spi.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_timer.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_uart.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_usb_cdc.c 

S_UPPER_SRCS += \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_irq.S 

OBJS += \
./zf_driver/zf_driver_adc.o \
./zf_driver/zf_driver_delay.o \
./zf_driver/zf_driver_dvp.o \
./zf_driver/zf_driver_encoder.o \
./zf_driver/zf_driver_exti.o \
./zf_driver/zf_driver_flash.o \
./zf_driver/zf_driver_gpio.o \
./zf_driver/zf_driver_irq.o \
./zf_driver/zf_driver_pit.o \
./zf_driver/zf_driver_pwm.o \
./zf_driver/zf_driver_soft_iic.o \
./zf_driver/zf_driver_spi.o \
./zf_driver/zf_driver_timer.o \
./zf_driver/zf_driver_uart.o \
./zf_driver/zf_driver_usb_cdc.o 

S_UPPER_DEPS += \
./zf_driver/zf_driver_irq.d 

C_DEPS += \
./zf_driver/zf_driver_adc.d \
./zf_driver/zf_driver_delay.d \
./zf_driver/zf_driver_dvp.d \
./zf_driver/zf_driver_encoder.d \
./zf_driver/zf_driver_exti.d \
./zf_driver/zf_driver_flash.d \
./zf_driver/zf_driver_gpio.d \
./zf_driver/zf_driver_pit.d \
./zf_driver/zf_driver_pwm.d \
./zf_driver/zf_driver_soft_iic.d \
./zf_driver/zf_driver_spi.d \
./zf_driver/zf_driver_timer.d \
./zf_driver/zf_driver_uart.d \
./zf_driver/zf_driver_usb_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
zf_driver/zf_driver_adc.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_adc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_delay.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_delay.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_dvp.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_encoder.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_exti.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_exti.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_flash.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_flash.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_gpio.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_gpio.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_irq.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_irq.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pit.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_pit.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_pwm.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_pwm.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_soft_iic.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_soft_iic.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_spi.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_spi.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_timer.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_timer.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_uart.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_driver/zf_driver_usb_cdc.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_driver/zf_driver_usb_cdc.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

