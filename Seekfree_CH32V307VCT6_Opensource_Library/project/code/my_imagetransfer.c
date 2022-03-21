/*
 * my_imagetransfer.c
 *
 *  Created on: 2021��11��30��
 *      Author: hxy
 */


#include "my_imagetransfer.h"
#include "zf_common_headfile.h"
#include "cbt_headfile.h"

extern uint8 image201[1628];
//���崫��ṹ��
extern uint8 LCenter[70], L_black[70], R_black[70];//��ͼ����
extern uint8 mt9v03x_image_dvp[MT9V03X_DVP_H][MT9V03X_DVP_W];
My_Data_Type My_Send_Data;
float my_car_data[60];

static uint32 my_blockNum = 0;

void My_Data_Give(void)//Ҫ�ϴ���λ���Ĳ���
{
    //���ɴ���50������
    my_car_data[0] = status_roundabout;
    my_car_data[1] = status_forkroad;
    my_car_data[2] = flag_podao;
    my_car_data[3] = flag_ruku;
    my_car_data[4] = line;
    my_car_data[5] = steer_out;
    my_car_data[6] = lgpt12;
    my_car_data[7] = rgpt12;
    my_car_data[8] = L_exp;
    my_car_data[9] = R_exp;
    my_car_data[10] = f_turn_left;
    my_car_data[11] = f_turn_right;
    my_car_data[12] = f_straight;
    my_car_data[13] = f_longstraight;
    my_car_data[14] = flag_bend;
    my_car_data[15] = flag_crossroad;
    my_car_data[16] = flag_left_cross;
    my_car_data[17] = flag_right_cross;
    my_car_data[18] = error;
    my_car_data[19] = last_error;

}

//��float����ĺ���
void My_floattoint32(uint8 *p_int, uint8 *p_float)
{
    *p_int = *p_float;
    p_int++;    p_float++;
    *p_int = *p_float;
    p_int++;    p_float++;
    *p_int = *p_float;
    p_int++;    p_float++;
    *p_int = *p_float;
}

void Get_SendData()//��䴫��ṹ��
{
    //����ͷ����
    My_Send_Data.Verific[0] = 0x01;
    My_Send_Data.Verific[1] = 0x02;
    My_Send_Data.Verific[2] = 0x03;
    My_Send_Data.Verific[3] = 0x04;
    My_Send_Data.Verific[4] = 0x05;
    My_Send_Data.Verific[5] = 0x06;
    My_Send_Data.Verific[6] = 0x07;
    My_Send_Data.Verific[7] = 0x08;
    My_Send_Data.Pixels_width = 186;
    My_Send_Data.Pixels_height = 70;
    My_Send_Data.Coefficient_Num = 50;
    My_Send_Data.Parameter_Num = 1;
    //ͼ���ȡ

    #if defined gray//�Ҷ�ģʽ ��ѹ��
    uint8 *p_pixels = My_Send_Data.Pixels;
    uint8 *p_pixels_gray = &Pixels[0][0];
    for(uint32 i = 0;i<Pixels_Len;i++)
    {
        *p_pixels++ = *p_pixels_gray++;
    }
    #elif defined bin//��ֵģʽ ��8ѹ����1λ
    uint8 *p_pixels = My_Send_Data.Pixels;//�������
    uint8 *p_pixels_gray = image201;//��ѹ������
    for(uint32 i = 0;i<1628/*Pixels_Len*/;i++)
    {
        //����һλ���䵽����
        *p_pixels++ = *p_pixels_gray++;
    }
    #endif
    //���в���
    int32 *p_data = (int32*)My_Send_Data.Data_Con;
    for(uint16 i = 0;i<50;i++)
    {
        My_floattoint32((uint8 *)p_data, (uint8 *)&my_car_data[i]);
        *(int32 *)(p_data + 1) = ~(*(int32 *)p_data);
        p_data += 2;
    }
    //��ͼ
    My_LCR *my_Lcr = (My_LCR *)My_Send_Data.Lcr; //����ͼ���趨��
    for (uint8 i = 0; i < 70; i++)
    {
            my_Lcr[i].left = (uint8)L_black[i];
            my_Lcr[i].right = (uint8)R_black[i];
            my_Lcr[i].center = (uint8)LCenter[i];
    }

}
void My_Tranfer_Init()//�����ʼ��
{
    uart_init(UART_3, 640000, UART3_TX_B10, UART3_RX_B11);
}

/********************************sd�����沿��****************************************/
void My_SdCard_Init(void)//��ʼ��sd��������ȡ
{
    sd_init();
    my_blockNum = 0;
    My_Tranfer_Init();
}

    #if defined gray//�Ҷ�ģʽ ��ѹ��
static uint8 Pixels_zip[13020];
    #elif defined bin//��ֵģʽ ��8ѹ����1λ
static uint8 Pixels_zip[2048];
    #endif
void My_Lines_Pack()//����7���� 7*70=490 һ������
{
    for(uint8 i = 0; i < 70; i++)
    {
        Pixels_zip[1628+i] = L_black[i];
        Pixels_zip[1628+i + 70] = LCenter[i];
        Pixels_zip[1628+i + 140] = R_black[i];
    }
}
void My_Lines_UnPack()//��ѹ����
{
    for(uint8 i = 0; i < 70; i++)
    {
        L_black[i] =Pixels_zip[1628+i];
        LCenter[i] = Pixels_zip[1628+i + 70];
        R_black[i] = Pixels_zip[1628+i + 140];
    }
}
void My_data_Pack(void)
{
    union
    {
    uint8 data_uint8[4];
    float data_float;
    }data;
    uint8 *data_define=&Pixels_zip[1838];

    for(uint8 i=0;i<50;i++)
    {
        data.data_float=my_car_data[i];
        for(uint8 j=0;j<4;j++)
            {
            *data_define++=data.data_uint8[j];
            } //д��4���ֽ�
    }
}
void My_data_UnPack(void)
{
     union
    {
    uint8 data_uint8[4];
    float data_float;
    }data;
    uint8 *data_define=&Pixels_zip[1838];
    for(uint8 i=0;i<50;i++)
    {
        for(uint8 j=0;j<4;j++)
        {
        data.data_uint8[j]=*data_define++;
        }
        my_car_data[i]=data.data_float;
    }
}
uint8 ans=0;



void My_SdCard_Save()//sd������Ҷ�ͼ������
{
        My_Data_Give();//������д������
////    My_Lines_Pack();//�����ߺ�һ�����Խ�ʡ����

    //ͼ��ѹ��
    uint8 *p_pixels = Pixels_zip;//�������
    uint8 *p_pixels_gray = image201;//��ѹ������
    for(uint32 i = 0;i<1628;i++)
    {
        *p_pixels++ = *p_pixels_gray++;
    }
    My_Lines_Pack();
    My_data_Pack();
    ans=sd_WriteDisk(Pixels_zip,my_blockNum, 4);//�������� ���洢��ͼ
    my_blockNum += 4;
}
void My_SdCard_Read()//��ȡsd��������
{
    ans=SD_read_sector_data(Pixels_zip,my_blockNum,4);
    my_blockNum += 4;
    uint8 *p_pixels = Pixels_zip;//�������
    uint8 *p_pixels_gray = image201;//��ѹ������
      for(uint32 i = 0;i<1628;i++)
      {
          *p_pixels_gray++=*p_pixels++;
      }

    My_Lines_UnPack();//��ѹ����
    //��ѹ�Զ�������
    My_data_UnPack();
    //����---------------------------------------------------
    Get_SendData();//��䴫��ṹ��
    uart_write_buffer(UART_3,DMA_UART_TX_SB,Send_Data_Len);
}


