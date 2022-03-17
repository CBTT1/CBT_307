################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/CODE/C/ch32v307/CHV307_Library/Seekfree_CH32V307VCT6_Opensource_Library/libraries/sdk/Startup/system_ch32v30x.c 

S_UPPER_SRCS += \
E:/CODE/C/ch32v307/CHV307_Library/Seekfree_CH32V307VCT6_Opensource_Library/libraries/sdk/Startup/startup_ch32v30x.S 

OBJS += \
./sdk/Startup/startup_ch32v30x.o \
./sdk/Startup/system_ch32v30x.o 

S_UPPER_DEPS += \
./sdk/Startup/startup_ch32v30x.d 

C_DEPS += \
./sdk/Startup/system_ch32v30x.d 


# Each subdirectory must supply rules for building sources it contributes
sdk/Startup/startup_ch32v30x.o: E:/CODE/C/ch32v307/CHV307_Library/Seekfree_CH32V307VCT6_Opensource_Library/libraries/sdk/Startup/startup_ch32v30x.S
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -x assembler -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
sdk/Startup/system_ch32v30x.o: E:/CODE/C/ch32v307/CHV307_Library/Seekfree_CH32V307VCT6_Opensource_Library/libraries/sdk/Startup/system_ch32v30x.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\Libraries\doc" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Core" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Ld" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Peripheral" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\sdk\Startup" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\project\user\inc" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_common" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_device" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\project\code" -I"E:\CODE\C\ch32v307\CHV307_Library\Seekfree_CH32V307VCT6_Opensource_Library\libraries\zf_driver" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

