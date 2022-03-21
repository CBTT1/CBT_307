/*
 * my_imagetransfer.c
 *
 *  Created on: 2021年11月30日
 *      Author: hxy
 */


#include "my_imagetransfer.h"
#include "zf_common_headfile.h"
#include "cbt_headfile.h"

extern uint8 image201[1628];
//定义传输结构体
extern uint8 LCenter[70], L_black[70], R_black[70];//拟图三线
extern uint8 mt9v03x_image_dvp[MT9V03X_DVP_H][MT9V03X_DVP_W];
My_Data_Type My_Send_Data;
float my_car_data[60];

static uint32 my_blockNum = 0;

void My_Data_Give(void)//要上传上位机的参数
{
    //最大可储存50个参数
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

//将float传输的函数
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

void Get_SendData()//填充传输结构体
{
    //传输头检验
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
    //图像获取

    #if defined gray//灰度模式 不压缩
    uint8 *p_pixels = My_Send_Data.Pixels;
    uint8 *p_pixels_gray = &Pixels[0][0];
    for(uint32 i = 0;i<Pixels_Len;i++)
    {
        *p_pixels++ = *p_pixels_gray++;
    }
    #elif defined bin//二值模式 将8压缩成1位
    uint8 *p_pixels = My_Send_Data.Pixels;//传输变量
    uint8 *p_pixels_gray = image201;//待压缩变量
    for(uint32 i = 0;i<1628/*Pixels_Len*/;i++)
    {
        //将这一位传输到里面
        *p_pixels++ = *p_pixels_gray++;
    }
    #endif
    //运行参数
    int32 *p_data = (int32*)My_Send_Data.Data_Con;
    for(uint16 i = 0;i<50;i++)
    {
        My_floattoint32((uint8 *)p_data, (uint8 *)&my_car_data[i]);
        *(int32 *)(p_data + 1) = ~(*(int32 *)p_data);
        p_data += 2;
    }
    //拟图
    My_LCR *my_Lcr = (My_LCR *)My_Send_Data.Lcr; //传拟图所需定义
    for (uint8 i = 0; i < 70; i++)
    {
            my_Lcr[i].left = (uint8)L_black[i];
            my_Lcr[i].right = (uint8)R_black[i];
            my_Lcr[i].center = (uint8)LCenter[i];
    }

}
void My_Tranfer_Init()//传输初始化
{
    uart_init(UART_3, 640000, UART3_TX_B10, UART3_RX_B11);
}

/********************************sd卡储存部分****************************************/
void My_SdCard_Init(void)//初始化sd卡储存或读取
{
    sd_init();
    my_blockNum = 0;
    My_Tranfer_Init();
}

    #if defined gray//灰度模式 不压缩
static uint8 Pixels_zip[13020];
    #elif defined bin//二值模式 将8压缩成1位
static uint8 Pixels_zip[2048];
    #endif
void My_Lines_Pack()//给出7条线 7*70=490 一个扇区
{
    for(uint8 i = 0; i < 70; i++)
    {
        Pixels_zip[1628+i] = L_black[i];
        Pixels_zip[1628+i + 70] = LCenter[i];
        Pixels_zip[1628+i + 140] = R_black[i];
    }
}
void My_Lines_UnPack()//解压三线
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
            } //写入4个字节
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



void My_SdCard_Save()//sd卡储存灰度图及参数
{
        My_Data_Give();//将参数写入数组
////    My_Lines_Pack();//将三线合一储存以节省扇区

    //图像压缩
    uint8 *p_pixels = Pixels_zip;//传输变量
    uint8 *p_pixels_gray = image201;//待压缩变量
    for(uint32 i = 0;i<1628;i++)
    {
        *p_pixels++ = *p_pixels_gray++;
    }
    My_Lines_Pack();
    My_data_Pack();
    ans=sd_WriteDisk(Pixels_zip,my_blockNum, 4);//不管怎样 都存储大图
    my_blockNum += 4;
}
void My_SdCard_Read()//读取sd卡并传输
{
    ans=SD_read_sector_data(Pixels_zip,my_blockNum,4);
    my_blockNum += 4;
    uint8 *p_pixels = Pixels_zip;//传输变量
    uint8 *p_pixels_gray = image201;//待压缩变量
      for(uint32 i = 0;i<1628;i++)
      {
          *p_pixels_gray++=*p_pixels++;
      }

    My_Lines_UnPack();//解压三线
    //解压自定义数据
    My_data_UnPack();
    //传输---------------------------------------------------
    Get_SendData();//填充传输结构体
    uart_write_buffer(UART_3,DMA_UART_TX_SB,Send_Data_Len);
}


