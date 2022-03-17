/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"
#include "cbt_headfile.h"

int main(void)
{
    interrupt_global_disable();             // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);          // 务必保留，设置系统时钟。
    debug_init();                           // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 此处编写用户代码(例如：外设初始化代码等)
    oled_init();
    key_init();

    encoder_init_dir(TIM5_ENCOEDER,TIM5_CH1_ENCOEDER_A0,TIM5_CH2_ENCOEDER_A1);
    encoder_init_dir(TIM1_ENCOEDER,TIM1_CH1_ENCOEDER_E9,TIM1_CH2_ENCOEDER_E11);
//    encoder_init_dir(TIM5_ENCOEDER,TIM5_CH2_ENCOEDER_A1,TIM5_CH1_ENCOEDER_A0);
//    encoder_init_dir(TIM1_ENCOEDER,TIM1_CH2_ENCOEDER_E11,TIM1_CH1_ENCOEDER_E9);




    menu_init();
    pwm_init(TIM10_PWM_CH1_D1,50,726);
    pwm_init(TIM9_PWM_CH2_A3,12000,0);//左后
    pwm_init(TIM9_PWM_CH1_A2,12000,0);//左前
    pwm_init(TIM3_PWM_CH3_B0,12000,0); //右后
    pwm_init(TIM3_PWM_CH4_B1,12000,0);//右前

    pit_init_ms(TIM4_PIT,20);

    mt9v03x_init_dvp();
    My_SdCard_Init();

    interrupt_global_enable();              // 总中断最后开启
    while(1)
    {
        MenuCmd(key_scan());
        if (navigate[cntpage]->dymantic_page)//如果为动态页
        {
                MenuRender(0);
                system_delay_ms(100);
        }

        // 此处编写需要循环执行的代码

    }
}




