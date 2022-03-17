/*
 * my_flash.c
 *
 *  Created on: 2021年11月29日
 *      Author: hxy
 */

#include <zf_common_headfile.h>
#include <my_flash.h>
#include <cbt_headfile.h>
#include "zf_device_mt9v03x_dvp.h"

#define DATA_LEN 25                //一定要记得修改这里的数据长度
#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)
char Is_FlashSave=0;
Flash_Type FlashData[100];

uint32 Data_Flash[100];//用于遍历数据
uint8* Data_FlashP = NULL;

static void FlashDataTranslate(char mode)//内部调用，不管，更改需要存入和读取的参数
{
    if(mode==1) //数据装载过程

    {
        FlashData[0].fdat=chasu;
        FlashData[1].fdat=chasu_huandao;
        FlashData[2].fdat=kp_speed;
        FlashData[3].fdat=ki_speed;
        FlashData[4].fdat=kp_straight;
        FlashData[5].fdat=kd_straight;
        FlashData[6].fdat=kp_turn;
        FlashData[7].fdat=kd_turn;
        FlashData[8].fdat=kp_roundabout;
        FlashData[9].fdat=kd_roundabout;
        FlashData[10].fdat=chasu_fork;
        FlashData[11].fdat=kp_fork;
        FlashData[12].fdat=kd_fork;
        FlashData[13].fdat=chasu_fork_out;
        FlashData[14].fdat=kp_fork_out;
        FlashData[15].fdat=kd_fork_out;

        FlashData[16].idat=middle;
        FlashData[17].idat=speed1;
        FlashData[18].idat=speed2;
        FlashData[19].idat=speed3;
        FlashData[20].idat=speed4;
        FlashData[21].idat=OstuMin;
        FlashData[22].idat=OstuMax;
        FlashData[23].idat=mt9v03x_set_confing_buffer_dvp[7][1];
        FlashData[24].idat=line;




    }
    else if(mode==0)       //数据解析过程
    {
        chasu = FlashData[0].fdat;
        chasu_huandao = FlashData[1].fdat;
        kp_speed = FlashData[2].fdat;
        ki_speed = FlashData[3].fdat;
        kp_straight= FlashData[4].fdat;
        kd_straight =FlashData[5].fdat;
        kp_turn= FlashData[6].fdat;
        kd_turn= FlashData[7].fdat;
        kp_roundabout= FlashData[8].fdat;
        kd_roundabout= FlashData[9].fdat;
        chasu_fork= FlashData[10].fdat;
        kp_fork= FlashData[11].fdat;
        kd_fork =FlashData[12].fdat;
        chasu_fork_out= FlashData[13].fdat;
        kp_fork_out= FlashData[14].fdat;
        kd_fork_out= FlashData[15].fdat;

        middle =FlashData[16].idat;
        speed1= FlashData[17].idat;
        speed2= FlashData[18].idat;
        speed3 =FlashData[19].idat;
        speed4 =FlashData[20].idat;
        OstuMin= FlashData[21].idat;
        OstuMax =FlashData[22].idat;
        mt9v03x_set_confing_buffer_dvp[7][1] =FlashData[23].idat;
        line =FlashData[24].idat;
    }

}

/*
 *
  * 数据写入，直接调用
 *
 */
 void write_flashdata()
 {
     FlashDataTranslate(1);
     flash_page_program(FLASH_SECTION_15,FLASH_PAGE_3,(uint32 *)FlashData,DATA_LEN);
     oled_clear(0x00);
     oled_show_string(0,0,"<writeok>");
     system_delay_ms(500);
     oled_clear(0x00);
 }

/*
 *
  * 数据读出，直接调用
 *
 *
 */
 void read_flashdata()
 {
     flash_page_read(FLASH_SECTION_15,FLASH_PAGE_3,(uint32 *)FlashData,DATA_LEN);
     FlashDataTranslate(0);
     oled_clear(0x00);
     oled_show_string(0,0,"<readok>");
     system_delay_ms(500);
     oled_clear(0x00);
 }


//void write_flashdata()
//{
//    flash_erase_page(Flash_SaveBlocks,FLASH_PAGE_3);
//    Data_FlashP = (uint8 *)&Data_Flash[0];
//
//    *Data_FlashP++ = middle >> 8;              *Data_FlashP++ = middle & 0x00ff;
//    *Data_FlashP++ = speed1 >> 8;              *Data_FlashP++ = speed1 & 0x00ff;
//    *Data_FlashP++ = speed2 >> 8;              *Data_FlashP++ = speed2 & 0x00ff;
//    *Data_FlashP++ = speed3 >> 8;              *Data_FlashP++ = speed3 & 0x00ff;
//    *Data_FlashP++ = line >> 8;              *Data_FlashP++ = line & 0x00ff;
//    *Data_FlashP++ = OstuMin >> 8;              *Data_FlashP++ = OstuMin & 0x00ff;
//    *Data_FlashP++ = OstuMax >> 8;              *Data_FlashP++ = OstuMax & 0x00ff;
//    *Data_FlashP++ = mt9v03x_set_confing_buffer_dvp[7][1] >> 8;    *Data_FlashP++ = mt9v03x_set_confing_buffer_dvp[7][1] & 0x00ff;
//
//    *(uint32*)Data_FlashP = float_conversion_uint32(chasu); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(chasu_huandao); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_speed); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(ki_speed); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_straight); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kd_straight); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_turn); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kd_turn); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_roundabout); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kd_roundabout); Data_FlashP += 4;
//
//    *Data_FlashP++ = speed4 >> 8;              *Data_FlashP++ = speed4 & 0x00ff;
//
//    *(uint32*)Data_FlashP = float_conversion_uint32(chasu_fork); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_fork); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kd_fork); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(chasu_fork_out); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kp_fork_out); Data_FlashP += 4;
//    *(uint32*)Data_FlashP = float_conversion_uint32(kd_fork_out); Data_FlashP += 4;
//
//    flash_page_program(Flash_SaveBlocks, FLASH_PAGE_3, Data_Flash, 100);
//    oled_init();
//    oled_show_string(0,0,"<writeok>");
//    system_delay_ms(500);
//    oled_init();
//
//}
//void read_flashdata()
//{
//    Data_FlashP = (uint8 *)&Data_Flash[0];
//    if (Flash_SaveBlocks == 0)//不写入数据
//    return;
//
//    flash_page_read(Flash_SaveBlocks,FLASH_PAGE_3,(uint32 *)FlashData,DATA_LEN);
//
//    middle = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    speed1 = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    speed2 = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    speed3 = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    line = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//
//    OstuMin = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    OstuMax = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//    mt9v03x_set_confing_buffer_dvp[7][1] = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//
//    chasu = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    chasu_huandao = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_speed = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    ki_speed = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_straight = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kd_straight = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_turn = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kd_turn = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_roundabout = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kd_roundabout = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//
//    speed4 = (int16)((*Data_FlashP << 8) + *(Data_FlashP + 1));    Data_FlashP = Data_FlashP + 2;
//
//    chasu_fork = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_fork = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kd_fork = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    chasu_fork_out = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kp_fork_out = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//    kd_fork_out = (*(float *)Data_FlashP);  Data_FlashP = Data_FlashP + 4;
//
//    oled_init();
//    oled_show_string(0,0,"<readok>");
//    system_delay_ms(500);
//    oled_init();
//}



