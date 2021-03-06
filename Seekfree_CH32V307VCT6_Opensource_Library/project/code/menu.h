/*
 * menu.h
 *
 *  Created on: 2021年12月1日
 *      Author: hxy
 */

#ifndef CORE_HDU_LIBRARIES_MENU_H_
#define CORE_HDU_LIBRARIES_MENU_H_

#include "zf_device_oled.h"
#include "my_flash.h"
#include "zf_common_headfile.h"

//结构体定义
struct item                                     //菜单选项
{
    enum
    {
        subpage=1,                      //页面类型 有子页
        value,
        switc,
        func,
        value_float,
        value_int32,
        title
    }type;

    int32 dlt;                          //每次改动的差值 试用于value
    float dlt_float;
    void *addr;                             //输出在oled上的值 若为子页类型 则为地址
    void *chf;                              //返回上一级地址

    char name[20];
};

struct page
{
    uint8 rpos;                          //第一行位置
    uint8 pos;                           //光标位置
    uint8 count;
    uint8 dymantic_page;                 //动态页

    struct item itemlist[35];
};

//按键
//zyx2
#define KEY_1       E6                    //up
#define KEY_2       C14                      //down
#define KEY_3       C13                     //add
#define KEY_4       C15                     //sub
#define KEY_5       D10                     //enter
#define KEY_6       D11                      //leave
#define KEY_7       D12                      //
#define KEY_DelayTime   100                     //按键扫描延时时间
extern uint32 cntpage;//页数
extern struct page *navigate[32];//指针

//函数声明待补充
//函数声明
void add_subpage(struct page * tg, char * name, struct page * v);
void add_value(struct page * tg, char * name, int16 * v, int16 dt, void (*changedCallBack)());
void add_value_float(struct page * tg, char * name, float * v, float dt, void (*changedCallBack)());
void add_switc(struct page * tg, char * name, int16 * v, void (*operate)());
void add_func(struct page * tg, char * name, void (*v)());
void add_value_int32(struct page * tg, char * name, int32 * v, int32 dt, void (*changedCallBack)());
void add_title(struct page * tg, char * name, char length);
void MenuRender(char full_update);
void OLED_BeginUpdate(void);
void MenuCmd(char cmd);
void key_init(void);//按键初始化
char key_scan(void);
void MenuInit(struct page *mainpage);
void OLED_EndUpdate(void);

#endif /* CORE_HDU_LIBRARIES_MENU_H_ */
