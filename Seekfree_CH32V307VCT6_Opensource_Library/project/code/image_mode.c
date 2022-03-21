#include "zf_common_headfile.h"
#include "cbt_headfile.h"

void mode1()
{
    oled_clear(0x00);
    gpio_init(KEY_6, GPI, 1,GPI_PULL_UP);
    while (1)
    {
        if (mt9v03x_finish_flag_dvp)
        {
            gray201image_clear();
            compress_image();
            DisplayImage_WithOLED();

            oled_show_uint(0, 0, Ostu_Threshold,3);
            mt9v03x_finish_flag_dvp = 0;
        }
        if (gpio_get_level(KEY_6) == 0)//判断是否退出
        {
              system_delay_ms(KEY_DelayTime);
              if ((gpio_get_level(KEY_6) == 0))
              {
                    pit_disable(TIM4_PIT);
                    DVP->CR0 |= 0x00;
                    mt9v03x_finish_flag_dvp = 0;
                    MenuRender(1);
                    return;
              }
        }
    }
        
}
void mode3()//读sd卡发送到上位机
{
//    My_SdCard_Init();
    while(1)
    {

          My_SdCard_Read();
          DisplayImage_WithOLED();
      if (gpio_get_level(KEY_6) == 0)//判断是否退出
      {
              system_delay_ms(KEY_DelayTime);
              if ((gpio_get_level(KEY_6) == 0))
              {
                    pit_disable(TIM4_PIT);
                    DVP->CR0 |= 0x00;
                    mt9v03x_finish_flag_dvp = 0;
                    MenuRender(1);
                    return;
              }
      }
    }
}

void mode4()
{
//    My_Tranfer_Init();
//    My_SdCard_Init();

//    mt9v03x_finish_flag_dvp = 1;
//    while(1)
//    {
//        if (mt9v03x_finish_flag_dvp)
//        {
//            mt9v03x_finish_flag_dvp = 0;
//            My_SdCard_Read();
//            DisplayImage_WithOLED();
//        }
//        oled_show_uint16(0,0,my_blockNum/6);
//        /******手动调节******/
//        if(gpio_get_level(KEY_3) == 0)//右
//        {
//            system_delay_ms(KEY_DelayTime);
//            if(gpio_get_level(KEY_3) == 0)//右
//            {
//                mt9v03x_finish_flag_dvp = 1;
//            }
//        }
//        if (gpio_get_level(KEY_4) == 0)//左
//        {
//            system_delay_ms(KEY_DelayTime);
//            if (gpio_get_level(KEY_4) == 0)//左
//            {
//                if(my_blockNum-12>=0)
//                {
//                    my_blockNum-=12;
//                    mt9v03x_finish_flag_dvp = 1;
//                }
//                else
//                {
//                    my_blockNum=0;
//                    mt9v03x_finish_flag_dvp = 1;
//                }

//            }
//        }
//        if(gpio_get_level(KEY_1) == 0)//上 一次五帧
//        {
//            system_delay_ms(KEY_DelayTime);
//            if(gpio_get_level(KEY_1) == 0)//上
//            {
//                my_blockNum+=24;
//                mt9v03x_finish_flag_dvp = 1;
//            }
//        }
//        if (gpio_get_level(KEY_2) == 0)//下 一次5帧
//        {
//            system_delay_ms(KEY_DelayTime);
//            if (gpio_get_level(KEY_2) == 0)//下
//            {
//                if(my_blockNum-36>=0)
//                {
//                    my_blockNum-=36;
//                    mt9v03x_finish_flag_dvp = 1;
//                }
//                else
//                {
//                    my_blockNum=0;
//                    mt9v03x_finish_flag_dvp = 1;
//                }

//            }
//        }

//        /************/
//        if (gpio_get_level(KEY_6) == 0)//判断是否退出
//        {
//                system_delay_ms(KEY_DelayTime);
//                if ((gpio_get_level(KEY_6) == 0))
//                {
//                    pit_disable(TIM4_PIT);
//                    mt9v03x_finish_flag_dvp = 0;
//                    MenuRender(1);
//                    return;
//                }
//        }
//    }
}

//void live_mode(void)
//{
//    uint16 i;
//    My_Tranfer_Init();
//    mt9v03x_init_dvp();
//    gpio_init(KEY_6, GPI, 1,GPI_PULL_UP );
//    // pit_enable_interrupt(CCU6_0, PIT_CH1);
//    transfer_finish_flag = 1;
//    i=200;
//    while(1)
//    {
//            if(mt9v03x_finish_flag_dvp && (!i))
//            {
//                i = 1000;
//                mt9v03x_finish_flag_dvp = 0;
//                transfer_finish_flag = 0;
//                init_saoxian();
//                compress_image();
//                get_centerline();
//                 //   find();
//                    //这里放图像处理
//                DisplayImage_WithOLED();    //oled显示
//                oled_show_int16(0,0,Ostu_Threshold);
//                My_LiveTransfer();
//            }
//            if (gpio_get_level(KEY_6) == 0)//判断是否退出
//            {
//                    system_delay_ms(KEY_DelayTime);
//                    if ((gpio_get_level(KEY_6) == 0))
//                    {
//                        pit_disable(TIM4_PIT);
//                        DVP->CR0 |= 0x00;
//                        mt9v03x_finish_flag_dvp = 0;
//                        MenuRender(1);
//                        return;
//                    }
//            }
//            i--;
//    }
//}
