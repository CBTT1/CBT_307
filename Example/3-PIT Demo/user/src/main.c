/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
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

// *************************** ����Ӳ������˵�� ***************************
// ��

// *************************** ���̲���˵�� ***************************
// 1.������ÿ��500ms�ͻ��һ�ζ�ʱ��2�����жϺ���
// 2.��ʱ��2�ж�Ϊisr.c�е�TIM2_IRQHandler()����

// **************************** �������� ****************************
uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    // �򿪶�ʱ2�����жϣ�500msִ��һ��
    pit_init_ms(TIM2_PIT, 500);

    interrupt_global_enable();            // ���ж������
    while(1)
    {


    }
}
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��
