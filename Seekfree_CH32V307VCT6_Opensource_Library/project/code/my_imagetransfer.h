/*
 * my_imagetransfer.h
 *
 *  Created on: 2021��11��30��
 *      Author: hxy
 */

#ifndef CORE_HDU_LIBRARIES_MY_IMAGETRANSFER_H_
#define CORE_HDU_LIBRARIES_MY_IMAGETRANSFER_H_


#include "my_sd_card.h"
#include "zf_driver_uart.h"
#include "ch32v30x_dma.h"
#include "zf_device_mt9v03x_dvp.h"
//#define gray
#define bin

#define DMA_UART_CHx         DMA2_ch2
#define DMA_UART_TX_DB       ((uint8*)&(UART2->TDR))
#define DMA_UART_TX_SB       (uint8*)&My_Send_Data //����DMAԭ��ַ

struct Byte8_Struct
{
 uint8 bit1:1;
 uint8 bit2:1;
 uint8 bit3:1;
 uint8 bit4:1;
 uint8 bit5:1;
 uint8 bit6:1;
 uint8 bit7:1;
 uint8 bit8:1;
};

typedef struct//���߽ṹ��
{
//  uint8 LEnd;
//  uint8 REnd;
//  uint8 LStart;
    uint8 RStart;
    uint8 left;
    uint8 right;
    uint8 center;
}My_LCR;

typedef struct //����ṹ��
{
    uint8 Verific[8];//У��λ
    uint8 Pixels_width;//ͼ���� 186
    uint8 Pixels_height;//ͼ��߶� 70
    uint8 Coefficient_Num;//datanum 50
    uint8 Parameter_Num;  //parnum 1
    uint8 Data_Con[50*4*2];//���� data_give
    uint8 Par_Con[1*8];//����
    My_LCR Lcr[70];//����
    #if defined gray
    uint8 Pixels[186*70];//�Ҷ�ͼ��
    #elif defined bin
    uint8 Pixels[1628];//ѹ��ͼ��
    #endif
}My_Data_Type;

//�����С����
#define Verific_Len (12)
#if defined gray//�Ҷ�ͼ���
#define Pixels_Len  (186*70)
#elif defined bin//��ֵͼ��С
#define Pixels_Len  (1628)
#endif
#define Data_Len        (50*4*2)
#define Lcr_Len         (70*7)
#define Fix_Len         (10)
//�����ܳ���
#define Send_Data_Len   (Verific_Len+Pixels_Len+Data_Len+Lcr_Len+Fix_Len)//14895    2538

extern My_Data_Type My_Send_Data;
extern float Accelerate_Hor;
//�ӿں���
void My_Tranfer_Init(void);//�����ʼ��
void My_SdCard_Init(void);//��ʼ��sd��������ȡ
void My_SdCard_Save(void);//sd�������ֵͼ������
void My_SdCard_Read(void);//��ȡsd��������
void Get_SendData();//��䴫��ṹ��

#endif /* CORE_HDU_LIBRARIES_MY_IMAGETRANSFER_H_ */
