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

#define     float_conversion_uint32(float_data)     (*(uint32 *)&float_data)


void write_flashdata()
{
    if(flash_check(FLASH_SECTION_60 + Flash_SaveBlocks , FLASH_PAGE_3))                      // 判断是否有数据
    flash_erase_page(FLASH_SECTION_60 + Flash_SaveBlocks, FLASH_PAGE_3);                // 擦除这一页


    flash_data_union_buffer[0].float_type=chasu;
    flash_data_union_buffer[1].float_type=chasu_huandao;
    flash_data_union_buffer[2].float_type=kp_speed;
    flash_data_union_buffer[3].float_type=ki_speed;
    flash_data_union_buffer[4].float_type=kp_straight;
    flash_data_union_buffer[5].float_type=kd_straight;
    flash_data_union_buffer[6].float_type=kp_turn;
    flash_data_union_buffer[7].float_type=kd_turn;
    flash_data_union_buffer[8].float_type=kp_roundabout;
    flash_data_union_buffer[9].float_type=kd_roundabout;
    flash_data_union_buffer[10].float_type=chasu_fork;
    flash_data_union_buffer[11].float_type=kp_fork;
    flash_data_union_buffer[12].float_type=kd_fork;
    flash_data_union_buffer[13].float_type=chasu_fork_out;
    flash_data_union_buffer[14].float_type=kp_fork_out;
    flash_data_union_buffer[15].float_type=kd_fork_out;

    flash_data_union_buffer[16].int16_type=middle;
    flash_data_union_buffer[17].int16_type=speed1;
    flash_data_union_buffer[18].int16_type=speed2;
    flash_data_union_buffer[19].int16_type=speed3;
    flash_data_union_buffer[20].int16_type=speed4;
    flash_data_union_buffer[21].int16_type=OstuMin;
    flash_data_union_buffer[22].int16_type=OstuMax;
    flash_data_union_buffer[23].int16_type=mt9v03x_set_confing_buffer_dvp[7][1];
    flash_data_union_buffer[24].int16_type=line;

    flash_write_page_to_data_buffer(FLASH_SECTION_60 + Flash_SaveBlocks, FLASH_PAGE_3);
    flash_data_buffer_clear();

    oled_clear(0x00);
    oled_show_string(0,0,"<readok>");
    system_delay_ms(500);
    oled_clear(0x00);
}


void read_flashdata()
{
    flash_data_buffer_clear();

    flash_read_page_to_data_buffer(FLASH_SECTION_60 + Flash_SaveBlocks , FLASH_PAGE_3);

    chasu = flash_data_union_buffer[0].float_type;
    chasu_huandao = flash_data_union_buffer[1].float_type;
    kp_speed = flash_data_union_buffer[2].float_type;
    ki_speed = flash_data_union_buffer[3].float_type;
    kp_straight= flash_data_union_buffer[4].float_type;
    kd_straight =flash_data_union_buffer[5].float_type;
    kp_turn= flash_data_union_buffer[6].float_type;
    kd_turn= flash_data_union_buffer[7].float_type;
    kp_roundabout= flash_data_union_buffer[8].float_type;
    kd_roundabout= flash_data_union_buffer[9].float_type;
    chasu_fork= flash_data_union_buffer[10].float_type;
    kp_fork= flash_data_union_buffer[11].float_type;
    kd_fork =flash_data_union_buffer[12].float_type;
    chasu_fork_out= flash_data_union_buffer[13].float_type;
    kp_fork_out= flash_data_union_buffer[14].float_type;
    kd_fork_out= flash_data_union_buffer[15].float_type;

    middle =flash_data_union_buffer[16].int16_type;
    speed1= flash_data_union_buffer[17].int16_type;
    speed2= flash_data_union_buffer[18].int16_type;
    speed3 =flash_data_union_buffer[19].int16_type;
    speed4 =flash_data_union_buffer[20].int16_type;
    OstuMin= flash_data_union_buffer[21].int16_type;
    OstuMax =flash_data_union_buffer[22].int16_type;
    mt9v03x_set_confing_buffer_dvp[7][1] =flash_data_union_buffer[23].int16_type;
    line =flash_data_union_buffer[24].int16_type;

    flash_data_buffer_clear(); 
    oled_clear(0x00);
    oled_show_string(0,0,"<readok>");
    system_delay_ms(500);
    oled_clear(0x00);
}

