#ifndef _EXTERN_H
#define _EXTERN_H

#include "zf_common_headfile.h"


//Menu

extern int16 dir_ku;
extern int16 dir_forkroad;
extern int16 chuku_flag;
extern int16 Flash_SaveBlocks;
//Encoder
extern int16 lgpt12,rgpt12;
extern uint8 b_line;
extern float k_line;

//环控制

extern int16 speed;
extern int turn,duty,x;
extern int begin;
extern float Angle,Anglelast;
extern int timeflag;

extern char Is_FlashSave;
//电机参数


//舵机参数
extern int16 middle,speed1,speed2,speed3,speed4;
extern uint16 steer_out;
extern int left_drive,right_drive;
extern uint8 f_turn_left,f_turn_right,f_straight;
extern int f_longstraight;
extern float kp,kd;
extern float kp_straight,kd_straight;
extern float kp_turn,kd_turn;
extern float kp_roundabout,kd_roundabout;
extern float kp_fork,kd_fork,kp_fork_out,kd_fork_out;

//差速参数
extern float chasu,chasu_huandao,chasu_fork,chasu_fork_out;
//控制环参数
extern int base;
extern float kp1,kd1,KD2;
extern int target,Bias;

extern int16 error,last_error,delta_error;
extern int16 line;
extern float D_OUT;
extern int an[13];

extern int L_exp,R_exp;
extern int L_speederr,R_speederr;
extern int L_speederr_l,R_speederr_l;
extern float kp_speed,ki_speed;
extern int pwm1,pwm2;
//摄像头
extern uint8  Ostu_Threshold;
extern int16  OstuMin,OstuMax;

//SD卡读取
//extern uint32 my_blockNum;

//中线处理相关
extern uint8 L_black[70];
extern uint8 R_black[70];
extern uint8 LCenter[70];
extern int flag_fps;

//extern uint8 old;
extern uint8 flag_s, times, leftline_duan_dian, rightline_duan_dian, break_hangshu;
extern uint8 lostleft_times, lostright_times, l_start,r_start, r_start_sec, l_start_sec;
extern uint8 trend2;
extern uint8 flag_leftdown, flag_rightdown,flag_leftup, flag_rightup;
extern uint8 flag_crossroad,flag_bend;
extern uint8 flag_left_cross ,flag_right_cross,flag_mid_cross;
extern uint8 flag_center_turn_left, flag_center_turn_right;
extern uint8 flag_find_huan_rightdown_point, flag_find_huan_leftdown_point, flag_find_huan_rightup_point, flag_find_huan_leftup_point, flag_find_huan_rightmiddle_point, flag_find_huan_leftmiddle_point;
extern uint8 second_findflag,sec_scan;
extern uint8 long_turn_flag_left, long_turn_flag_right, long_turn_flag;
extern uint8 flag_roundabout,flag_podao , flag_ruku ,flag_chuku,flag_forkroad;
extern uint8 flag_left_podao , flag_right_podao;
extern uint8 podao_up, podao_top, podao_down,podao_lock;
extern uint8 flag_right_roundabout, flag_left_roundabout;
extern uint8 status_roundabout,status_forkroad;
extern uint8 reg_right_up_y,reg_right_up_x;

extern float curvity_right, curvity_left;
extern float k, b, last_k,last_b;
extern float k_before_R_roundabout, b_before_R_roundabout , k_before_L_roundabout, b_before_L_roundabout;
extern float curve_a, curve_b;
extern float k1, k2, b1, b2;
extern float L_Cur, R_Cur;

//extern uint8 L_black[70];
//extern uint8 R_black[70];
extern uint8 L_Start[70];
extern uint8 R_Start[70];
extern uint8 L_End[70];
extern uint8 R_End[70];
//extern uint8 LCenter[70];
extern uint8 Fore_LCenter[70];
extern uint8 Fore_L_black[70];
extern uint8 Fore_R_black[70];
extern uint8 Leftline[70];
extern uint8 Rightline[70];
extern uint8 Centerline[70];
extern uint8 width[70];
extern uint8 leftfindflag[70];
extern uint8 rightfindflag[70];
extern uint8 right_turn_down[2];
extern uint8 left_turn_down[2];
extern uint8 right_turn_middle[2];
extern uint8 left_turn_middle[2];
extern uint8 right_turn_up[2];
extern uint8 left_turn_up[2];
extern uint8 center_turn_left[2];
extern uint8 center_turn_right[2];
extern uint8 curve_guai[2];

extern float parameterA,parameterB;

#endif
