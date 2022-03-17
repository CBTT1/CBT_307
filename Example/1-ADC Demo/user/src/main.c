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
// ʹ����ɿƼ� WCH-LINK ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� B10
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� B11
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ

// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      ADC_0 = x
//      ...
//      ...
//      ...
// 5.�� ADC_CHANNELx �궨���Ӧ�����ŷֱ�ӵ� 3V3/GND �ٶ�Ӧ����Ϣ�ῴ�����ݱ仯
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************

#define ADC_CHANNEL1            ADC_IN12_C2
#define ADC_CHANNEL2            ADC_IN13_C3
#define ADC_CHANNEL3            ADC_IN14_C4
#define ADC_CHANNEL4            ADC_IN15_C5

uint16_t dat[4];
int main(void)
{
    interrupt_global_disable();            // �ر����ж�
    clock_init(SYSTEM_CLOCK_144M);      // ��ر���������ϵͳʱ�ӡ�
    debug_init();                       // ��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���

    adc_init(ADC_CHANNEL1);
    adc_init(ADC_CHANNEL2);
    adc_init(ADC_CHANNEL3);
    adc_init(ADC_CHANNEL4);

    interrupt_global_enable();            // ���ж������
    while(1)
    {

        dat[0] = adc_convert(ADC_CHANNEL1, ADC_12BIT);
        dat[1] = adc_convert(ADC_CHANNEL2, ADC_12BIT);
        dat[2] = adc_convert(ADC_CHANNEL3, ADC_12BIT);
        dat[3] = adc_convert(ADC_CHANNEL4, ADC_12BIT);
        printf("ADC_0 = %d\r\n", dat[0]);
        printf("ADC_1 = %d\r\n", dat[1]);
        printf("ADC_2 = %d\r\n", dat[2]);
        printf("ADC_3 = %d\r\n", dat[3]);

        system_delay_ms(100);

    }
}
// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б����
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� WCH-LINK �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
// ����3����ʾ��ֵ������ѹ������
//      ����ź������Ƿ�Ӷԣ��ź����Ƿ��ɶ�
//      ʹ�����ñ�����ʵ�������ϵ�ѹ�Ƕ��� Ȼ���� voltage/3V3*4096 ����