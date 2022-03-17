
#include "zf_common_headfile.h"
#include "cbt_headfile.h"
#include "stdlib.h"

int16 middle = 726;
uint16 steer_out = 0;
int left_drive,right_drive;
int16 speed1 = 305 , speed2 = 295,speed3 = 320 , speed4 = 280;
float kp = 0,kd = 0;
float kp_straight = 0.49,kd_straight = 0.96;
float kp_turn = 1.25,kd_turn = 2.50;
float kp_roundabout = 1.15,kd_roundabout = 2.6;
float kp_fork = 1.2,kd_fork = 2.4,kp_fork_out = 1.16,kd_fork_out = 2.32;
float kp_speed = 20.1,ki_speed = 15.1;
uint8 f_turn_left = 0,f_turn_right = 0,f_straight = 0;
int f_longstraight = 0;

int16 error = 0,last_error = 0,delta_error;
float chasu = 1.7,chasu_huandao = 1.6 , chasu_fork = 1.5,chasu_fork_out = 1.5;
int16 line = 22;
float D_OUT;
int Bias = 0;
int16 speed = 0;
int L_exp,R_exp;
int L_speederr=0,R_speederr=0;
int L_speederr_l=0,R_speederr_l=0;
int L_increase=0, R_increase=0;
int L_pwm=0,R_pwm=0;
int last_speed = 0;
int L_pwm_f=0,R_pwm_f=0;
int pwm1=0,pwm2=0;
extern uint8 status_roundabout;


void Incremental_pwm()
{
    L_speederr = L_exp-lgpt12;
    L_increase = kp_speed*(L_speederr-L_speederr_l)+ki_speed*L_speederr;
    pwm1 += L_increase;
    L_speederr_l=L_speederr;

    if(pwm1>=9500)pwm1=9500;
    if(pwm1<-9500)pwm1=-9500;
    if(pwm1>=0)
    {
        L_pwm=pwm1;
        L_pwm_f=0;
    }
    else
    {
        L_pwm_f=-1*pwm1;
        L_pwm=0;
    }

    R_speederr = R_exp-rgpt12;
    R_increase = kp_speed*(R_speederr-R_speederr_l)+ki_speed*R_speederr;
    pwm2 += R_increase;
    R_speederr_l=R_speederr;

    if(pwm2>=9500)pwm2=9500;
    if(pwm2<-9500)pwm2=-9500;
    if(pwm2>=0)
    {
        R_pwm=pwm2;
        R_pwm_f=0;
    }
    else
    {
        R_pwm_f=-1*pwm2;
        R_pwm=0;
    }

//    if((Trans_Pixels(1,LCenter[1]) == 0 && Trans_Pixels(2,LCenter[2]) == 0 )|| flag_ruku >=2)
//    {
//        pwm_set_duty(TIM9_PWM_CH2_A3,0);//右前
//        pwm_set_duty(TIM9_PWM_CH1_A2,0);//右后
//        pwm_set_duty(TIM3_PWM_CH3_B0,0);//左前
//        pwm_set_duty(TIM3_PWM_CH4_B1,0); //左后
//    }
//    else
//    {
        pwm_set_duty(TIM3_PWM_CH4_B1,R_pwm);//右前
        pwm_set_duty(TIM3_PWM_CH3_B0,R_pwm_f);//右后
        pwm_set_duty(TIM9_PWM_CH1_A2,L_pwm);//左前
        pwm_set_duty(TIM9_PWM_CH2_A3,L_pwm_f); //左后
//    }



}

void pwm_out()
{

    if((status_roundabout>0&&status_roundabout<3)||(status_roundabout>=7 &&status_roundabout<=8))
    {
        f_longstraight = 0;
        L_exp = speed1;
        R_exp = speed1;
    }
    else if(f_turn_left == 0&&f_turn_right == 0&&f_straight == 1 && flag_podao == 0)//直道  赛道判断条件待确定
    {

        f_longstraight++;
        L_exp = speed1;
        R_exp = speed1;
    }
    else if(flag_podao == 1)
    {
        L_exp = speed1 - 80;
        R_exp = speed1 - 80;
    }

    else if(f_turn_left == 1&&f_turn_right == 0&&f_straight == 0)//左转
    {
        f_longstraight = 0;
        if(status_roundabout >=3 && status_roundabout < 7)
        {
            L_exp = speed3 - 0.5*abs(steer_out-middle) * chasu_huandao;
            R_exp = speed3 + 0.5*abs(steer_out-middle) * chasu_huandao;
        }
        else if(status_forkroad != 0 )
        {
            L_exp = speed4 - 0.5*abs(steer_out-middle) * chasu_fork;
            R_exp = speed4 + 0.5*abs(steer_out-middle) * chasu_fork;
        }
        else
        {
            L_exp = speed2  - 0.5* abs(steer_out-middle) * chasu;
            R_exp = speed2  + 0.5* abs(steer_out-middle) * chasu;
        }
    }
    else if(f_turn_left == 0&&f_turn_right == 1&&f_straight == 0)//右转
    {
        f_longstraight = 0;
        if(status_roundabout >=3 && status_roundabout < 7)
        {
            L_exp = speed3 + 0.5 * abs(steer_out-middle) * chasu_huandao;
            R_exp = speed3 - 0.5 * abs(steer_out-middle) * chasu_huandao;
        }
        else if(status_forkroad != 0 )
        {
            L_exp = speed4 + 0.5*abs(steer_out-middle) * chasu_fork;
            R_exp = speed4 - 0.5*abs(steer_out-middle) * chasu_fork;
        }
        else
        {
            L_exp = speed2 + 0.5 * abs(steer_out-middle) * chasu ;
            R_exp = speed2 - 0.5 * abs(steer_out-middle) * chasu;
        }
    }
    Incremental_pwm();
    pwm_set_duty(TIM10_PWM_CH1_D1,steer_out);
}

//void chasu_control()
//{
//    chasu = kp_chasu * error + kd_chasu*(error - last_error);
//
//
//}

void steer_control()
{

    if(flag_forkroad && status_forkroad <= 3)
    {
        kp = kp_fork;
        kd = kd_fork;
    }
    else if(flag_forkroad && status_forkroad > 3)
    {
        kp = kp_fork_out;
        kd = kd_fork_out;
    }
    else if(flag_roundabout)
    {
        kp = kp_roundabout;
        kd = kd_roundabout;
    }
    else if(f_straight)
    {
        kp = kp_straight;
        kd = kd_straight;
    }
    else if(f_turn_right || f_turn_left )
    {
        kp = kp_turn;
        kd = kd_turn;
    }
    else
    {
        kp = kp_straight;
        kd = kd_straight;
    }

    steer_out = (int)(middle - kp*error - kd*(error - last_error));
    if(steer_out >= middle + 80)
        steer_out = middle + 80;
    else if(steer_out <= middle - 80)
        steer_out = middle -80;


}


int an[13] = {8,15,19,23,26,29,32,34,36,38,40,42,44};//0  100 110 120 130 140 150 160 170 180 190 200 220
void line_control_new2()
{

    float x1,x2;
    int y1,y2;
    int16 sum1 = lgpt12 + rgpt12;
//    speed = lgpt12 + rgpt12;
    speed = (int16)(0.85f*(float)(sum1) + 0.15f*(float)(last_speed));
    last_speed = speed;
    if(speed>0&&speed<=100)
    {
        x1 = (100 - speed)/100.0;
        x2 = (speed - 0)/100.0;
        y1 = 0;
        y2 = 1;
    }
    else if(speed>100&&speed<=110)
    {
        x1 = (110 - speed)/10.0;
        x2 = (speed - 100)/10.0;

        y1 = 1;
        y2 = 2;
    }
    else if(speed>110&&speed<=120)
    {
        x1 = (120 - speed)/10.0;
        x2 = (speed - 110)/10.0;

        y1 = 2;
        y2 = 3;
    }
    else if(speed>120&&speed<=130)
    {
        x1 = (130 - speed)/10.0;
        x2 = (speed - 120)/10.0;
        y1 = 3;
        y2 = 4;
    }
    else if(speed>130&&speed<=140)
    {
        x1 = (140 - speed)/10.0;
        x2 = (speed - 130)/10.0;

        y1 = 4;
        y2 = 5;
    }
    else if(speed>140&&speed<=150)
    {
        x1 = (150 - speed)/10.0;
        x2 = (speed - 140)/10.0;

        y1 = 5;
        y2 = 6;
    }
    else if(speed>150&&speed<=160)
    {
        x1 = (160 - speed)/10.0;
        x2 = (speed - 150)/10.0;

        y1 = 6;
        y2 = 7;
    }
    else if(speed>160&&speed<=170)
    {
        x1 = (170 - speed)/10.0;
        x2 = (speed - 160)/10.0;

        y1 = 7;
        y2 = 8;
    }
    else if(speed>170&&speed<=180)
    {
        x1 = (180 - speed)/10.0;
        x2 = (speed - 170)/10.0;

        y1 = 8;
        y2 = 9;
    }
    else if (speed>180&&speed<=190)
    {
        x1 = (190 - speed)/10.0;
        x2 = (speed - 180)/10.0;

        y1 = 9;
        y2 = 10;
    }
    else if (speed>190&&speed<=200)
    {
        x1 = (200 - speed)/10.0;
        x2 = (speed - 190)/10.0;

        y1 = 10;
        y2 = 11;
    }
    else if (speed>200&&speed<=220)
    {
        x1 = (220 - speed)/20.0;
        x2 = (speed - 200)/20.0;

        y1 = 11;
        y2 = 12;
    }

    line = (int16)(x1*an[y1])+(int)(x2*an[y2]);
    if(line>=63) line  = 63;
}

