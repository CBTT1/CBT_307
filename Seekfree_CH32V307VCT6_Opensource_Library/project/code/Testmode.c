#include "zf_common_headfile.h"
#include "isr.h"
#include "cbt_headfile.h"

void drive_test()
{
    oled_clear(0x00);

    while(1)
    {
        pwm_set_duty(TIM9_PWM_CH2_A3,1000);//右前
        pwm_set_duty(TIM9_PWM_CH1_A2,3000);//右后
        pwm_set_duty(TIM3_PWM_CH3_B0,1000);//左前
        pwm_set_duty(TIM3_PWM_CH4_B1,3000); //左后
        if(gpio_get_level(KEY_6) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_6) == 0)
            {

            }

        }
    }
}
// void wireless_test()
// {
//     oled_fill(0x00);
//     uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
//     char x = 5 ;
//     while(1)
//     {
//         oled_p6x8char(20, 4, x+'0');
//         uart_putchar(UART_0, x+'0');
//         systick_delay_ms(STM1,500);
//         if(gpio_get_level(KEY_3) == 0)
//         {
//             systick_delay_ms(STM1, KEY_DelayTime);
//             if(gpio_get_level(KEY_3) == 0)
//             {
//                 x += 1;
//             }
//         }
//         if(gpio_get_level(KEY_4) == 0)
//         {
//             systick_delay_ms(STM1, KEY_DelayTime);
//             if(gpio_get_level(KEY_4) == 0)
//             {
//                 x -= 1;
//             }
//         }
//     }
// }
void speed_test()
{
    oled_init();
    system_delay_ms(500);
    pit_init_ms(TIM4_PIT,20);
    interrupt_global_enable();
    int L_set = 200;
    int R_set = 200;
    while(1)
    {
//        systick_delay_ms(STM1,18);


        if(zhongduan_flag)
        {
            L_exp = L_set;
            R_exp = R_set;
            pwm_out();
            zhongduan_flag = 0;
            oled_show_string(20, 0, "speed test");
            oled_show_int(20, 2, L_exp,3);
            oled_show_int(80, 2, R_exp,3);
            oled_show_float(20, 4, ki_speed , 2, 1);
            oled_show_float(20, 6, kp_speed , 2, 1);
        }
        if(gpio_get_level(KEY_1) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_1) == 0)
            {
                L_set += 100;
                R_set += 100;
            }

        }
        if(gpio_get_level(KEY_2) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_2) == 0)
            {
                L_set -= 100;
                R_set -= 100;
            }
        }
        if(gpio_get_level(KEY_3) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_3) == 0)
            {
                ki_speed += 0.5;
            }
        }
        if(gpio_get_level(KEY_4) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_4) == 0)
            {
                ki_speed -= 0.5;
            }
        }
        if(gpio_get_level(KEY_5) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_5) == 0)
            {
                kp_speed += 0.5;
            }
        }
        if(gpio_get_level(KEY_6) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_6) == 0)
            {
                kp_speed -= 0.5;
            }
        }
    }
}

void encoder_test()
{
    interrupt_global_disable(); ;
    oled_init();
    key_init();
    oled_clear(0x00);
    int16_t x1,x2;
    x1 = x2 = 0;
    while(1)
    {
        x1 = encoder_get_count(TIM5_ENCOEDER);
        x2 = -encoder_get_count(TIM1_ENCOEDER);

        oled_show_int(32, 0, x1,5);
        oled_show_int(32, 5, x2,5);


        if (gpio_get_level(KEY_5) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_5) == 0)
            {
                x1 = x2 = 0;
            }
        }

        if (gpio_get_level(KEY_6) == 0)//判断是否退出
        {
            system_delay_ms(KEY_DelayTime);
            if ((gpio_get_level(KEY_6) == 0))
            {
                MenuRender(1);
                return;
            }
        }
    }

}

void SDcard_test()
{
    int x;
    oled_init();
    x = sd_init();
    if(!x)
    {
        oled_show_string(32, 3, "Success");
    }
    else
    {
        oled_show_string(32, 3, "ERROR!");
    }

    while(1)
    {
        if (gpio_get_level(KEY_6) == 0)//判断是否退出
        {
                system_delay_ms(KEY_DelayTime);
                if ((gpio_get_level(KEY_6) == 0))
                {
    //                        pit_disable_interrupt(CCU6_0, PIT_CH1);
    //                        eru_disable_interrupt(MT9V03X_VSYNC_PIN);
    //                        dma_stop(MT9V03X_DMA_CH);
                        MenuRender(1);
                        return;
                }
        }
    }

}

//void Initall_testmode()
//{
//
//}
