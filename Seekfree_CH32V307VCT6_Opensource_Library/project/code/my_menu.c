#include "zf_common_headfile.h"
#include "cbt_headfile.h"
#include "zf_device_mt9v03x_dvp.h"

struct page p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19,p20,p21,p22,p23,p24,p25,p26,p27,p28,p29,p30,p31,p32,p33,p34,p35,p36,p37,p38,p39,p40;


int16 dir_ku = 1;
int16 dir_forkroad = 1;
int16 chuku_flag = 0;
int16 Flash_SaveBlocks = 1;
int16 lgpt12 = 0,rgpt12 = 0;


void run();


void menu_init (void)
{
        //P3
        {
            add_value(&p3,"chuku?",&chuku_flag,1,NULL);
            add_value(&p3,"Dir",&dir_ku,1,NULL);
            add_value(&p3,"Fork",&dir_forkroad,1,NULL);
            add_func(&p3,"Run", run);
        }
        //P0
        {
            add_title(&p0, "Main", 4);
//            add_func(&p0,"Voltage",Voltage_Text);
            add_subpage(&p0, "Camera_set", &p1);
            add_subpage(&p0, "TURN", &p2);
            add_subpage(&p0, "Roundabout",&p7);
            add_subpage(&p0, "Fork",&p8);
            add_subpage(&p0, "Run",&p3);
            add_subpage(&p0, "TestMode",&p4);
            add_subpage(&p0, "flash",&p5);
            add_func(&p0,"mode3",mode3);
            add_func(&p0,"WatchingPic",mode4);

        }
        //P1
        {
            add_title(&p1,"Camera_set",12);
            add_value(&p1,"OstuMin",&OstuMin,1,NULL);
            add_value(&p1,"OstuMax",&OstuMax,1,NULL);
            add_value(&p1, "Gain", &mt9v03x_set_confing_buffer_dvp[7][1],1,NULL);
        }
        //P2
        {
            add_title(&p2,"turn setting",12);
            add_value(&p2,"line",&line,1,NULL);
            add_value_float(&p2,"chasu",&chasu,0.05, NULL);
            add_value(&p2,"middle",&middle,1,NULL);
            add_value(&p2,"speed1",&speed1,5,NULL);
            add_value(&p2,"speed2",&speed2,5,NULL);
            add_value_float(&p2,"p_sp",&kp_speed,0.05,NULL);
            add_value_float(&p2,"i_sp",&ki_speed,0.05,NULL);
            add_value_float(&p2, "KP_s",&kp_straight, 0.01, NULL);
            add_value_float(&p2, "KD_s",&kd_straight, 0.01, NULL);
            add_value_float(&p2, "KP_t",&kp_turn, 0.01, NULL);
            add_value_float(&p2, "KD_t",&kd_turn, 0.01, NULL);

        }

        //P4
        {
            add_func(&p4,"show",mode1);
//            add_func(&p4,"live_trans",live_mode);
//            add_func(&p4,"bluetooth_uart",wireless_test);
            add_func(&p4,"speed_test",speed_test);
            add_func(&p4,"drive_test",drive_test);
            add_func(&p4,"encoder_test",encoder_test);
            add_func(&p4,"SDcard_test",SDcard_test);
        }
        //P5
        {
            add_value(&p5,"Flash_SaveBlocks",&Flash_SaveBlocks,1,NULL);
            add_func(&p5,"read flash",&read_flashdata);
            add_func(&p5,"writeflash",&write_flashdata);
        }
        //P6
//        {
//            add_value(&p6, "0",   &an[0] , 1, NULL);
//            add_value(&p6, "100", &an[1] , 1, NULL);
//            add_value(&p6, "110", &an[2] , 1, NULL);
//            add_value(&p6, "120", &an[3] , 1, NULL);
//            add_value(&p6, "130", &an[4] , 1, NULL);
//            add_value(&p6, "140", &an[5] , 1, NULL);
//            add_value(&p6, "150", &an[6] , 1, NULL);
//            add_value(&p6, "160", &an[7] , 1, NULL);
//            add_value(&p6, "170", &an[8] , 1, NULL);
//            add_value(&p6, "180", &an[9] , 1, NULL);
//            add_value(&p6, "190", &an[10], 1, NULL);
//            add_value(&p6, "200", &an[11], 1, NULL);
//            add_value(&p6, "220", &an[12], 1, NULL);
//
//        }
        //p7
        {
            add_value(&p7,"speed",&speed3,5,NULL);
            add_value_float(&p7, "chasu", &chasu_huandao, 0.05, NULL);
            add_value_float(&p7, "kp", &kp_roundabout,0.01,NULL);
            add_value_float(&p7,"kd",&kd_roundabout,0.01,NULL);
        }
        //p8
        {
            add_value(&p8,"speed",&speed4,5,NULL);
            add_value_float(&p8, "chasu_in", &chasu_fork, 0.05, NULL);
            add_value_float(&p8, "kp_in", &kp_fork,0.01,NULL);
            add_value_float(&p8,"kd_in",&kd_fork,0.01,NULL);
            add_value_float(&p8, "chasu_out", &chasu_fork_out, 0.05, NULL);
            add_value_float(&p8, "kp_out", &kp_fork_out,0.01,NULL);
            add_value_float(&p8,"kd_out",&kd_fork_out,0.01,NULL);
        }


        MenuInit                            (&p0);
}


void run()
{
    oled_clear(0x00);
    pwm_set_duty(TIM10_PWM_CH1_B8,middle);
    flag_fps = 0;
    gpio_init(KEY_6, GPI, 1,GPI_PULL_UP);
    system_delay_ms(2000);
    pwm1=0,pwm2=0;
    flag_roundabout = status_roundabout = flag_right_roundabout = flag_left_roundabout = 0;
    LCenter[(uint8)line] =middle;
    run_flag = 1;
    interrupt_global_enable();
    while(1)
    {
        if(gpio_get_level(KEY_6) == 0)
        {
            system_delay_ms(KEY_DelayTime);
            if(gpio_get_level(KEY_6) == 0)
            {
                pwm_set_duty(TIM10_PWM_CH1_D1,middle);
                pit_disable(TIM4_PIT);
                mt9v03x_finish_flag_dvp = 0;
                MenuRender(1);
                return;
            }

        }

        if(mt9v03x_finish_flag_dvp)
        {
            flag_fps++;
            init_saoxian();
            compress_image();
            get_centerline();
            Cal_losttimes(break_hangshu);
//            breakhang_hold(2,15,break_hangshu);



            if(chuku_flag == 1)
            {
                chuku(dir_ku); //1出右库入左库 2出左库入右库
                ruku(dir_ku);
            }
            else if(chuku_flag == 0)
            {
                flag_chuku = 0;
                ruku(dir_ku);
            }

            podao();
            huandao();
            fork(dir_forkroad);
            crossroad();
            symbol_judge();
            pwm_out();
            zhongduan_flag = 0;
            mt9v03x_finish_flag_dvp = 0;

        }
    }
}
