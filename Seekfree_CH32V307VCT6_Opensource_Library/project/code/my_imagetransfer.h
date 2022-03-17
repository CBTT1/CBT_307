/*
 * my_imagetransfer.h
 *
 *  Created on: 2021年11月30日
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
#define DMA_UART_TX_SB       (uint8*)&My_Send_Data //设置DMA原地址

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

typedef struct//传线结构体
{
//  uint8 LEnd;
//  uint8 REnd;
//  uint8 LStart;
    uint8 RStart;
    uint8 left;
    uint8 right;
    uint8 center;
}My_LCR;

typedef struct //传输结构体
{
    uint8 Verific[8];//校验位
    uint8 Pixels_width;//图像宽度 186
    uint8 Pixels_height;//图像高度 70
    uint8 Coefficient_Num;//datanum 50
    uint8 Parameter_Num;  //parnum 1
    uint8 Data_Con[50*4*2];//数据 data_give
    uint8 Par_Con[1*8];//不用
    My_LCR Lcr[70];//三线
    #if defined gray
    uint8 Pixels[186*70];//灰度图像
    #elif defined bin
    uint8 Pixels[1628];//压缩图像
    #endif
}My_Data_Type;

//传输大小计算
#define Verific_Len (12)
#if defined gray//灰度图像大
#define Pixels_Len  (186*70)
#elif defined bin//二值图像小
#define Pixels_Len  (1628)
#endif
#define Data_Len        (50*4*2)
#define Lcr_Len         (70*7)
#define Fix_Len         (10)
//传输总长度
#define Send_Data_Len   (Verific_Len+Pixels_Len+Data_Len+Lcr_Len+Fix_Len)//14895    2538

extern My_Data_Type My_Send_Data;
extern float Accelerate_Hor;
//接口函数
void My_Tranfer_Init(void);//传输初始化
void My_SdCard_Init(void);//初始化sd卡储存或读取
void My_SdCard_Save(void);//sd卡储存二值图及参数
void My_SdCard_Read(void);//读取sd卡并传输
void Get_SendData();//填充传输结构体

#endif /* CORE_HDU_LIBRARIES_MY_IMAGETRANSFER_H_ */
