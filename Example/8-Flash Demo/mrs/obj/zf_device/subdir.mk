################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_absolute_encoder.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_bluetooth_ch9141.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_camera.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_icm20602.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_ips114.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_ips200_parallel8.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_mpu6050.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_mt9v03x_dvp.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_oled.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_scc8660_dvp.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_tft180.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_type.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_wireless_ch573.c \
E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_wireless_uart.c 

OBJS += \
./zf_device/zf_device_absolute_encoder.o \
./zf_device/zf_device_bluetooth_ch9141.o \
./zf_device/zf_device_bluetooth_ch9141_ch2.o \
./zf_device/zf_device_camera.o \
./zf_device/zf_device_icm20602.o \
./zf_device/zf_device_ips114.o \
./zf_device/zf_device_ips200_parallel8.o \
./zf_device/zf_device_mpu6050.o \
./zf_device/zf_device_mt9v03x_dvp.o \
./zf_device/zf_device_oled.o \
./zf_device/zf_device_scc8660_dvp.o \
./zf_device/zf_device_tft180.o \
./zf_device/zf_device_type.o \
./zf_device/zf_device_wireless_ch573.o \
./zf_device/zf_device_wireless_uart.o 

C_DEPS += \
./zf_device/zf_device_absolute_encoder.d \
./zf_device/zf_device_bluetooth_ch9141.d \
./zf_device/zf_device_bluetooth_ch9141_ch2.d \
./zf_device/zf_device_camera.d \
./zf_device/zf_device_icm20602.d \
./zf_device/zf_device_ips114.d \
./zf_device/zf_device_ips200_parallel8.d \
./zf_device/zf_device_mpu6050.d \
./zf_device/zf_device_mt9v03x_dvp.d \
./zf_device/zf_device_oled.d \
./zf_device/zf_device_scc8660_dvp.d \
./zf_device/zf_device_tft180.d \
./zf_device/zf_device_type.d \
./zf_device/zf_device_wireless_ch573.d \
./zf_device/zf_device_wireless_uart.d 


# Each subdirectory must supply rules for building sources it contributes
zf_device/zf_device_absolute_encoder.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_absolute_encoder.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_bluetooth_ch9141.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_bluetooth_ch9141_ch2.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_bluetooth_ch9141_ch2.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_camera.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_camera.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_icm20602.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_icm20602.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips114.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_ips114.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_ips200_parallel8.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_ips200_parallel8.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mpu6050.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_mpu6050.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_mt9v03x_dvp.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_mt9v03x_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_oled.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_oled.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_scc8660_dvp.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_scc8660_dvp.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_tft180.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_tft180.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_type.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_type.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_ch573.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_wireless_ch573.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
zf_device/zf_device_wireless_uart.o: E:/CODE/C/ch32v307/CHV307_Library/Example/libraries/zf_device/zf_device_wireless_uart.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Example\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\8-Flash Demo\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Example\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

