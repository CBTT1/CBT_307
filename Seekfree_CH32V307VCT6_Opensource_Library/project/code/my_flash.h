/*
 * my_flash.h
 *
 *  Created on: 2021Äê11ÔÂ29ÈÕ
 *      Author: hxy
 */

#ifndef CORE_HDU_LIBRARIES_MY_FLASH_H_
#define CORE_HDU_LIBRARIES_MY_FLASH_H_

#include "zf_driver_flash.h"

typedef union FLASH_Type{
    uint32 dat;
    float fdat;
    int16 idat;
    char cdat;
}Flash_Type;

extern char Is_FlashSave;

void write_flashdata();
void read_flashdata();


#endif /* CORE_HDU_LIBRARIES_MY_FLASH_H_ */
