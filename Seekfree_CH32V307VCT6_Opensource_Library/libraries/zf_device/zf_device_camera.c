/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_camera
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             version:
*                   V1.1 2021.12.02 增加串口发送图像到上位机函数
********************************************************************************************************************/

#include "zf_device_mt9v03x_dvp.h"
#include "zf_device_scc8660_dvp.h"
#include "zf_device_camera.h"
#include "zf_device_type.h"
#include "zf_device_oled.h"

uint8 camera_send_image_frame_header[4] = {0x00, 0xFF, 0x01, 0x01};

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头串口回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_uart_handler (void)
{
    if(camera_type == CAMERA_BIN_UART)
    {
        // 小钻风暂不支持
        //ov7725_cof_uart_interrupt();
    }
    else if(camera_type == CAMERA_GRAYSCALE)
    {
        // 总钻风串口回调函数
        mt9v03x_uart_callback_dvp();
    }
    else if(camera_type == CAMERA_COLOR)
    {
        //凌瞳串口回调函数
        scc8660_uart_callback_dvp();
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头场中断回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_vsync_handler (void)
{
    //不需要
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头采集完成DMA回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_dma_handler (void)
{
    //不需要
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头DVP接口回调函数
// @param       void
// @return      void
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void camera_dvp_handler(void)
{
    if(camera_type == CAMERA_COLOR)
    {
        scc8660_vsync_dvp();
    }
    else if(camera_type == CAMERA_GRAYSCALE)
    {
        mt9v03x_handler_dvp();
    }
    else if(camera_type == CAMERA_BIN_UART)
    {
        //小钻风不支持
    }
}


//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头二进制图像数据解压为十六进制八位数据 小钻风用
// @param       *data1          摄像头图像数组
// @param       *data2          存放解压数据的地址
// @param       image_size      图像的大小
// @return      void
// Sample usage:                camera_binary_image_decompression(&ov7725_image_binary[0][0], &data_buffer[0][0], OV7725_SIZE);
//-------------------------------------------------------------------------------------------------------------------
void camera_binary_image_decompression (uint8 *data1, uint8 *data2, uint32 image_size)
{
    uint8  i = 8;

    while(image_size--)
    {
        i = 8;
        while(i--)
        {
            *data2++ = ((*data1 >> i)&0x01 ? 255:0);
        }
        data1++;
    }
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       摄像头图像发送至上位机查看图像
// @param       uartn           使用的串口号
// @param       *image_addr     需要发送的图像地址
// @param       image_size      图像的大小
// @return      void
// Sample usage:                camera_send_image(DEBUG_UART_INDEX, &mt9v03x_image[0][0], MT9V03X_IMAGE_SIZE);
//-------------------------------------------------------------------------------------------------------------------
void camera_send_image (uart_index_enum uartn, void *image_addr, uint32 image_size)
{
    // 发送命令
    uart_write_byte(uartn,0x00);
    uart_write_byte(uartn,0xff);
    uart_write_byte(uartn,0x01);
    uart_write_byte(uartn,0x01);

    // 发送图像
    uart_write_buffer(uartn, (uint8*)image_addr, image_size);
}


uint8_t Ostu_Threshold=72;//74//61
uint8_t L_black[70];
uint8_t R_black[70];
uint8_t LCenter[70];
#define byte uint8_t
#define black_block 0
#define white_block 1
uint8_t image201[1628];
int16_t OstuMin = 30,OstuMax = 140;
int16_t start_p = 17;
float t;
float variance;
float maxVariance = 0, w0 = 0, avgValue = 0;
float u = 0;// 整幅图的平均灰度
float histogram[256];
void Ostu(void)
{
            //初始化
            u = 0;
            avgValue = 0;
            w0 = 0;
            maxVariance = 0;
            //清空灰度数组
            for(int i = 0; i < 256; i++)
            {
                    histogram[i] = 0;
            }

            // 生成灰度柱状图
            uint8_t *p_image = &mt9v03x_image_dvp[start_p][1];
            for (uint8_t i = 0; i < 70; i+=2)
            {
                    for (int j = 0; j < 186; ++j)
                    {//44-374
                            ++histogram[*p_image];
                            p_image++;
                    }
                    p_image += 190;
            }


            for (int16_t i = 0; i < 256; ++i)
            {
                    if(histogram[i] == 0)
                    {
                        continue;
                    }
                    histogram[i] = histogram[i] / (35 * 186);
                    u += i * histogram[i];
            }

            for (int16_t i = 0; i < 256; ++i)
            {
                    w0 += histogram[i];  //前景灰度
                    avgValue += i * histogram[i];
                    t = avgValue / w0 - u;
                    variance = t * t * w0 / (1 - w0); // g = w0/(1-w0)*(u0-u1)^2
                    if (variance > maxVariance)
                    { //找到使灰度差最大的值
                            maxVariance = variance;
                            Ostu_Threshold = i;            //那个值就是阈值
                    }
            }
            //对阈值限幅
            if (Ostu_Threshold > OstuMax)
            {
                    Ostu_Threshold = OstuMax;
            }
            if (Ostu_Threshold < OstuMin)
            {
                    Ostu_Threshold = OstuMin;
            }
}
void compress_image()
{
    gray201image_clear();
    uint8_t Bin_Array[256];
    uint8_t i;
    uint8_t *p_image = &mt9v03x_image_dvp[start_p][0];
    uint8_t H,W;
    uint16_t compress_oc=0;
    Ostu();
    for(i = 0; i < Ostu_Threshold; i++)
        Bin_Array[i] = 0;
    for(i = Ostu_Threshold; i < 255; i++)
        Bin_Array[i] = 1;
    for(H = 0;H<70;H++)
    {
        for(W = 0;W<186;W++)
        {
            image201[compress_oc] +=Bin_Array[*p_image]<<(7-(H*186+W)%8);
            //gray201image[H][W/8] += Bin_Array[*p_image]<<(W%8);
            if((H*186+W)%8==7) compress_oc++;
            p_image++;
        }
    }
}
uint8_t Trans_Pixels(uint8_t x,uint8_t y)
{
    if(x<0||x>=70||y<0||y>=186)
        return 0;
    else
        return (image201[(x*186+y)/8]>>(7-(x*186+y)%8))&0x01;
}

void gray201image_clear()
{
    memset(image201,0,sizeof(image201));
}
const uint8_t OledDian[128]=
{
    0,1,2,4,5,7,8,10,11,13,
    14,16,17,19,20,22,23,24,26,27,
    29,30,32,33,35,36,38,39,41,42,
    44,45,47,48,49,51,52,54,55,57,
    58,60,61,63,64,66,67,69,70,71,
    73,74,76,77,79,80,82,83,85,86,
    88,89,91,92,94,95,96,98,99,101,
    102,104,105,107,108,110,111,113,114,116,
    117,118,120,121,123,124,126,127,129,130,
    132,133,135,136,138,139,141,142,143,145,
    146,148,149,151,152,154,155,157,158,160,
    161,163,164,165,167,168,170,171,173,174,
    176,177,179,180,182,183,184,185,
};



void DisplayImage_WithOLED()
{
    uint8_t data,i,j,k;
    for(j=0; j<8; j++)
    {
        oled_set_coordinate(0,j);
        for(i=0; i<128; i++)
        {
            data=0;
            for(k=0; k<8; k++)
            {
                data+=(Trans_Pixels(63-(j*8+k),185-OledDian[i])<<k);              //将竖直的八个像素合成一个字节x
            }
            oled_write_data(data);
        }
    }
}

