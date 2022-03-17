/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             main
* @company          �ɶ���ɿƼ����޹�˾
 * @author          ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/



#include "zf_common_headfile.h"
#include "cbt_headfile.h"

int main(void)
{
    interrupt_global_disable();             // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);          // ��ر���������ϵͳʱ�ӡ�
    debug_init();                           // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // �˴���д�û�����(���磺�����ʼ�������)
    oled_init();
    key_init();

    encoder_init_dir(TIM5_ENCOEDER,TIM5_CH1_ENCOEDER_A0,TIM5_CH2_ENCOEDER_A1);
    encoder_init_dir(TIM1_ENCOEDER,TIM1_CH1_ENCOEDER_E9,TIM1_CH2_ENCOEDER_E11);
//    encoder_init_dir(TIM5_ENCOEDER,TIM5_CH2_ENCOEDER_A1,TIM5_CH1_ENCOEDER_A0);
//    encoder_init_dir(TIM1_ENCOEDER,TIM1_CH2_ENCOEDER_E11,TIM1_CH1_ENCOEDER_E9);




    menu_init();
    pwm_init(TIM10_PWM_CH1_D1,50,726);
    pwm_init(TIM9_PWM_CH2_A3,12000,0);//���
    pwm_init(TIM9_PWM_CH1_A2,12000,0);//��ǰ
    pwm_init(TIM3_PWM_CH3_B0,12000,0); //�Һ�
    pwm_init(TIM3_PWM_CH4_B1,12000,0);//��ǰ

    pit_init_ms(TIM4_PIT,20);

    mt9v03x_init_dvp();
    My_SdCard_Init();

    interrupt_global_enable();              // ���ж������
    while(1)
    {
        MenuCmd(key_scan());
        if (navigate[cntpage]->dymantic_page)//���Ϊ��̬ҳ
        {
                MenuRender(0);
                system_delay_ms(100);
        }

        // �˴���д��Ҫѭ��ִ�еĴ���

    }
}




