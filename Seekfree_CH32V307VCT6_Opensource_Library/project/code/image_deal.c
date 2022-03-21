
#include "zf_common_headfile.h"
#include "cbt_headfile.h"
#include <math.h>

//void get_pic()
//{
//    Pixels_get();
//    ImageGet_Pixels();
//}
#define L_black L_black
#define LCenter LCenter
#define R_black R_black


//int old;
//int leftfindflag[70],rightfindflag[70],width[70],leftline_duan_dian,rightline_duan_dian,flag_s,times,break_hangshu,fiv_width[70];
//int flag_find_huan_rightmiddle_point,flag_find_huan_leftmiddle_point,lostright_times,lostleft_times,l_start,r_start,center_delta,left_delta,right_delta,long_turn_flag,long_turn_flag_left,long_turn_flag_right;
//int right_turn_down[70],left_turn_down[70],right_turn_middle[70],left_turn_middle[70],right_turn_up[70],left_turn_up[70],curve_guai[70],forecast_centerline[70],R_Start[70];

int rou_of_right, rou_of_left, rou_of_center, last_rou_of_right, last_rou_of_left;
int center_delta, right_delta, left_delta;
int flag_fps = 0;

uint8 old = 93;
uint8 old_flag = 0;
uint8 error_L;
uint8 flag_s, times, leftline_duan_dian, rightline_duan_dian, break_hangshu;
uint8 lostleft_times, lostright_times, l_start,r_start, r_start_sec, l_start_sec;
uint8 trend2;
uint8 flag_leftdown, flag_rightdown,flag_leftup, flag_rightup;
uint8 flag_left_cross ,flag_right_cross;
uint8 flag_center_turn_left, flag_center_turn_right;
uint8 flag_find_huan_rightdown_point, flag_find_huan_leftdown_point, flag_find_huan_rightup_point, flag_find_huan_leftup_point, flag_find_huan_rightmiddle_point, flag_find_huan_leftmiddle_point;
uint8 second_findflag,sec_scan = 0;
uint8 flag_crossroad = 0, flag_roundabout = 0,flag_podao = 0, flag_ruku = 0,flag_chuku = 1 ,flag_forkroad = 0;
uint8 flag_left_podao = 0, flag_right_podao = 0;
uint8 flag_starting_line = 0;
uint8 podao_up, podao_top, podao_down,podao_lock = 0;
uint8 long_turn_flag_left, long_turn_flag_right, long_turn_flag;
uint8 flag_right_roundabout, flag_left_roundabout;
uint8 status_roundabout =0, status_forkroad = 0;
uint8 reg_right_up_y,reg_right_up_x,reg_left_up_y, reg_left_up_x;
uint8 flag_straight,flag_bend;
uint8 flag_left_cross, flag_right_cross,flag_mid_cross;
uint8 reg_center = 92;

float curvity_right, curvity_left;
float k, b, last_k,last_b;
float k_before_R_roundabout, b_before_R_roundabout , k_before_L_roundabout, b_before_L_roundabout;
float curve_a, curve_b;
float k1, k2, b1, b2;
float L_Cur, R_Cur;
//uint8 L_black[70];
//uint8 R_black[70];
uint8 v_guai[186];
uint8 L_End[70];
uint8 R_End[70];
uint8 L_Start[70];
uint8 R_Start[70];
//uint8 LCenter[70];
uint8 Fore_LCenter[70];
uint8 Fore_L_black[70];
uint8 Fore_R_black[70];
//uint8 L_black[70];
//uint8 R_black[70];
//uint8 LCenter[70];
uint8 width[70];
uint8 leftfindflag[70];
uint8 rightfindflag[70];
uint8 right_turn_down[2];
uint8 left_turn_down[2];
uint8 right_turn_middle[2];
uint8 left_turn_middle[2];
uint8 right_turn_up[2];
uint8 left_turn_up[2];
uint8 center_turn_left[2];
uint8 center_turn_right[2];
uint8 curve_guai[2];
uint8 ruku_guai_l[2];
uint8 ruku_guai_r[2];

/**处理函数*/
int My_Abs(int x)
{
    if (x < 0)
    {
        return (-x);
    }
    else return x;

}

int My_Min(int x, int y)
{
    if (x <= y) return x;
    else return y;
}

int My_Max(int x, int y)
{
    if (x >= y) return x;
    else return y;
}


uint8 Judge_fuhao(float a, float b)
{
    if ((a * b <= 0) && (a != 0 && b != 0))
        return 1; //异号
    else
        return 0; //同号
}


float process_curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3)
{
    float K;
    int S_of_ABC = ((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)) / 2;
    //面积的符号表示方向
    uint8 q1 = (uint8)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    uint8 AB = (uint8)sqrt(q1);
    q1 = (uint8)((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    uint8 BC = (uint8)sqrt(q1);
    q1 = (uint8)((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    uint8 AC = (uint8)sqrt(q1);
    if (AB * BC * AC == 0)
    {
        K = 0;
    }
    else
        K = (float)4 * S_of_ABC / (AB * BC * AC);
    return K;
}

float regression(int type, int startline, int endline)
{
    int i = 0;
    int sumlines = endline - startline;
    int sumX = 0;
    int sumY = 0;
    float k_return = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;
    if (type == 0)      //拟合中线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += LCenter[i];
        }
        if (sumlines != 0)
        {
            averageX = sumX / sumlines;     //x的平均值
            averageY = sumY / sumlines;     //y的平均值
        }
        else
        {
            averageX = 0;     //x的平均值
            averageY = 0;     //y的平均值
        }
        for (i = startline; i < endline; i++)
        {
            sumUp += (LCenter[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else
        {
            k = sumUp / sumDown;
            k_return = k;
        }
        b = averageY - k * averageX;
    }
    else if (type == 1)//拟合左线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += L_black[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x的平均值
        averageY = sumY / sumlines;     //y的平均值
        for (i = startline; i < endline; i++)
        {
            ////////////     ("L_black"+i+" " +L_black[i] + " averageY" +" "+ averageY);
            sumUp += (L_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else
        {
            k = sumUp / sumDown;
            k_return = k;
        }
        b = averageY - k * averageX;
    }
    else if (type == 2)//拟合右线
    {
        for (i = startline; i < endline; i++)
        {
            sumX += i;
            sumY += R_black[i];
        }
        if (sumlines == 0) sumlines = 1;
        averageX = sumX / sumlines;     //x的平均值
        averageY = sumY / sumlines;     //y的平均值
        for (i = startline; i < endline; i++)
        {
            sumUp += (R_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else
        {
            k = sumUp / sumDown;
            k_return = k;
        }
        b = averageY - k * averageX;

    }

    return k_return;
}

void advanced_regression(int type, int startline1, int endline1, int startline2, int endline2)
{
    int i = 0;
    int sumlines1 = endline1 - startline1;
    int sumlines2 = endline2 - startline2;
    int sumX = 0;
    int sumY = 0;
    float averageX = 0;
    float averageY = 0;
    float sumUp = 0;
    float sumDown = 0;
    if (type == 0)  //拟合中线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += LCenter[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += LCenter[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (LCenter[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (LCenter[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else k = sumUp / sumDown;
        b = averageY - k * averageX;

    }
    else if (type == 1)     //拟合左线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += L_black[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += L_black[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (L_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (L_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else k = sumUp / sumDown;
        b = averageY - k * averageX;
    }
    else if (type == 2)         //拟合右线
    {
        /**计算sumX sumY**/
        for (i = startline1; i < endline1; i++)
        {
            sumX += i;
            sumY += R_black[i];
        }
        for (i = startline2; i < endline2; i++)
        {
            sumX += i;
            sumY += R_black[i];
        }
        averageX = sumX / (sumlines1 + sumlines2);     //x的平均值
        averageY = sumY / (sumlines1 + sumlines2);     //y的平均值
        for (i = startline1; i < endline1; i++)
        {
            sumUp += (R_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        for (i = startline2; i < endline2; i++)
        {
            sumUp += (R_black[i] - averageY) * (i - averageX);
            sumDown += (i - averageX) * (i - averageX);
        }
        if (sumDown == 0) k = 0;
        else k = sumUp / sumDown;
        b = averageY - k * averageX;
    }

}

void Drew_Line(float k, float b, int StartLine, int EndLine, int type)
{
    int i = 0;
    if (type == 0)
    {
        for (i = StartLine; i < EndLine; i++)
        {
            int tool = (int)(k * i + b);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            L_End[i] = (uint8)tool;
        }
    }
    if (type == 1)//左线
    {
        //////////     ("1");
        for (i = StartLine; i < EndLine; i++)
        {
            int tool = (int)(k * i + b);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            L_Start[i] = (uint8)tool;
        }
    }
    if (type == 2)//右线
    {
        //////////     ("2");
        for (i = StartLine; i < EndLine; i++)
        {
            int tool = (int)(k * i + b);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            R_Start[i] = (uint8)tool;
        }
    }
}

void Cal_Line(float k, float b, uint8 StartLine, uint8 EndLine, uint8 type)
{
    int start = 0;
    if (type == 1)//左线
    {
        for (start = StartLine; start < EndLine; start++)
        {
            int tool = (int)(k * start + b);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            Fore_L_black[start] = (uint8)tool;
        }
    }
    if (type == 2)//右线
    {
        for (start = StartLine; start < EndLine; start++)
        {
            int tool = (int)(k * start + b);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            Fore_R_black[start] = (uint8)tool;
        }
    }
}


uint8 Judge_bend()
{
    error_L = My_Abs(LCenter[line] - 94);
    if(error_L >= 14)
    {
        flag_straight = 0;
        flag_bend = 1;
        return 1 ; //弯道
    } 
    else
    {
        flag_straight = 1;
        flag_bend = 0;
        return 0 ; //直道
    }
}

void shit(uint8 type, uint8 startline, uint8 endline)
{
    if (type == 2)
    {
        int delta = startline - endline;
        if (delta == 0) delta = 1;
        float k = (R_black[startline] - R_black[endline]) * 1.0f / delta;
        float b = R_black[startline] - k * startline;
        for (int j = (uint8)startline; j <= (uint8)endline; j++)
        {
            int jicun = ((int)(k * j + b));
            if (jicun >= 185) jicun = 185;
            else if (jicun <= 0) jicun = 0;
            R_End[j] = (uint8)jicun;
            //纠正右线

        }

    }
    if (type == 1)
    {
        int delta = startline - endline;
        if (delta == 0) delta = 1;
        float k = (L_black[startline] - L_black[endline]) * 1.0f / delta;
        float b = L_black[startline] - k * startline;
        for (int j = (uint8)startline; j <= (uint8)endline; j++)
        {
            int jicun = ((int)(k * j + b));
            if (jicun >= 185) jicun = 185;
            else if (jicun <= 0) jicun = 0;
            L_End[j] = (uint8)jicun;
            //纠正右线

        }

    }
}

void LeastSquareCalc_Curve(uint8 StartLine, uint8 EndLine, uint8 type)
{
    uint8 i = 0;
    float Sum_X2 = 0, Sum_Y = 0, Sum_X4 = 0, Sum_YX2 = 0, Average_X2 = 0, Average_Y = 0, Average_X4 = 0, Average_YX2 = 0, Sum = 0;

    Sum = EndLine - StartLine;
    if (type == 1)
    {
        for (i = StartLine; i < EndLine; i++)
        {
            Sum_X2 += i * i;
            Sum_Y += L_black[i];
            Sum_X4 += i * i * i * i;
            Sum_YX2 += L_black[i] * i * i;
        }
    }
    else if (type == 2)
    {
        for (i = StartLine; i < EndLine; i++)
        {
            Sum_X2 += i * i;
            Sum_Y += R_black[i];
            Sum_X4 += i * i * i * i;
            Sum_YX2 += R_black[i] * i * i;
        }
    }
    else    //中线
    {
        for (i = StartLine; i < EndLine; i++)
        {
            Sum_X2 += i * i;
            Sum_Y += LCenter[i];
            Sum_X4 += i * i * i * i;
            Sum_YX2 += LCenter[i] * i * i;
        }
    }
    Average_X2 = Sum_X2 / Sum;
    Average_Y = Sum_Y / Sum;
    Average_X4 = Sum_X4 / Sum;
    Average_YX2 = Sum_YX2 / Sum;
    curve_a = (Average_YX2 - Average_Y * Average_X2) / (Average_X4 - Average_X2 * Average_X2);
    curve_b = Average_Y - curve_a * Average_X2;
}

void init_saoxian()
{
 int y;
 for(y= 0;y<186;y++)
 {
     v_guai[y] = 69;
 }
 for(y=0;y<70;y++)
 {
     L_black[y] = 185;
     R_black[y] = 0;
     L_Start[y] = 0;
     R_Start[y] = 0;
     L_End[y] = 185;
     R_End[y] = 0;
     LCenter[y] = 93;
     Fore_LCenter[y] = 0;
     leftfindflag[y] = 0;
     rightfindflag[y] = 0;
     width[y] = 0;

 }
 for (y = 0; y < 2; y++)
 {
     right_turn_down[y] = 0;
     left_turn_down[0] = 0;
     left_turn_down[1] = 185;
     right_turn_up[y] = 0;
     left_turn_up[0] = 0;
     left_turn_up[1] = 185;
     right_turn_middle[y] = 0;
     left_turn_middle[0] = 0;
     left_turn_middle[1] = 185;

     curve_guai[y] = 0;
     ruku_guai_l[0] = 0;
     ruku_guai_l[1] = 185;
     ruku_guai_r[y] = 0;
 }

 flag_s = times = leftline_duan_dian = rightline_duan_dian = 0;
 lostleft_times = lostright_times = l_start = r_start = r_start_sec = l_start_sec = 0;
 k = b = 0;

 flag_left_cross = flag_right_cross = 0;
 k1 = k2 = b1 = b2 = k_before_R_roundabout = b_before_R_roundabout = k_before_L_roundabout = b_before_L_roundabout = 0;
 curve_a = curve_b = 0;
 flag_leftdown = flag_rightdown = flag_leftup = flag_rightup = 0;
 curvity_right = curvity_left = 0;
 rou_of_center = rou_of_right = rou_of_left = last_rou_of_right = last_rou_of_left = 0;
 flag_find_huan_rightdown_point = flag_find_huan_leftdown_point = flag_find_huan_rightup_point = flag_find_huan_leftup_point = flag_find_huan_rightmiddle_point = flag_find_huan_leftmiddle_point = 0;
 long_turn_flag_left = long_turn_flag_right = long_turn_flag = 0;
 center_delta = right_delta = left_delta = 0;
 second_findflag = sec_scan = 0;
 L_Cur = R_Cur = 0;
 flag_bend = 0;
 flag_crossroad = 0;



// flag_s = times = leftline_duan_dian = rightline_duan_dian = 0;
// lostleft_times = lostright_times = l_start = r_start=0;
// k = b = 0;
// k1 = k2 = b1 = b2 = 0;
// flag_leftdown = flag_rightdown = flag_leftup = flag_rightup = 0;
// second_findflag = 0;
}

void get_centerline()
{
    uint8 i, j;
    for (j = 0; j < 69; j++)
    {
        if (status_roundabout > 0 && status_roundabout != 5 && status_roundabout != 6 && status_roundabout != 7)
        {
            old = 93;
        }

        if (podao_top == 1 || podao_down == 1)
        {
            old = 93;
        }

        for (i = old; i >= 0 && i < 184; i++)
        {
            width[j]++;
            if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j,i+1) == 0)
            {
                leftfindflag[j] = 1;
                L_black[j] = i;
                break;
            }
        }
        for (i = old; i <= 185 && i > 1; i--)
        {
            width[j]++;
            if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j,i-1) == 0)
            {
                rightfindflag[j] = 1;
                R_black[j] = i;
                break;
            }

        }
        if (j <= 16 && leftfindflag[j] == 0 && rightfindflag[j] == 0) times++;
        if (j >= 16 && L_black[j] - L_black[j - 1] >= 15) leftline_duan_dian = (uint8)(j - 1);
        if (j >= 16 && R_black[j] - R_black[j - 1] <= -15) rightline_duan_dian = (uint8)(j - 1);
        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);

        if ((Trans_Pixels(j,LCenter[j]) == 0) && (Trans_Pixels(j+1,LCenter[j]) == 0))
        {
            break_hangshu = j;
            if (break_hangshu >= 15)    //防止在一开始就break
            {
                break;
            }
        }
        else break_hangshu = 69;
        if (status_roundabout > 0 && status_roundabout != 5 && status_roundabout != 6 && status_roundabout != 7)
        {
            old = 93;
        }
        else
        {
            old = LCenter[j];
            //old = (uint8)(0.05 * LCenter[j] + 0.95 * old);
        }

    }
    old = LCenter[5];
}

void find_rightdown_point(uint8 start_point, uint8 end_point, uint8 RoadName)
        {
            uint8 j;
            if (RoadName == 0) //十字 0
            {
                for (j = start_point; j <= end_point; j++)
                {
                    //找右边突变(下拐点)
                    if (My_Abs((int)R_black[j - 1] - (int)R_black[j - 2]) <= 3 && My_Abs((int)R_black[j] - (int)R_black[j - 1]) <= 3 && (R_black[j + 1] - R_black[j] <= -2)
                        && rightfindflag[j - 2] == 1 && rightfindflag[j - 1] == 1 && rightfindflag[j] == 1)
                    {
                        right_turn_down[0] = (uint8)(j + 1);//数组里面没有第0行
                        right_turn_down[1] = R_black[j];
                        break;
                    }
                }
            }
            else if (RoadName == 1) //环岛 1
            {
                if (status_roundabout != 2)
                {
                    for (j = start_point; j <= end_point; j++)
                    {
                        //找右边突变(下拐点)
                        if (r_start <= 34 && My_Abs((int)R_black[j - 1] - (int)R_black[j - 2]) <= 5 && My_Abs((int)R_black[j] - (int)R_black[j - 1]) <= 3 && (R_black[j + 1] - R_black[j] <= -2)
                            && rightfindflag[j - 2] == 1 && rightfindflag[j - 1] == 1 && rightfindflag[j] == 1)
                        {
                            right_turn_down[0] = (uint8)(j + 1);//数组里面没有第0行
                            right_turn_down[1] = R_black[j];
                            flag_find_huan_rightdown_point = 1;
                            break;
                        }
                    }
                    //如果右下拐点坐标不为空 且 环岛状态不是4 就认定找到环岛的右下拐点
                    if (right_turn_down[0] != 0)
                    {
                        flag_find_huan_rightdown_point = 1;
                    }
                }

            }
            //else
            //{

            //}
        }

void find_leftdown_point(uint8 start_point, uint8 end_point, uint8 RoadName)
{
    uint8 j;
    if (RoadName == 0)
    {
        for (j = start_point; j <= end_point; j++)
        {
            //找左边突变(下拐点)；连续且是存在的点（）
            if (My_Abs((int)L_black[j - 1] - (int)L_black[j - 2]) <= 3 && My_Abs((int)L_black[j] - (int)L_black[j - 1]) <= 3 && (L_black[j + 1] - L_black[j]) >= 4
                && leftfindflag[j - 2] == 1 && leftfindflag[j - 1] == 1 && leftfindflag[j] == 1)
            {
                left_turn_down[0] = (uint8)(j + 1);//数组里面没有第0行
                left_turn_down[1] = L_black[j];
                break;
            }
        }
    }
    else if (RoadName == 1)
    {
        if ( status_roundabout != 2)
        {
            //setText用户自定义("l_start"+ l_start);
            for (j = start_point; j <= end_point; j++)
            {
                //找左边突变(下拐点)；连续且是存在的点（）
                if (l_start <= 34 && My_Abs(L_black[j - 1] - L_black[j - 2]) <= 5 && My_Abs(L_black[j] - L_black[j - 1]) <= 3 && (L_black[j + 1] - L_black[j] >= 3)
                    && leftfindflag[j - 2] == 1 && leftfindflag[j - 1] == 1 && leftfindflag[j] == 1)
                {
                    left_turn_down[0] = (uint8)(j + 1);//数组里面没有第0行
                    left_turn_down[1] = L_black[j];
                    flag_find_huan_leftdown_point = 1;
                    break;
                }
            }
            if (left_turn_down[0] != 0) flag_find_huan_leftdown_point = 1;
        }
    }
    //else
    //{

    //}
}

void find_rightup_point(uint8 start_point, uint8 end_point, uint8 RoadName)
{
    uint8 j;
    if (RoadName == 0)
    {
        for (j = start_point; j <= end_point; j++)
        {
            //如果出现了连续的行数超过45行判定为长直道，此时不存在拐点
            if (flag_s >= 47) break;
            //右上拐点
            if (j >= 2 && ((R_black[j - 1] - R_black[j - 2]) >= 3 && My_Abs(R_black[j] - R_black[j - 1]) <= 4 && My_Abs(R_black[j + 1] - R_black[j]) <= 4
                && rightfindflag[j - 1] == 1 && rightfindflag[j] == 1 && rightfindflag[j + 1] == 1 || (R_black[j - 1] - R_black[j - 2] >= 15 && My_Abs(R_black[j] - R_black[j - 1]) <= 4 && My_Abs(R_black[j + 1] - R_black[j]) <= 4)))
            {
                right_turn_up[0] = (uint8)(j + 1);
                right_turn_up[1] = R_black[j];
                break;
            }
        }
    }
    else if (RoadName == 1)
    {
        for (j = start_point; j <= end_point; j++)
        {
            //如果出现了连续的行数超过45行判定为长直道，此时不存在拐点
            //if (flag_s >= 47) break;
            //右上拐点
            if ((R_black[j - 1] - R_black[j - 2]) >= 4 && My_Abs(R_black[j] - R_black[j - 1]) <= 3 && My_Abs(R_black[j + 1] - R_black[j]) <= 3
                && rightfindflag[j - 1] == 1 && rightfindflag[j] == 1 && rightfindflag[j + 1] == 1)
            {
                right_turn_up[0] = (uint8)(j + 1);
                right_turn_up[1] = R_black[j];
                flag_find_huan_rightup_point = 1;
                break;
            }
        }
    }
    //else
    //{

    //}
}

void find_leftup_point(uint8 start_point, uint8 end_point, uint8 RoadName)
{
    uint8 j;
    if (RoadName == 0)
    {
        for (j = start_point; j <= end_point; j++)
        {
            //左上拐点
            //L_black[j - 2] - L_black[j - 3] <= -4 &&
            if (j >= 2 && ((L_black[j - 1] - L_black[j - 2] <= -3 && L_black[j] - L_black[j - 1] <= 4 && L_black[j + 1] - L_black[j] <= 4
                && leftfindflag[j - 1] == 1 && leftfindflag[j] == 1 && leftfindflag[j + 1] == 1)
                || (L_black[j - 1] - L_black[j - 2] <= -15 && L_black[j] - L_black[j - 1] <= 4 && L_black[j + 1] - L_black[j + 2] <= 4)))
            {

                left_turn_up[0] = (uint8)(j + 1);//数组里面没有第0行
                left_turn_up[1] = L_black[j];
                if (left_turn_up[1] < 120)
                {
                    break;
                }
                else
                {

                }
            }
        }
    }
    else if (RoadName == 1)
    {
        for (j = start_point; j <= end_point; j++)
        {
            //左上拐点
            if (L_black[j - 1] - L_black[j - 2] <= -4 && My_Abs(L_black[j] - L_black[j - 1]) <= 3 && My_Abs(L_black[j + 1] - L_black[j]) <= 3
                && leftfindflag[j - 1] == 1 && leftfindflag[j] == 1 && leftfindflag[j + 1] == 1)
            {

                left_turn_up[0] = (uint8)(j + 1);//数组里面没有第0行
                left_turn_up[1] = L_black[j];
                flag_find_huan_leftup_point = 1;

                    break;
            }
        }
    }
    //else
    //{

    //}
}

void find_rightmiddle_point(uint8 start_point, uint8 end_point)
{
    uint8 i;
    for (i = start_point; i <= end_point; i++)
    {
        //找右拐点 下面3个点 上面2个点满足条件
        if (i >= 8 && (R_black[i - 3] - R_black[i + 1]) < 0 && (R_black[i - 2] - R_black[i + 1]) < 0 && (R_black[i - 1] - R_black[i + 1]) < 0
            && (R_black[i - 8] - R_black[i]) <= -2 && (R_black[i - 3] - R_black[i - 2]) <= 0 && (R_black[i - 2] - R_black[i - 1]) <= 0 && (R_black[i - 1] - R_black[i]) <= 0
            && (R_black[i + 3] - R_black[i + 1]) <= 0 && (R_black[i + 2] - R_black[i + 1]) <= 0
            && rightfindflag[i + 1] == 1 && rightfindflag[i] == 1 && rightfindflag[i - 1] == 1 && rightfindflag[i - 2] == 1 && rightfindflag[i + 2] == 1 && rightfindflag[i + 3] == 1
            )
        {
            right_turn_middle[0] = (uint8)(i + 1);
            right_turn_middle[1] = R_black[i];
            flag_find_huan_rightmiddle_point = 1;
            break;
        }
    }

}

void find_leftmiddle_point(uint8 start_point, uint8 end_point)
{
    uint8 i; //&& (L_black[i - 5] - L_black[i]) >= 2
    for (i = start_point; i <= end_point; i++)
    {
        //找左拐点
        if (i >= 8 && (L_black[i - 3] - L_black[i + 1]) > 0 && (L_black[i - 2] - L_black[i + 1]) > 0 && (L_black[i - 1] - L_black[i + 1]) > 0
            && (L_black[i - 8] - L_black[i]) >= 2 && (L_black[i - 3] - L_black[i - 2]) >= 0 && (L_black[i - 2] - L_black[i - 1]) >= 0 && (L_black[i - 1] - L_black[i]) >= 0
            && (L_black[i + 3] - L_black[i + 1]) >= 0 && (L_black[i + 2] - L_black[i + 1]) >= 0
            && leftfindflag[i + 1] == 1 && leftfindflag[i] == 1 && leftfindflag[i - 1] == 1 && leftfindflag[i - 2] == 1 && leftfindflag[i + 2] == 1 && leftfindflag[i + 3] == 1
            )
        {
            left_turn_middle[0] = (uint8)(i + 1);
            left_turn_middle[1] = L_black[i];
            flag_find_huan_leftmiddle_point = 1;
            break;
        }
    }

}

//void show_centerline()
//{
//
//    Pixels_get();
//    get_centerline();
//    DisplayImage_WithOLED();
//    mt9v03x_finish_flag = 0;
//
//}

void Cal_losttimes(int times)
{
    uint8 i;
    uint8 flag_of_rightbreak = 0;
    uint8 flag_of_leftbreak = 0;
    lostleft_times = lostright_times = l_start = r_start = 0;
    for (i = 0; i < times; i++)
    {
        //左线操作
        if (leftfindflag[i] == 0)       //未扫到线
        {
            lostleft_times++;
            if (flag_of_leftbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
            {
                l_start++;
            }
        }
        else    //扫到线
        {
            //lostleft_times不继续增加
            flag_of_leftbreak = 1;  //break标志成立
        }
        //右线操作
        if (rightfindflag[i] == 0)       //未扫到线
        {
            lostright_times++;
            if (flag_of_rightbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
            {
                r_start++;
            }
        }
        else    //扫到线
        {
            //lostright_times不继续增加
            flag_of_rightbreak = 1;  //break标志成立
        }
    }
}

void breakhang_hold(uint8 startline, uint8 endline, uint8 j)
{
    endline = (uint8)My_Min((uint8)endline, (uint8)j);
    int k = LCenter[endline] - LCenter[startline];
    if((k >-8 && k < 8) || flag_forkroad == 1)
    {
            for (uint8 i = j; i < 70; i++)
            {
                if (j >= 2)
                {
                    LCenter[i] = LCenter[j - 2];
                }
            }
    }
    else if (k >= 8) // 左弯
    {
        for (uint8 i = j; i < 70; i++)
        {
            LCenter[i] = 185;
        }
    }
    else if (k <= -8) //右弯
    {
        for (uint8 i = j; i < 70; i++)
        {
            LCenter[i] = 0;
        }
    }
    else
    {
        for (uint8 i = j; i < 70; i++)
        {
            if (j >= 2)
            {
                LCenter[i] = LCenter[j - 2];
            }
        }
    }
}

int Cal_estimator(uint8 type)
{
    if (type == 1)//左
    {
        int p;
        int rec = 0;
        /*****************************先计算右线曲率**********/
        uint8 curvity_point1 = (uint8)((l_start + break_hangshu) / 2);        //中点
        uint8 curvity_point2 = 0;
        if (break_hangshu >= 5)
        {
            curvity_point2 = (uint8)(break_hangshu - 3);
        }
        else
        {
            curvity_point2 = (uint8)(break_hangshu);
        }
        curvity_left = process_curvity(L_black[l_start], l_start, L_black[curvity_point1], curvity_point1, L_black[curvity_point2], curvity_point2);

        /*****************************计算方差********************/
        //曲率接近0说明线挺直的，为了体现直线方差小的特点，从第start行开始计算
        if (curvity_right < 0.4 && curvity_right > -0.1 && l_start <= 32 && (break_hangshu - l_start) >= 7)
        {
            regression(1, l_start, break_hangshu);

            Cal_Line(k, b, 0, break_hangshu, 1);
            for (p = l_start; p < break_hangshu - 5; p++)
            {
                rec += (Fore_L_black[p] - L_black[p]) * (Fore_L_black[p] - L_black[p]);
            }
        }
        //否则说明边界是曲线，此时为了凸显出曲线的方差大的特点，从第0行开始计算
        else
        {

            regression(1, 0, break_hangshu);

            Cal_Line(k, b, 0, break_hangshu, 1);
            for (p = 0; p < break_hangshu - 5; p++)
            {
                rec += (Fore_L_black[p] - L_black[p]) * (Fore_L_black[p] - L_black[p]);
            }
        }
        return rec;
    }
    else if (type == 2)//右
    {
        int p;
        int rec = 0;
        /*****************************先计算右线曲率**********/
        uint8 curvity_point1 = (uint8)((r_start + break_hangshu) / 2);        //中点
        uint8 curvity_point2 = 0;
        if (break_hangshu >= 5)
        {
            curvity_point2 = (uint8)(break_hangshu - 3);
        }
        else
        {
            curvity_point2 = (uint8)(break_hangshu);
        }
        curvity_right = process_curvity(R_black[r_start], r_start, R_black[curvity_point1], curvity_point1, R_black[curvity_point2], curvity_point2);

        /*****************************计算方差********************/
        //曲率接近0说明线挺直的，为了体现直线方差小的特点，从第start行开始计算
        if (curvity_right > -0.4 && curvity_right < 0.1 && r_start <= 32 && (break_hangshu - r_start) >= 7)
        {
            regression(2, r_start, break_hangshu);    //拟合右线


            Cal_Line(k, b, 0,break_hangshu, 2);
            for (p = r_start; p < break_hangshu - 5; p++)
            {
                rec += (Fore_R_black[p] - R_black[p]) * (Fore_R_black[p] - R_black[p]);
            }
        }
        //否则说明边界是曲线，此时为了凸显出曲线的方差大的特点，从第0行开始计算
        else
        {

            regression(2, 0, break_hangshu);    //拟合右线

            Cal_Line(k, b, 0, break_hangshu, 2);
            for (p = 0; p < break_hangshu - 5; p++)
            {
                rec += (Fore_R_black[p] - R_black[p]) * (Fore_R_black[p] - R_black[p]);
            }
        }
        return rec;
    }
    else return -1;
}

void Cal__estimator(uint8 type, uint8 startline, uint8 endline)
{
    int i = 0;
    endline = (uint8)My_Min((int)break_hangshu, (int)endline);
    int sumlines = endline - startline;
    float sum = 0;
    float average = 0;
    if (type == 0)   //拟合中线
    {
        for (i = startline; i <= endline; i++)
        {
            sum += LCenter[i];
        }
        if (sumlines != 0)
        {
            average = (float)sum / sumlines;     //x的平均值
        }
        else
        {
            average = 0;     //x的平均值                       //y的平均值
        }
        for (i = startline; i <= endline; i++)
        {
            rou_of_center += ((LCenter[i] - average) * (LCenter[i] - average));
        }
        if (sumlines != 0)
        {
            rou_of_center = (rou_of_center) / sumlines;
        }
        else rou_of_center = 0;

    }
    else if (type == 1)//拟合左线
    {
        shit(1, startline, endline);
        for (i = startline; i <= endline; i++)
        {

            sum += (L_black[i] - L_End[i]) * (L_black[i] - L_End[i]);
        }

        if (sumlines != 0)
        {
            rou_of_left = sum / sumlines;

        }
        else rou_of_left = 0;

    }
    else if (type == 2)//拟合右线
    {
        shit(2, startline, endline);
        for (i = startline; i <= endline; i++)
        {

            sum += (R_black[i] - R_End[i]) * (R_black[i] - R_End[i]);
        }
        if (sumlines != 0)
        {
            rou_of_right = sum / sumlines;
        }
        else rou_of_right = 0;

    }
}

void check_starting_line_l()
{
    if(flag_chuku == 0)
    {
        //int[] black_nums_stack = new int[20];
        uint8 times = 0;
        for (uint8 y = 26; y <= 39; y++)
        {
            uint8 black_blocks = 0;
            uint8 cursor = 0;    //指向栈顶的游标
            for (uint8 x = 0; x <= 185; x++)
            {
                if (Trans_Pixels(y,x) == 0)
                {
                    if (cursor >= 20)
                    {
                        //当黑色元素超过栈长度的操作   break;
                    }
                    else
                    {
                        cursor++;
                    }
                }
                else
                {
                    if (cursor >= 4 && cursor <= 8)
                    {
                        black_blocks++;
                        cursor = 0;
                    }
                    else
                    {
                        cursor = 0;
                    }
                }
            }
            if (black_blocks >= 6 && black_blocks <= 10) times++;
        }
        if (times >= 3 && times <= 7)
        {
            flag_starting_line = 1;
            ////////     ("进入起跑线状态");
        }
        else
        {
            flag_starting_line = 0;
        }
    }

}
void ruku_l()
{
    int rukudian = 0;
    if (flag_starting_line == 1 && flag_ruku <= 1) //还能找到斑马线
    {
        flag_ruku = 1;

        for (uint8 y = 60; y >= 1; y--)
        {
            for (uint8 x = 35; x < 182; x++)
            {
                if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x + 1) == 0 && Trans_Pixels(y,x + 2) == 0)
                {
                    L_End[y] = x;
                    break;
                }
            }
            if (L_End[y] - L_End[y + 1] >= 3 && y != 60)
            {
                ruku_guai_l[0] = (uint8)(y + 1);
                ruku_guai_l[1] = L_End[y + 1];

                ////////     ("车库左上拐点");
                ////////     ("   (" + ruku_guai_l[1] + "," + ruku_guai_l[0] + ")");
                break;
            }
        }
        if (ruku_guai_l[0] > 0)
        {
            float k_la = (ruku_guai_l[1] - 0) / (ruku_guai_l[0] - 0);
            float b_la = ruku_guai_l[1] - k_la * ruku_guai_l[0];
            for (uint8 i = 1; i < ruku_guai_l[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                R_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < ruku_guai_l[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }

        breakhang_hold(2, 15, ruku_guai_l[0]);
    }
    else if (flag_ruku == 1 || flag_ruku == 2) //已经找不到斑马线
    {
        flag_ruku = 2;
        ////////     ("入库状态" + flag_ruku);
        for (uint8 y = 60; y >= 1; y--)
        {
            for (uint8 x = 35; x < 182; x++)
            {
                if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x + 1) == 0 && Trans_Pixels(y,x + 2) == 0)
                {
                    L_End[y] = x;
                    break;
                }
            }
            if (L_End[y] - L_End[y + 1] >= 3 && y != 60)
            {
                ruku_guai_l[0] = (uint8)(y + 1);
                ruku_guai_l[1] = L_End[y + 1];

                ////////     ("车库左上拐点");
                ////////     ("   (" + ruku_guai_l[1] + "," + ruku_guai_l[0] + ")");
                break;
            }
        }
        if (ruku_guai_l[0] > 0)
        {
            float k_la = (ruku_guai_l[1] - 0) / (ruku_guai_l[0] - 0);
            float b_la = ruku_guai_l[1] - k_la * ruku_guai_l[0];
            for (uint8 i = 1; i < ruku_guai_l[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                R_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < ruku_guai_l[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }
        if (ruku_guai_l[0] <= 25 && ruku_guai_l[0] > 0)
        {
            flag_ruku = 3;
        }
        breakhang_hold(2, 15, ruku_guai_l[0]);
    }
    else if (flag_ruku == 3)
    {
        float k_la = (185 - 0) / (20 - 0);
        float b_mid = 185 - k_la * 20;
        for (uint8 i = 0; i < 60; i++)
        {
            int tool;
            tool = (int)(k_la * i + b_mid);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            LCenter[i] = tool;
        }
    }


}
void check_starting_line_r()
{
    if(flag_chuku == 0)
    {
        //int[] black_nums_stack = new int[20];
        uint8 times = 0;
        for (uint8 y = 28; y <= 39; y++)
        {
            uint8 black_blocks = 0;
            uint8 cursor = 0;    //指向栈顶的游标
            for (uint8 x = 183; x > 0; x--)
            {
                if (Trans_Pixels(y,x) == 0)
                {
                    if (cursor >= 20)
                    {
                        //当黑色元素超过栈长度的操作   break;
                    }
                    else
                    {
                        cursor++;
                    }
                }
                else
                {
                    if (cursor >= 4 && cursor <= 8)
                    {
                        black_blocks++;
                        cursor = 0;
                    }
                    else
                    {
                        cursor = 0;
                    }
                }
            }
            if (black_blocks >= 6 && black_blocks <= 10) times++;
        }
        if (times >= 3 && times <= 7)
        {
            flag_starting_line = 1;
            ////////     ("进入起跑线状态");
        }
        else
        {
            flag_starting_line = 0;
        }
    }

}
void ruku_r()
{
    int rukudian = 0;
    if (flag_starting_line == 1 && flag_ruku <= 1) //还能找到斑马线
    {
        flag_ruku = 1;

        for (uint8 y = 60; y >= 1; y--)
        {
            for (uint8 x = 150; x > 3; x--)
            {
                if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x - 1) == 0 && Trans_Pixels(y,x - 2) == 0)
                {
                    R_End[y] = x;
                    break;
                }
            }
            if (R_End[y+1] - R_End[y] >= 3 && y != 60)
            {
                ruku_guai_r[0] = (uint8)(y + 1);
                ruku_guai_r[1] = R_End[y + 1];

                ////////     ("车库右上拐点");
                ////////     ("   (" + ruku_guai_r[1] + "," + ruku_guai_r[0] + ")");
                break;
            }
        }
        if (ruku_guai_r[0] > 0)
        {
            float k_la = (ruku_guai_r[1] - 185) / (ruku_guai_r[0] - 0);
            float b_la = ruku_guai_r[1] - k_la * ruku_guai_r[0];
            for (uint8 i = 1; i < ruku_guai_r[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                L_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < ruku_guai_r[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }

        breakhang_hold(2, 15, ruku_guai_r[0]);
    }
    else if (flag_ruku == 1 || flag_ruku == 2) //已经找不到斑马线
    {
        flag_ruku = 2;
        ////////     ("入库状态" + flag_ruku);
        for (uint8 y = 60; y >= 1; y--)
        {
            for (uint8 x = 150; x > 3; x--)
            {
                if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x - 1) == 0 && Trans_Pixels(y,x - 2) == 0)
                {
                    R_End[y] = x;
                    break;
                }
            }
            if (R_End[y + 1] - R_End[y] >= 3 && y != 60)
            {
                ruku_guai_r[0] = (uint8)(y + 1);
                ruku_guai_r[1] = R_End[y + 1];

                ////////     ("车库右上拐点");
                ////////     ("   (" + ruku_guai_r[1] + "," + ruku_guai_r[0] + ")");
                break;
            }
        }
        if (ruku_guai_r[0] > 0)
        {
            float k_la = (ruku_guai_r[1] - 185) / (ruku_guai_r[0] - 0);
            float b_la = ruku_guai_r[1] - k_la * ruku_guai_r[0];
            for (uint8 i = 1; i < ruku_guai_r[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                L_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < ruku_guai_r[0]; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }
        if (ruku_guai_r[0] <= 25 && ruku_guai_r[0] > 0)
        {
            flag_ruku = 3;
        }
        breakhang_hold(2, 15, ruku_guai_r[0]);
    }
    else if (flag_ruku == 3)
    {
        float k_la = (0 - 185) / (20 - 0);
        float b_mid = 0 - k_la * 20;
        for (uint8 i = 0; i < 60; i++)
        {
            int tool;
            tool = (int)(k_la * i + b_mid);
            if (tool >= 185) tool = 185;
            if (tool <= 0) tool = 0;
            LCenter[i] = (uint8)tool;
        }
    }


}
void ruku(uint8 s)
{
    if (s == 1) //入左库
    {
        check_starting_line_l();
        if (flag_starting_line == 1 && flag_ruku <= 1) //还能找到斑马线
        {
            flag_ruku = 1;

            for (uint8 y = 60; y >= 1; y--)
            {
                for (uint8 x = 35; x < 182; x++)
                {
                    if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x + 1) == 0 && Trans_Pixels(y,x + 2) == 0)
                    {
                        L_End[y] = x;
                        break;
                    }
                }
                if (L_End[y] - L_End[y + 1] >= 3 && y != 60)
                {
                    ruku_guai_l[0] = (uint8)(y + 1);
                    ruku_guai_l[1] = L_End[y + 1];

                    ////////     ("车库左上拐点");
                    ////////     ("   (" + ruku_guai_l[1] + "," + ruku_guai_l[0] + ")");
                    break;
                }
            }
            if (ruku_guai_l[0] > 0)
            {
                float k_la = (ruku_guai_l[1] - 0) / (ruku_guai_l[0] - 0);
                float b_la = ruku_guai_l[1] - k_la * ruku_guai_l[0];
                for (uint8 i = 1; i < ruku_guai_l[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_la);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    R_black[i] = (uint8)tool;
                }
                float b_mid = LCenter[2] - k_la * 2;
                for (uint8 i = 0; i < ruku_guai_l[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_mid);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    LCenter[i] = (uint8)tool;
                }
            }

            breakhang_hold(2, 15, ruku_guai_l[0]);
        }
        else if (flag_ruku == 1 || flag_ruku == 2) //已经找不到斑马线
        {
            flag_ruku = 2;
            ////////     ("入库状态" + flag_ruku);
            for (uint8 y = 60; y >= 1; y--)
            {
                for (uint8 x = 35; x < 182; x++)
                {
                    if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x + 1) == 0 && Trans_Pixels(y,x + 2) == 0)
                    {
                        L_End[y] = x;
                        break;
                    }
                }
                if (L_End[y] - L_End[y + 1] >= 3 && y != 60)
                {
                    ruku_guai_l[0] = (uint8)(y + 1);
                    ruku_guai_l[1] = L_End[y + 1];

                    ////////     ("车库左上拐点");
                    ////////     ("   (" + ruku_guai_l[1] + "," + ruku_guai_l[0] + ")");
                    break;
                }
            }
            if (ruku_guai_l[0] > 0)
            {
                float k_la = (ruku_guai_l[1] - 0) / (ruku_guai_l[0] - 0);
                float b_la = ruku_guai_l[1] - k_la * ruku_guai_l[0];
                for (uint8 i = 1; i < ruku_guai_l[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_la);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    R_black[i] = (uint8)tool;
                }
                float b_mid = LCenter[2] - k_la * 2;
                for (uint8 i = 0; i < ruku_guai_l[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_mid);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    LCenter[i] = (uint8)tool;
                }
            }
            if (ruku_guai_l[0] <= 25 && ruku_guai_l[0] > 0)
            {
                flag_ruku = 3;
            }
            breakhang_hold(2, 15, ruku_guai_l[0]);
        }
        else if (flag_ruku == 3)
        {
            float k_la = (185 - 0) / (20 - 0);
            float b_mid = 185 - k_la * 20;
            for (uint8 i = 0; i < 60; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }

    }
    else if (s == 2) //入右库
    {
        check_starting_line_r();
        if (flag_starting_line == 1 && flag_ruku <= 1) //还能找到斑马线
        {
            flag_ruku = 1;

            for (uint8 y = 60; y >= 1; y--)
            {
                for (uint8 x = 150; x > 3; x--)
                {
                    if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x - 1) == 0 && Trans_Pixels(y,x - 2) == 0)
                    {
                        R_End[y] = x;
                        break;
                    }
                }
                if (R_End[y + 1] - R_End[y] >= 3 && y != 60)
                {
                    ruku_guai_r[0] = (uint8)(y + 1);
                    ruku_guai_r[1] = R_End[y + 1];

                    ////////     ("车库右上拐点");
                    ////////     ("   (" + ruku_guai_r[1] + "," + ruku_guai_r[0] + ")");
                    break;
                }
            }
            if (ruku_guai_r[0] > 0)
            {
                float k_la = (ruku_guai_r[1] - 185) / (ruku_guai_r[0] - 0);
                float b_la = ruku_guai_r[1] - k_la * ruku_guai_r[0];
                for (uint8 i = 1; i < ruku_guai_r[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_la);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    L_black[i] = (uint8)tool;
                }
                float b_mid = LCenter[2] - k_la * 2;
                for (uint8 i = 0; i < ruku_guai_r[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_mid);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    LCenter[i] = (uint8)tool;
                }
            }

            breakhang_hold(2, 15, ruku_guai_r[0]);
        }
        else if (flag_ruku == 1 || flag_ruku == 2) //已经找不到斑马线
        {
            flag_ruku = 2;
            ////////     ("入库状态" + flag_ruku);
            for (uint8 y = 60; y >= 1; y--)
            {
                for (uint8 x = 150; x > 3; x--)
                {
                    if (Trans_Pixels(y,x) != 0 && Trans_Pixels(y,x - 1) == 0 && Trans_Pixels(y,x - 2) == 0)
                    {
                        R_End[y] = x;
                        break;
                    }
                }
                if (R_End[y + 1] - R_End[y] >= 3 && y != 60)
                {
                    ruku_guai_r[0] = (uint8)(y + 1);
                    ruku_guai_r[1] = R_End[y + 1];

                    ////////     ("车库右上拐点");
                    ////////     ("   (" + ruku_guai_r[1] + "," + ruku_guai_r[0] + ")");
                    break;
                }
            }
            if (ruku_guai_r[0] > 0)
            {
                float k_la = (ruku_guai_r[1] - 185) / (ruku_guai_r[0] - 0);
                float b_la = ruku_guai_r[1] - k_la * ruku_guai_r[0];
                for (uint8 i = 1; i < ruku_guai_r[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_la);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    L_black[i] = (uint8)tool;
                }
                float b_mid = LCenter[2] - k_la * 2;
                for (uint8 i = 0; i < ruku_guai_r[0]; i++)
                {
                    int tool;
                    tool = (int)(k_la * i + b_mid);
                    if (tool >= 185) tool = 185;
                    if (tool <= 0) tool = 0;
                    LCenter[i] = (uint8)tool;
                }
            }
            if (ruku_guai_r[0] <= 25 && ruku_guai_r[0] > 0)
            {
                flag_ruku = 3;
            }
            breakhang_hold(2, 15, ruku_guai_r[0]);
        }
        else if (flag_ruku == 3)
        {
            float k_la = (0 - 185) / (20 - 0);
            float b_mid = 0 - k_la * 20;
            for (uint8 i = 0; i < 60; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }
    }
}
void fork(int16 dir)
{
    if (flag_ruku == 0 && flag_podao == 0 && flag_chuku == 0 && flag_roundabout == 0)
    {
        int min_V_y = 69;
        int min_V_x = 185;
        if (dir == 1)
        {

            if (status_forkroad == 0) //&& (left_turn_down[0] > 0 || right_turn_down[0] > 0)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                for (int i = right_turn_down[1]; i < left_turn_down[1]; i++)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]) + 5; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            v_guai[i] = (uint8)j;
                            if (j <  min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (right_turn_down[0] > 6)
                {
                    right_turn_down[0] = (uint8)(right_turn_down[0] - 5);
                    right_turn_down[1] = R_black[right_turn_down[0]];
                }

                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
                if (left_turn_down[0] > 0 && right_turn_down[0] > 0 && Trans_Pixels(55,92) == 0 && Trans_Pixels(60,92) == 0 && Trans_Pixels(60,70) == 0 && Trans_Pixels(60,110) == 0 && min_V_x > 45 && min_V_x < 130 && L_black[min_V_y - 5] > 175 && R_black[min_V_y - 5] < 10 && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                {
                        flag_forkroad = 1;
                        status_forkroad = 1;

                        //SetText("正入三叉");
                }
                //else if (BinPixels[50][50] == 0 && BinPixels[60][50] == 0 && (r_start > 30 || rou_of_right > 1500) && min_V_x > 25 && min_V_x < 130 && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x] - v_guai[min_V_x - 20] <= 2 && v_guai[min_V_x + 20] - v_guai[min_V_x] >= 2 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                //{
                //    flag_forkroad = 1;
                //    status_forkroad = 1;
                //    //SetText("左斜入三叉");
                //}

                else if (Trans_Pixels(55,92)==0 && (l_start > 30 || rou_of_left > 1500) && min_V_y <35 && min_V_x > 25 && min_V_x < 130 && right_turn_down[0] > 3)
                {
                    k = b = 0;
                    regression(2, 0, right_turn_down[0] - 3);
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        R_Start[i] = (uint8)(k * i + b);
                    }

                    if (R_Start[min_V_y] - min_V_x < -15 && (R_Start[min_V_y] - min_V_x > -40 || (left_turn_down[0] < 25 && left_turn_down[0] > 0 && right_turn_down [0] < 45) ))
                    {
                        flag_forkroad = 1;
                        status_forkroad = 1;
                        //SetText("右斜入三叉");
                    }
                }
                else if (Trans_Pixels(55,92)==0 && (r_start > 30 || rou_of_right > 1500) && min_V_x > 10 && min_V_x < 130 && left_turn_down[0] > 3)
                {
                    k = b = 0;
                    regression(1, 0, left_turn_down[0] - 3);
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        R_Start[i] = (uint8)(k * i + b);
                    }
                    if (R_Start[min_V_y] - min_V_x > 15)
                    {
                        flag_forkroad = 1;
                        status_forkroad = 1;
                        //SetText("左斜入三叉");
                    }
                }
                //else if (l_start > 30 && min_V_x > 65 && min_V_x < 170 && right_turn_down[0] > 3)
                //{
                //    k = b = 0;
                //    regression(2, 0, right_turn_down[0] - 3);
                //    for (int i = 0; i <= min_V_y; i++)
                //    {
                //        R_Start[i] = (uint8)(k * i + b);
                //    }
                //    setText用户自定义("差值为" + (R_Start[min_V_y] - min_V_x));
                //    if (R_Start[min_V_y] - min_V_x < -15)
                //    {
                //        flag_forkroad = 1;
                //        status_forkroad = 1;
                //        //SetText("右斜入三叉");
                //    }
                //}


            }
            else if (status_forkroad == 1) //&& (left_turn_down[0] == 0 || right_turn_down[0] == 0 || min_V_y <= 30)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");



                for (int i = right_turn_down[1] ; i < left_turn_down[1] - 5; i++)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0 && j > 10)
                        {
                            v_guai[i] = (uint8)j;
                            if (j <=  min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (right_turn_down[0] > 6)
                {
                    right_turn_down[0] = (uint8)(right_turn_down[0] - 5);
                    right_turn_down[1] = R_black[right_turn_down[0]];
                }
                //SetText("右线斜率");
                //SetText(r_k);



                if (l_start > 10 ) status_forkroad = 2;

                //SetText("三叉状态1");
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);

            }
            else if (status_forkroad == 2)
            {
                for (int i = 160; i > 25; i--)
                {
                    for (int j = 20; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            if (j <=  min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (width[5] < 170 && min_V_y < 25 && right_turn_down[0] < 5 ) status_forkroad = 3; //判断是否已经进入支路
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
                //SetText("三叉状态2 入三叉口");

            }
            else if (status_forkroad == 3)
            {
                //SetText("三叉状态3 正常扫线");
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                if (right_turn_down[0] > 6)
                {
                    right_turn_down[0] = (uint8)(right_turn_down[0] - 5);
                    right_turn_down[1] = R_black[right_turn_down[0]];
                }

                for (int i = right_turn_down[1] + 10 ; i < left_turn_down[1] - 5; i++)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0 )
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
                 if ((r_start > 30 || rou_of_right > 1500) && min_V_x > 20 && min_V_x < 165 && Trans_Pixels(min_V_y - 2,min_V_x - 15)!= 0
                         && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x] - v_guai[min_V_x - 15] <= 3
                         && v_guai[min_V_x + 15] - v_guai[min_V_x] >= 2 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                {
                    status_forkroad = 4;
                    //SetText("出三叉");
                }
                else if (left_turn_down[0] > 0 && right_turn_down[0] > 0)
                {
                    if (Trans_Pixels(55,92) == 0 && Trans_Pixels(60,92) == 0 && (Trans_Pixels(60,70) == 0|| Trans_Pixels(65,65) == 0) && (Trans_Pixels(60,110) == 0||Trans_Pixels(65,100) == 0)
                            && min_V_x>20 &&min_V_x <170 && L_black[min_V_y - 5] > 175 && R_black[min_V_y - 5] < 10 && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                    {
                        status_forkroad = 4;
                        //SetText("正出三叉");
                    }
                }

            }
            else if (status_forkroad == 4)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                if (right_turn_down[0] > 6)
                {
                    right_turn_down[0] = (uint8)(right_turn_down[0] - 5);
                    right_turn_down[1] = R_black[right_turn_down[0]];
                }

                for (int i = left_turn_down[1]; i > right_turn_down[1]; i--)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0 && j > 25 )
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (l_start > 10 ) status_forkroad = 5;

            }
            else if (status_forkroad == 5)
            {
                for (int i = 160; i > 25; i--)
                {
                    for (int j = 20; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (width[5] < 170 && min_V_y < 25) status_forkroad = 6; //判断是否已经进入支路
                //SetText("三叉状态5 出三叉口");
            }

            if (status_forkroad == 1 || status_forkroad == 4)
            {
                if (left_turn_down[0] > 0 && right_turn_down[0] > 0)
                {
                    if (right_turn_down[0] - min_V_y != 0) k = (right_turn_down[1] - min_V_x) / (right_turn_down[0] - min_V_y);
                    else k = 0;
                    b = min_V_x - k * min_V_y;
                    for (int i = right_turn_down[0]; i <= min_V_y; i++)
                    {
                        R_black[i] = (uint8)(k * i + b);

                    }
                }
                else if (left_turn_down[0] == 0 || right_turn_down[0] == 0 || min_V_y <= 30)
                {
                    if (min_V_y != 0) k = (0 - min_V_x) / (0 - min_V_y);
                    else k = 0;
                    b = min_V_x - k * min_V_y;
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        int temp = (int)(k * i + b);
                        if (temp > 185) temp = 185;
                        else if (temp < 0) temp = 0;
                        R_black[i] = (uint8)temp;

                    }
                }
                else if (left_turn_down[0] > 0 && right_turn_down[0] == 0)
                {
                    k = (right_turn_down[1] - min_V_x) / (right_turn_down[0] - min_V_y);
                    b = min_V_x - k * min_V_y;
                    for (int i = right_turn_down[0]; i <= min_V_y; i++)
                    {
                        R_black[i] = (uint8)(k * i + b);

                    }
                }
                else
                {
                    k = (0 - min_V_x) / (0 - min_V_y);
                    b = min_V_x - k * min_V_y;
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        R_black[i] = (uint8)(k * i + b);

                    }
                }
            }
            else if (status_forkroad == 2 || status_forkroad == 5)
            {
                if (min_V_y != 0) k = (0 - min_V_x) / (0 - min_V_y);
                else k = 0;
                b = min_V_x - k * min_V_y;
                for (int i = 0; i <= min_V_y; i++)
                {
                    R_black[i] = (uint8)(k * i + b);

                }
            }
            else if (status_forkroad == 3)
            {

            }
            else if (status_forkroad == 6)
            {
                status_forkroad = flag_forkroad = 0;
            }

        }
        else if (dir == 2)
        {
            if (status_forkroad == 0) // && (left_turn_down[0] > 0 || right_turn_down[0] > 0)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                if (left_turn_down[0] > 6)
                {
                    left_turn_down[0] = (uint8)(left_turn_down[0] - 5);
                    left_turn_down[1] = L_black[left_turn_down[0]];
                }


                for (int i = left_turn_down[1]; i > right_turn_down[1]; i--)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0])+5; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
                if (left_turn_down[0] > 0 && right_turn_down[0] > 0 && Trans_Pixels(55,92) == 0 &&  Trans_Pixels(60,92) == 0 &&  Trans_Pixels(60,70) == 0 && Trans_Pixels(60,110) == 0 && min_V_x > 45 && min_V_x < 130 && L_black[min_V_y - 5] > 175 && R_black[min_V_y - 5] < 10  && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3 )
                {
                        flag_forkroad = 1;
                        status_forkroad = 1;
                        //SetText("正入三叉");
                }
                else if (Trans_Pixels(55,92)==0 && (l_start > 30 || rou_of_left > 1500) && min_V_x > 25 && min_V_x < 130 && right_turn_down[0] > 3)
                {
                    k = b = 0;
                    regression(2, 0, right_turn_down[0] - 3);
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        R_Start[i] = (uint8)(k * i + b);
                    }

                    if (R_Start[min_V_y] - min_V_x < -15)
                    {
                        flag_forkroad = 1;
                        status_forkroad = 1;
                        //SetText("右斜入三叉");
                    }
                }
                //else if (BinPixels[50][135] == 0 && BinPixels[60][135] == 0 && (l_start > 30 || rou_of_left > 1500) && min_V_x > 25 && min_V_x < 130 && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] >= 1 && v_guai[min_V_x + 15] - v_guai[min_V_x] <= 3 && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 20] - v_guai[min_V_x] >= 2 && v_guai[min_V_x - 20] - v_guai[min_V_x] <= 15)
                //{
                //    flag_forkroad = 1;
                //    status_forkroad = 1;
                //    //SetText("右斜入三叉");

                //}
                else if (Trans_Pixels(55,92)==0 && (r_start > 30 || rou_of_right > 1500) && min_V_y < 35 && min_V_x > 10 && min_V_x < 130 && left_turn_down[0] > 3)
                {
                    k = b = 0;
                    regression(1, 0, left_turn_down[0] - 3);
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        R_Start[i] = (uint8)(k * i + b);
                    }
                    if (R_Start[min_V_y] - min_V_x > 15 && (R_Start[min_V_y] - min_V_x <40 || (right_turn_down[0] < 30 && right_turn_down[0] > 0 && left_turn_down[0] < 45)))
                    {
                        flag_forkroad = 1;
                        status_forkroad = 1;
                        //SetText("左斜入三叉");
                    }
                }
                //else if (BinPixels[50][50] == 0 && BinPixels[60][50] == 0 && r_start > 30 && min_V_y > 20 && min_V_x > 25 && min_V_x < 130 && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x] - v_guai[min_V_x - 15] <= 3 && v_guai[min_V_x - 20] - v_guai[min_V_x] <= 2 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                //{
                //    flag_forkroad = 1;
                //    status_forkroad = 1;
                //    //SetText("左斜入三叉");
                //}
            }
            else if (status_forkroad == 1) //&& (left_turn_down[0] == 0 || right_turn_down[0] == 0 ||  min_V_y <= 30)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                if (left_turn_down[0] > 6)
                {
                    left_turn_down[0] = (uint8)(left_turn_down[0] - 5);
                    left_turn_down[1] = L_black[left_turn_down[0]];
                }

                for (int i = left_turn_down[1]; i > right_turn_down[1] + 5; i--)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0 && j > 10)
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                float l_k = regression(1, 2, 56);
                //SetText("左线斜率");
                //SetText(l_k);

                if (r_start > 10) status_forkroad = 2;

                //SetText("三叉状态1");
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);



            }
            else if (status_forkroad == 2)
            {
                for (int i = 160; i > 25; i--)
                {
                    for (int j = 20; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (width[5] < 170 && min_V_y < 25) status_forkroad = 3; //判断是否已经进入支路
                //SetText("三叉状态2");
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
            }
            else if (status_forkroad == 3)
            {
                //SetText("三叉状态3 正常扫线");
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");



                for (int i = left_turn_down[1] - 10; i > right_turn_down[1] + 5; i--)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);

                if (left_turn_down[0] > 6)
                {
                    left_turn_down[0] = (uint8)(left_turn_down[0] - 5);
                    left_turn_down[1] = L_black[left_turn_down[0]];
                }

                if ( (l_start > 30 || rou_of_left > 1500) && min_V_x > 20 && min_V_x < 165 && Trans_Pixels(min_V_y - 2,min_V_x - 15)!= 0
                        && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] >= 1 && v_guai[min_V_x + 15] - v_guai[min_V_x] <= 3
                        && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 15] - v_guai[min_V_x] >= 2 )
                {
                    status_forkroad = 4;
                    //SetText("出三叉");
                }
                else if (left_turn_down[0] > 0 && right_turn_down[0] > 0)
                {
                    if (Trans_Pixels(55,92) == 0 && Trans_Pixels(60,92) == 0 && (Trans_Pixels(60,70) == 0 || Trans_Pixels(65,65) == 0) && (Trans_Pixels(60,110) == 0 || Trans_Pixels(65,100) == 0)
                            && min_V_x>20 &&min_V_x <170&& L_black[min_V_y - 5] > 175 && R_black[min_V_y - 5] < 10 && v_guai[min_V_x + 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x - 1] - v_guai[min_V_x] <= 1 && v_guai[min_V_x + 4] - v_guai[min_V_x] <= 3 && v_guai[min_V_x - 4] - v_guai[min_V_x] <= 3)
                    {
                        status_forkroad = 4;
                        //SetText("正出三叉");
                    }
                }
            }
            else if (status_forkroad == 4)
            {
                find_rightdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);
                find_leftdown_point(10, (uint8)My_Min(45, (int)break_hangshu), 1);

                //SetText("左下拐点       " + "右下拐点         ");
                //SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                if (left_turn_down[0] > 6)
                {
                    left_turn_down[0] = (uint8)(left_turn_down[0] - 5);
                    left_turn_down[1] = L_black[left_turn_down[0]];
                }

                for (int i = left_turn_down[1]; i > right_turn_down[1] + 5; i--)
                {
                    for (int j = My_Max(left_turn_down[0], right_turn_down[0]); j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0 && j > 10 )
                        {
                            v_guai[i] = (uint8)j;
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                float l_k = regression(1, 2, 56);
                //SetText("左线斜率");
                //SetText(l_k);

                if (r_start > 10 || l_k > -0.1 && l_k < 0) status_forkroad = 5;

                //SetText("三叉状态4 出三叉");
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
            }
            else if (status_forkroad == 5)
            {

                for (int i = 160; i > 25; i--)
                {
                    for (int j = 20; j < 68; j++)
                    {
                        if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j+1,i) == 0)
                        {
                            if (j <= min_V_y)
                            {
                                min_V_y = j;
                                min_V_x = i;
                            }

                            break;
                        }
                    }
                }

                if (width[5] < 170 && min_V_y < 25) status_forkroad = 6; //判断是否已经进入支路
                //SetText("三叉状态5 出三叉");
                //SetText("“V”拐点最低点为" + min_V_x + "  " + min_V_y);
            }

            if (status_forkroad == 1 || status_forkroad == 4)
            {
                if (left_turn_down[0] > 0 && right_turn_down[0] > 0)
                {
                    k = (left_turn_down[1] - min_V_x) / (left_turn_down[0] - min_V_y);
                    b = min_V_x - k * min_V_y;
                    for (int i = left_turn_down[0]; i <= min_V_y; i++)
                    {
                        L_black[i] = (uint8)(k * i + b);

                    }
                }
                else if (left_turn_down[0] == 0 || right_turn_down[0] == 0 || min_V_y <= 30)
                {
                    if (min_V_y != 0) k = (185 - min_V_x) / (0 - min_V_y);
                    else k = 0;
                    b = min_V_x - k * min_V_y;
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        int temp = (int)(k * i + b);
                        if (temp > 185) temp = 185;
                        else if (temp < 0) temp = 0;
                        L_black[i] = (uint8)temp;
                    }
                }
                else if (left_turn_down[0] > 0 && right_turn_down[0] == 0)
                {
                    k = (left_turn_down[1] - min_V_x) / (left_turn_down[0] - min_V_y);
                    b = min_V_x - k * min_V_y;
                    for (int i = left_turn_down[0]; i <= min_V_y; i++)
                    {
                        L_black[i] = (uint8)(k * i + b);

                    }
                }
                else
                {
                    if (min_V_y != 0) k = (185 - min_V_x) / (0 - min_V_y);
                    else k = 0;
                    b = min_V_x - k * min_V_y;
                    for (int i = 0; i <= min_V_y; i++)
                    {
                        L_black[i] = (uint8)(k * i + b);

                    }
                }
            }
            else if (status_forkroad == 2 || status_forkroad == 5)
            {
                if (min_V_y != 0) k = (185 - min_V_x) / (0 - min_V_y);
                else k = 0;
                b = min_V_x - k * min_V_y;
                for (int i = 0; i <= min_V_y; i++)
                {
                    L_black[i] = (uint8)(k * i + b);

                }
            }
            else if (status_forkroad == 3 )
            {

            }
            else if (status_forkroad == 6)
            {
                status_forkroad = flag_forkroad = 0;
            }
        }

        for (uint8 j = 0; j <= break_hangshu; j++)
        {
            LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);
        }
        if (min_V_y >= 25)
        {
            breakhang_hold(2, 15, (uint8)My_Min(break_hangshu, min_V_y));
        }
        else
        {
            breakhang_hold(2, 15, break_hangshu);
        }
    }
}

void chuku(uint8 s)
{
    if (s == 2) //出右库 入右库
    {
        rou_of_left = rou_of_right = 0;
        Cal__estimator(1, 1, 45);
        Cal__estimator(2, 1, 45);

        ////////     ("左线方差为:" + rou_of_left);
        ////////     ("右线方差为:" + rou_of_right);

        if (rou_of_left < 5 && r_start < 30 && l_start < 5)
        {
            flag_chuku = 0;
        }
        if (flag_chuku == 1)
        {
            float k_la = (0 - 185) / (break_hangshu - 0);
            float b_la = 0 - k_la * break_hangshu;
            for (uint8 i = 1; i < break_hangshu; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                L_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < break_hangshu; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }
    }
    else if(s == 1) //出左库 入左库
    {
        rou_of_left = rou_of_right = 0;
        Cal__estimator(1, 1, 45);
        Cal__estimator(2, 1, 45);

        ////////     ("左线方差为:" + rou_of_left);
        ////////     ("右线方差为:" + rou_of_right);

        if (rou_of_right < 5 && l_start < 30 && r_start < 5)
        {
            flag_chuku = 0;
        }

        if (flag_chuku == 1)
        {
            float k_la = (185 - 0) / (break_hangshu - 0);
            float b_la = 185 - k_la * break_hangshu;
            for (uint8 i = 1; i < break_hangshu; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_la);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                R_black[i] = (uint8)tool;
            }
            float b_mid = LCenter[2] - k_la * 2;
            for (uint8 i = 0; i < break_hangshu; i++)
            {
                int tool;
                tool = (int)(k_la * i + b_mid);
                if (tool >= 185) tool = 185;
                if (tool <= 0) tool = 0;
                LCenter[i] = (uint8)tool;
            }
        }
    }


}
void crossroad()
{
    if (flag_roundabout == 0 && flag_ruku == 0 && flag_podao == 0 && flag_chuku == 0 && flag_forkroad == 0)
    {
        ////////////SetText("***************************十字扫线*************************");
        ////////////SetText("**************************寻找下拐点************************");
        find_leftdown_point(8, 45, 0);
        find_rightdown_point(8, 45, 0);
        ////////////SetText("左下拐点       " + "右下拐点         ");
        ////////////SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

        //find_leftup_point((uint8)My_Max(left_turn_down[0],13), 60, 0);
        //find_rightup_point((uint8)My_Max(right_turn_down[0], 13), 60, 0);
        //////////////SetText("左上拐点       " + "右上拐点         ");
        //////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")          (" + right_turn_up[1] + "," + right_turn_up[0] + ")");
        //////////////SetText("   ");

        if (left_turn_down[0] > 8 || right_turn_down[0] > 8) // 发现下拐点
        {

            int j = 0;
            int i = 0;

            //左右拐点都存在
            if (left_turn_down[0] != 0 && right_turn_down[0] != 0)
            {
                L_Cur = regression(1, left_turn_down[0] - 5, left_turn_down[0] + 2);
                R_Cur = regression(2, right_turn_down[0] - 5, right_turn_down[0] + 2);
            }
            //只有左拐点
            else if (left_turn_down[0] != 0 && right_turn_down[0] == 0)
            {
                L_Cur = regression(1, left_turn_down[0] - 5, left_turn_down[0] + 2);
                R_Cur = regression(2, left_turn_down[0] - 5, left_turn_down[0] + 2);
            }
            //只有右拐点
            else if (left_turn_down[0] == 0 && right_turn_down[0] != 0)
            {
                L_Cur = regression(1, right_turn_down[0] - 5, right_turn_down[0] + 2);
                R_Cur = regression(2, right_turn_down[0] - 5, right_turn_down[0] + 2);
            }

            ////////////SetText("左线斜率      " + "右线斜率    ");
            ////////////SetText(L_Cur + "          " + R_Cur);


            //两线斜率判断是否弯道
            if (L_Cur < 0 && R_Cur < 0 || L_Cur > 0 && R_Cur > 0)
            {
                flag_bend = 1;
                ////////////SetText("此时是弯道");
            }
            else if (L_Cur * R_Cur <= 0)
            {
                flag_crossroad = 1;
                ////////////SetText("此时是十字");
                rou_of_left = rou_of_right = 0;
                Cal__estimator(1, 5, 50);
                Cal__estimator(2, 5, 50);
                ////////////SetText("直线状态下方差为:");
                ////////////SetText("左线方差为:" + rou_of_left);
                ////////////SetText("右线方差为:" + rou_of_right);
                //左斜入十字  ************************LCenter[line] line直接给定 需要修改**************
                if (left_turn_down[0] != 0 && right_turn_down[0] == 0)
                {
                    ////////////SetText("**************左斜入十字********");
                    flag_left_cross = 1;
                    regression(0, left_turn_down[0] - 8, left_turn_down[0] - 3);
                    k = k - 0.15f;
                    Drew_Line(k, b, left_turn_down[0] - 8, 60, 0);
                    //regression(1, left_turn_down[0] - 8, left_turn_down[0] - 3);
                    //Drew_Line(k, b, left_turn_down[0] - 8, 55, 1);
                    for (j = left_turn_down[0] - 8; j <= 60; j++)
                    {
                        leftfindflag[j] = 0;
                        rightfindflag[j] = 0;
                        for (i = L_End[j]; i >= 0 && i < 185; i++)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                leftfindflag[j] = 1;
                                L_black[j] = (uint8)i;
                                break;
                            }
                        }
                        for (i = L_End[j]; i <= 185 && i > 0; i--)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                rightfindflag[j] = 1;
                                R_black[j] = (uint8)i;
                                break;
                            }
                        }
                        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);
                    }
                    find_leftup_point(left_turn_down[0], 60, 0);
                    ////////////SetText("真实左上拐点为:" + left_turn_up[1] + "," + left_turn_up[0]);
                    //right_turn_up[0] = 0;
                    //right_turn_up[1] = 185;
                    find_rightup_point((uint8)(left_turn_up[0] - 20), 50, 0);

                    flag_left_cross = 1;
                }
                //右斜入十字
                else if (left_turn_down[0] == 0 && right_turn_down[0] != 0)
                {
                    ////////////SetText("**************右斜入十字********");
                    flag_right_cross = 1;
                    regression(0, 2, 8);
                    k = k + 0.15f;
                    Drew_Line(k, b, 2, 60, 0);
                    //regression(2, right_turn_down[0] - 8, right_turn_down[0] - 3);
                    //Drew_Line(k, b, right_turn_down[0] - 8, 55, 2);
                    for (j = 2; j <= 60; j++)
                    {
                        leftfindflag[j] = 0;
                        rightfindflag[j] = 0;
                        int s = My_Min((int)L_End[j], 183);
                        for (i = s; i >= 0 && i < 185; i++)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                leftfindflag[j] = 1;
                                L_black[j] = (uint8)i;
                                break;
                            }
                        }
                        for (i = s; i <= 185 && i > 0; i--)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                rightfindflag[j] = 1;
                                R_black[j] = (uint8)i;
                                break;
                            }
                        }
                        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);
                    }
                    ////////////SetText("breakhangshu" + break_hangshu);
                    find_rightup_point(right_turn_down[0], 60, 0);
                    ////////////SetText("真实右上拐点为:" + right_turn_up[1] + "," + right_turn_up[0]);
                    //left_turn_up[0] = 0;
                    //left_turn_up[1] = 185;
                    find_leftup_point((uint8)(right_turn_up[0] - 20), 50, 0);

                    flag_right_cross = 1;
                }
                //正入十字
                else if (left_turn_down[0] != 0 && right_turn_down[0] != 0) //最后一个判断弯道的条件需要修改
                {

                    ////////////SetText("正入十字");
                    k = regression(0, My_Min(left_turn_down[0], right_turn_down[0]) - 5, My_Min(left_turn_down[0], right_turn_down[0]));
                    b = 1 * b;
                    for (j = My_Min(left_turn_down[0], right_turn_down[0]); j < 69; j++)
                    {
                        L_End[j] = (uint8)(k * j + b);
                        width[j] = 0;
                        L_black[j] = 185;
                        R_black[j] = 0;
                    }
                    for (j = My_Min(left_turn_down[0], right_turn_down[0]); j < 69; j++)
                    {
                        for (i = L_End[j]; i >= 0 && i < 184; i++)
                        {
                            width[j]++;
                            if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j,i+1) == 0)
                            {
                                leftfindflag[j] = 1;
                                L_black[j] = (uint8)i;
                                break;
                            }
                        }
                        for (i = L_End[j]; i <= 185 && i > 1; i--)
                        {
                            width[j]++;
                            if (Trans_Pixels(j,i) == 0 && Trans_Pixels(j,i-1) == 0)
                            {
                                rightfindflag[j] = 1;
                                R_black[j] = (uint8)i;
                                break;
                            }
                        }
                        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);

                        if ((Trans_Pixels(j,LCenter[j]) == 0) && (Trans_Pixels(j+1,LCenter[j]) == 0))
                        {
                            break_hangshu = (uint8)j;
                            if (break_hangshu >= 13 && status_roundabout != 5 && status_roundabout != 6)    //防止在一开始就break
                            {
                                break;
                            }
                        }
                        else break_hangshu = 69;
                    }
                    find_leftup_point(left_turn_down[0], 50, 0);

                    find_rightup_point(right_turn_down[0], 50, 0);
                    ////////////SetText("真实左上拐点为:" + left_turn_up[1] + "," + left_turn_up[0]);
                    ////////////SetText("真实右上拐点为:" + right_turn_up[1] + "," + right_turn_up[0]);


                }


                ////////////SetText("左上拐点       " + "右上拐点         ");
                ////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")          (" + right_turn_up[1] + "," + right_turn_up[0] + ")");
                ////////////SetText("   ");

                //拉线
                //左边拉线
                if (left_turn_up[0] != 0 && left_turn_down[0] != 0 && left_turn_up[0] > left_turn_down[0] && flag_right_cross != 1)
                {

                    k = (float)(left_turn_up[1] - left_turn_down[1]) / (left_turn_up[0] - left_turn_down[0]);
                    b = left_turn_up[1] - k * left_turn_up[0];

                    for (j = left_turn_down[0] - 5; j < left_turn_up[0]; j++)
                    {
                        int tool;
                        tool = (int)(k * j + b);
                        if (tool >= 185) tool = 185;
                        if (tool <= 0) tool = 0;
                        L_black[j] = (uint8)tool;

                    }
                }
                else if (left_turn_up[0] != 0 && left_turn_down[0] == 0 && flag_right_cross != 1)
                {
                    regression(1, left_turn_up[0], left_turn_up[0] + 5);

                    for (j = 0; j < left_turn_up[0]; j++)
                    {
                        int tool;
                        tool = (int)(k * j + b);
                        if (tool >= 185)
                        {
                            tool = 185;
                        }
                        if (tool <= 0)
                        {
                            tool = 0;
                        }
                        L_black[j] = (uint8)tool;
                    }
                }
                else if (flag_right_cross == 1)
                {
                    if (left_turn_up[1] - right_turn_up[1] > 10)
                    {
                        regression(1, left_turn_up[0], left_turn_up[0] + 5);

                        for (j = 0; j < left_turn_up[0]; j++)
                        {
                            int tool;
                            tool = (int)(k * j + b);
                            if (tool >= 185) tool = 185;
                            if (tool <= 0) tool = 0;

                            L_black[j] = (uint8)tool;
                        }
                    }
                    else
                    {
                        for (j = 0; j < 70; j++)
                        {
                            L_black[j] = 185;
                        }
                    }
                }


                //右边拉线
                if (right_turn_up[0] != 0 && right_turn_down[0] != 0 && right_turn_up[0] > right_turn_down[0] && flag_left_cross != 1)
                {
                    k = (float)(right_turn_up[1] - right_turn_down[1]) / (right_turn_up[0] - right_turn_down[0]);
                    b = right_turn_up[1] - k * right_turn_up[0];
                    //advanced_regression(2, right_turn_down[0] - 8, right_turn_down[0], right_turn_up[0], right_turn_up[0] + 2);
                    for (j = right_turn_down[0] - 5; j < right_turn_up[0] + 2; j++)
                    {
                        int tool;
                        tool = (int)(k * j + b);
                        if (tool >= 185) tool = 185;
                        if (tool <= 0) tool = 0;
                        R_black[j] = (uint8)tool;
                    }
                }
                else if (right_turn_up[0] != 0 && right_turn_down[0] == 0 && flag_left_cross != 1)
                {
                    regression(2, right_turn_up[0], right_turn_up[0] + 5);

                    for (j = 0; j < right_turn_up[0]; j++)
                    {
                        int tool;
                        tool = (int)(k * j + b);
                        if (tool >= 185) tool = 185;
                        if (tool <= 0) tool = 0;
                        R_black[j] = (uint8)tool;
                    }
                }
                else if (flag_left_cross == 1)
                {
                    if (left_turn_up[1] - right_turn_up[1] > 10)
                    {
                        regression(2, right_turn_up[0], right_turn_up[0] + 5);

                        for (j = 0; j < right_turn_up[0]; j++)
                        {
                            int tool;
                            tool = (int)(k * j + b);
                            if (tool >= 185) tool = 185;
                            if (tool <= 0) tool = 0;
                            R_black[j] = (uint8)tool;
                        }
                    }
                    else
                    {
                        for (j = 0; j < 70; j++)
                        {
                            R_black[j] = 0;
                        }
                    }
                }
            }

        }
        else if (times >= 5 && left_turn_down[0] <= 30 && right_turn_down[0] <= 30)
        {
            find_leftup_point((uint8)My_Max(left_turn_down[0], 13), 50, 0);
            find_rightup_point((uint8)My_Max(right_turn_down[0], 13), 50, 0);
            ////////////SetText("左上拐点       " + "右上拐点         ");
            ////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")          (" + right_turn_up[1] + "," + right_turn_up[0] + ")");
            ////////////SetText("   ");
            if (left_turn_up[0] != 0)
            {
                regression(1, left_turn_up[0], left_turn_up[0] + 5);
                for (uint8 j = 0; j < left_turn_up[0]; j++)
                {
                    int tool = L_black[j];
                    tool = (int)(k * j + b);
                    if (tool >= 185)
                    {
                        tool = 185;
                    }
                    L_black[j] = (uint8)tool;
                }
            } //从左上拐点拉线

            //左右并列关系
            if (right_turn_up[0] != 0)
            {
                regression(2, right_turn_up[0], right_turn_up[0] + 5);

                for (uint8 j = 0; j < right_turn_up[0]; j++)
                {
                    int tool = R_black[j];
                    tool = (int)(k * j + b);
                    if (tool <= 0)
                    {
                        tool = 0;
                    }
                    R_black[j] = (uint8)tool;
                }
            } //从右上拐点拉线
        }


        for (uint8 j = 0; j <= break_hangshu; j++)
        {
            LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);
        }
        breakhang_hold(2, 15, break_hangshu);
    }
}
void podao()
{
    if (flag_chuku == 0 && flag_ruku == 0 && flag_roundabout == 0 )
    {
        float l_k = regression(1, 2, 56);
        float r_k = regression(2, 2, 56);
        float mid_k = regression(0, 56, 66);
        uint8 judge = 0;
        rou_of_center = 0;
        Cal_estimator(0);
        find_rightup_point(3,30,0);
        find_leftup_point(3,30,0);

        if (left_turn_up[0]*right_turn_up[0] == 0 && podao_lock == 0 && width[40] > 110 && width[45] > 100 && width[50] > 83 && width[55] > 80 && width[50] - width[55] <= 15 && width[50] - width[55] >= 0 && width[45] - width [50] <= 15 && width[40] - width[45] <= 15 )
        {
            judge = 1;
        }
        else if (podao_lock > 0)
        {
            if (podao_lock++ > 20)
            {
                podao_lock = 0;
                podao_down = 0;
                flag_podao = flag_right_podao = flag_left_podao = 0;
            }
        }
        left_turn_up[0] = left_turn_up[1] = right_turn_up[0] = right_turn_up[1] = 0;
        if (flag_podao == 0 && judge >= 1 && l_k > -1.3 && l_k < 0.1 && r_k > -0.1 && r_k < 1.3 && break_hangshu > 40  && rou_of_center < 60 && mid_k < 1 && mid_k > -1)
        {
            flag_podao = 1;
            podao_up = 1;
            if (r_k + l_k > 0.6)
            {
                flag_right_podao = 1;
            }
            else if (r_k + l_k < -0.6)
            {
                flag_left_podao = 1;
            }
            else
            {
            }

        }
        else if (podao_up == 1)
        {

            if (width[1]<70&&(break_hangshu <= 40 || width[10] < 60))
            {
                flag_podao = 2;
                podao_up = 0;
                podao_top = 1;
            }
        }
        else if (podao_top == 1 && break_hangshu > 40)
        {
            flag_podao = 3;
            podao_top = 0;
            podao_down = 1;

        }
        else if (podao_down == 1 && width[10] > 170 )
        {
            podao_down = 0;
            reg_center = LCenter[5];
            flag_podao = flag_right_podao = flag_left_podao = 0;
        }

        if (podao_up == 1)
        {
        }
        else if (podao_top == 1)
        {
        }
        else if (podao_down == 1)
        {
            if (podao_lock == 0)
            {
                podao_lock = 1;
            }
        }
    }

}
void huandao()
{
    if (flag_ruku == 0 && flag_podao == 0 && flag_chuku == 0)
    {
        rou_of_left = rou_of_right = 0;
        Cal__estimator(1, 5, 50);
        Cal__estimator(2, 5, 50);
        //////////////SetText("环岛计算方差:");
        //////////////SetText("左线方差为:" + rou_of_left);
        //////////////SetText("右线方差为:" + rou_of_right);
        find_rightdown_point(6, (uint8)My_Min(33, (int)break_hangshu), 1);
        find_leftdown_point(6, (uint8)My_Min(33, (int)break_hangshu), 1);
        //////////////SetText("第一次扫线");
        //////////////SetText("左下拐点       " + "右下拐点         ");
        //////////////SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

        if (status_roundabout < 1 && flag_forkroad == 0 && right_turn_down[0] > 0 && right_turn_down[0] <= 40 && lostright_times >= 10 && (int)lostleft_times - (int)l_start < 5 && l_start < 10)
        {
            rou_of_left = rou_of_right = 0;
            Cal__estimator(1, 10, 55);
            Cal__estimator(2, 10, 55);
            //////////////SetText("右线方差为:" + rou_of_right);
            //////////////SetText("左线方差为:" + rou_of_left);
            if (rou_of_left < 10 && rou_of_right > 80)
            {
                //////////////SetText("********************找到右环岛*********************");
                flag_roundabout = 1;
                flag_left_roundabout = 0;
                flag_right_roundabout = 1;
                status_roundabout = 1;
                get_centerline();
                Cal_losttimes(break_hangshu);
            }

        }
        else if (status_roundabout < 1 && flag_forkroad == 0 && (int)lostleft_times - (int)l_start < 5 && lostright_times > 20)  //&& (int)lostright_times - (int)r_start >= 5
        {
            find_rightmiddle_point(16, 50);
            find_leftmiddle_point(16, 50);
            //////////////SetText("左中拐点       " + "右中拐点       ");
            //////////////SetText("(" + left_turn_middle[1] + "," + left_turn_middle[0] + ")          (" + right_turn_middle[1] + "," + right_turn_middle[0] + ")");

            if (right_turn_middle[0] > 0)
            {
                find_rightup_point((uint8)(right_turn_middle[0] + 1), 68, 1);
                if (right_turn_up[0] > 0)
                {
                    //////////////SetText("右上拐点       ");
                    //////////////SetText("(" + right_turn_up[1] + "," + right_turn_up[0] + ")");
                }
            }
            float k_top_r = 0;
            if (right_turn_up[0] > right_turn_middle[0])
            {
                k_top_r = regression(2, right_turn_up[0], right_turn_up[0] + 3);
                //////////////SetText("右上斜率" + k_top_r);
            }


            rou_of_left = rou_of_right = 0;
            Cal__estimator(1, 5, 50);
            Cal__estimator(2, 5, 50);
            //////////////SetText("环岛计算方差:");
            //////////////SetText("左线方差为:" + rou_of_left);
            //////////////SetText("右线方差为:" + rou_of_right);

            if (right_turn_middle[1] > 15 && right_turn_middle[0] > 16 && right_turn_middle[0] <= 62 && left_turn_middle[1] > 175 && rou_of_left < 20 && rou_of_right > 55 && k_top_r > -2) // && left_turn_middle[0] == 0
            {
                //////////////SetText("********************找到右环岛*********************");
                flag_roundabout = 1;
                flag_left_roundabout = 0;
                flag_right_roundabout = 1;
                status_roundabout = 1;
                get_centerline();
                Cal_losttimes(break_hangshu);
            }
        }


        if (status_roundabout < 1 && flag_forkroad == 0 && left_turn_down[0] > 0 && left_turn_down[0] <= 40 && (int)lostleft_times >= 10 && (int)lostright_times - (int)r_start < 5) //找的到下拐点
        {
            rou_of_left = rou_of_right = 0;
            Cal__estimator(1, 10, 55);
            Cal__estimator(2, 10, 55);
            //////////////SetText("右线方差为:" + rou_of_right);
            //////////////SetText("左线方差为:" + rou_of_left);
            if (rou_of_right < 10 && rou_of_left > 80)
            {
                //////////////SetText("********************找到左环岛*********************");
                flag_roundabout = 1;
                flag_left_roundabout = 1;
                flag_right_roundabout = 0;
                status_roundabout = 1;
                get_centerline();
                Cal_losttimes(break_hangshu);
            }

        }
        else if (status_roundabout < 1 && flag_forkroad == 0 && (int)lostright_times - (int)r_start < 5 && lostleft_times > 20) // && (int)lostright_times - (int)r_start < 5 //找不到下拐点
        {
            find_rightmiddle_point(16, 50);
            find_leftmiddle_point(16, 50);
            //////////////SetText("左中拐点       " + "右中拐点       ");
            //////////////SetText("(" + left_turn_middle[1] + "," + left_turn_middle[0] + ")          (" + right_turn_middle[1] + "," + right_turn_middle[0] + ")");

            if (left_turn_middle[0] > 0)
            {
                find_leftup_point((uint8)(left_turn_middle[0] + 1), 68, 1);
                if (left_turn_up[0] > 0)
                {
                    //////////////SetText("右上拐点       ");
                    //////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")");
                }
            }
            float k_top_l = 0;
            if (left_turn_up[0] > left_turn_middle[0])
            {
                k_top_l = regression(1, left_turn_up[0], left_turn_up[0] + 3);
                //////////////SetText("左上斜率" + k_top_l);
            }

            rou_of_left = rou_of_right = 0;
            Cal__estimator(1, 5, 50);
            Cal__estimator(2, 5, 50);
            //////////////SetText("环岛计算方差:");
            //////////////SetText("左线方差为:" + rou_of_left);
            //////////////SetText("右线方差为:" + rou_of_right);
            if (left_turn_middle[1] < 170 && left_turn_middle[0] > 16 && left_turn_middle[0] <= 62 && right_turn_middle[1] < 10 && rou_of_right < 20 && rou_of_left > 55   && k_top_l < 2) //&& right_turn_middle[0] == 0
            {
                //////////////SetText("********************找到左环岛*********************");
                flag_roundabout = 1;
                flag_left_roundabout = 1;
                flag_right_roundabout = 0;
                status_roundabout = 1;
                get_centerline();
                Cal_losttimes(break_hangshu);
            }

        }

        if (flag_right_roundabout == 1 || flag_left_roundabout == 1)
        {
            //////////////SetText("*********************环岛扫线OVO********************");
            find_rightdown_point(3, (uint8)My_Min(33, (int)break_hangshu), 1);
            find_leftdown_point(3, (uint8)My_Min(33, (int)break_hangshu), 1);
            //////////////SetText("左下拐点       " + "右下拐点         ");
            //////////////SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");
            Cal_losttimes(30);
            if (flag_find_huan_leftdown_point == 1 && status_roundabout != 2 && status_roundabout != 5)
            {
                //////////////SetText("从左下拐点向上扫线");
                find_leftmiddle_point((uint8)(left_turn_down[0] + 5), 60);
            }
            else
            {
                //////////////SetText("！！！！！左下拐点无效");
                //////////////SetText("从第18行开始向上找左中");
                find_leftmiddle_point(18, 60);
            }
            if (left_turn_middle[0] != 0 && status_roundabout != 4) flag_find_huan_leftmiddle_point = 1;

            if (flag_find_huan_rightdown_point == 1 && status_roundabout != 2 && status_roundabout != 5)
            {
                //////////////SetText("从右下拐点向上扫线");
                find_rightmiddle_point((uint8)(right_turn_down[0] + 5), 50);
            }
            else
            {
                //////////////SetText("！！！！！右下拐点无效");
                //////////////SetText("从第16行开始向上找右中");
                find_rightmiddle_point(16, 60);
            }
            if (right_turn_middle[0] != 0 && status_roundabout != 4) flag_find_huan_rightmiddle_point = 1;

            //////////////SetText("左中拐点       " + "右中拐点       ");
            //////////////SetText("(" + left_turn_middle[1] + "," + left_turn_middle[0] + ")          (" + right_turn_middle[1] + "," + right_turn_middle[0] + ")");

            if (flag_find_huan_rightmiddle_point == 1 && status_roundabout != 3 && status_roundabout != 4 && status_roundabout != 5 && status_roundabout != 6)  //右中拐点存在  && right_turn_middle[0] < 55
            {
                //////////////SetText("从右中开始往上找");
                find_rightup_point((uint8)(right_turn_middle[0] + 1), 68, 1);
            }
            else if (status_roundabout == 3 || status_roundabout == 6)
            {
                find_rightup_point(5, 68, 1);
            }
            else if (flag_find_huan_rightmiddle_point == 1 && status_roundabout == 7)
            {
                //////////////SetText("从第5行开始往上找右上拐点");
                find_rightup_point(5, 68, 1);
            }
            else
            {
                //////////////SetText("从第25行开始往上找右上拐点");
                find_rightup_point(25, 68, 1);
            }

            if (flag_find_huan_leftmiddle_point == 1 && status_roundabout != 3 && status_roundabout != 4 && status_roundabout != 5 && status_roundabout != 6)  //左中拐点存在   && left_turn_middle[0] < 55
            {
                //////////////SetText("从左中开始往上找");
                find_leftup_point((uint8)(left_turn_middle[0] + 1), 68, 1);
            }
            else if (status_roundabout == 3 || status_roundabout == 6)
            {
                find_leftup_point(5, 68, 1);
            }
            else if (flag_find_huan_leftmiddle_point == 1 && status_roundabout == 7)
            {
                //////////////SetText("从第5行开始往上找左上拐点");
                find_leftup_point(5, 68, 1);
            }
            else
            {
                //////////////SetText("从第25行开始往上找左上拐点");
                find_leftup_point(25, 68, 1);
            }

            //////////////SetText("左上拐点       " + "右上拐点       ");
            //////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")          (" + right_turn_up[1] + "," + right_turn_up[0] + ")");
            //////////////SetText("************************************环岛初步扫线结束***************************");

            if (status_roundabout == 1)
            {

                if (flag_right_roundabout == 1) //右
                {
                    if (lostright_times < 35 && r_start >= right_turn_down[0] && right_turn_middle[0] < 45) //    || (int)right_turn_middle[0] > 15 && (int)right_turn_middle[0] < 40
                    {
                        status_roundabout = 2;
                    }
                }
                else if (flag_left_roundabout == 1) //左
                {

                    if (lostleft_times < 35 && l_start >= left_turn_down[0] && left_turn_middle[0] < 45)  // || (int)left_turn_middle[0] > 15 && (int)left_turn_middle[0] < 40
                    {
                        status_roundabout = 2;
                    }
                }
            }
            else if (status_roundabout == 2)
            {
                Cal_losttimes(60);
                if (flag_right_roundabout == 1) //右
                {
                    //////////////SetText("环岛状态2找上拐点");
                    uint8 i;
                    uint8 right_breakpoint = 0;

                    for (i = (uint8)(right_turn_down[0] + 1); i < break_hangshu; i++)
                    {
                        if (R_black[i] - R_black[i - 1] >= 20)
                        {
                            right_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + right_breakpoint);
                    //////////////SetText("真正的右上拐点       ");
                    //////////////SetText("(" + R_black[right_breakpoint] + "," + right_breakpoint + ")");
                    if (width[30] > 115 && lostright_times > 20 && right_breakpoint > 0 && right_breakpoint < 50)
                    {
                        status_roundabout = 3;
                    }

                }
                else if (flag_left_roundabout == 1)
                {
                    //////////////SetText("环岛状态2找上拐点");
                    uint8 i;
                    uint8 left_breakpoint = 0;

                    for (i = (uint8)(left_turn_down[0] + 1); i < break_hangshu; i++)
                    {
                        if (L_black[i] - L_black[i - 1] <= -20 )
                        {
                            left_breakpoint = i;
                            break;
                        }
                        else if (L_black[i] - L_black[i - 1] <= -10 && left_turn_middle[0] > 50)
                        {
                            left_breakpoint = left_turn_middle[0];
                            break;
                        }
                    }
                    //////////////SetText("断点为" + left_breakpoint);
                    //////////////SetText("真正的左上拐点       ");
                    //////////////SetText("(" + L_black[left_breakpoint] + "," + left_breakpoint + ")");
                    if (width[20] > 115 && lostleft_times > 20 && left_breakpoint > 0 && (left_breakpoint < 50 || left_breakpoint == left_turn_middle[0]))
                    {
                        status_roundabout = 3;
                    }
                }
            }
            else if (status_roundabout == 3)
            {

                rou_of_left = rou_of_right = 0;
                Cal__estimator(1, 5, 55);
                Cal__estimator(2, 5, 55);
                //////////////SetText("环岛内方差:");
                //////////////SetText("左线方差为:" + rou_of_left);
                //////////////SetText("右线方差为:" + rou_of_right);
                if (flag_right_roundabout == 1)
                {
                    if (width[10] > 150 && right_turn_up[0] <= 28)
                    {
                        status_roundabout = 4;
                    }
                }
                else if (flag_left_roundabout == 1)
                {
                    if (width[10] > 150 && left_turn_up[0] <= 28)
                    {
                        status_roundabout = 4;
                    }
                }
            }
            else if (status_roundabout == 4)
            {
                if (flag_right_roundabout == 1)
                {
                    uint8 i;
                    uint8 right_breakpoint = 0;

                    for (i = 1; i < 67; i++)
                    {
                        if (R_black[i] - R_black[i - 1] >= 20)
                        {
                            right_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + right_breakpoint);
                    //////////////SetText("真正的右上拐点       ");
                    //////////////SetText("(" + R_black[right_breakpoint] + "," + right_breakpoint + ")");

                    if (l_start <= 4 && width[1] < 165) //&& right_breakpoint < 20
                    {
                        status_roundabout = 5;
                    }

                }
                else if (flag_left_roundabout == 1)
                {
                    uint8 i;
                    uint8 left_breakpoint = 0;

                    for (i = 1; i < 67; i++)
                    {
                        if (L_black[i] - L_black[i - 1] <= -20)
                        {
                            left_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + left_breakpoint);
                    //////////////SetText("真正的左上拐点       ");
                    //////////////SetText("(" + L_black[left_breakpoint] + "," + left_breakpoint + ")");
                    if (r_start <= 4 && width[1] < 165)  //&& left_breakpoint < 20
                    {
                        status_roundabout = 5;
                    }
                }
            }
            else if (status_roundabout == 5)
            {
                if (flag_right_roundabout == 1)
                {


                    if (left_turn_down[0] >= 5 && left_turn_down[0] <= break_hangshu && left_turn_down[0] < 40)
                    {
                        old_flag = 0;
                        status_roundabout = 6;
                    }
                }
                else if (flag_left_roundabout == 1)
                {

                    if (right_turn_down[0] >= 5 && right_turn_down[0] <= break_hangshu && right_turn_down[0] < 40)
                    {
                        old_flag = 0;
                        status_roundabout = 6;
                    }
                }
            }
            else if (status_roundabout == 6)
            {
                if (flag_right_roundabout == 1)
                {
                    find_rightup_point(16, 68, 1);
                    //////////////SetText("Width[5]" + width[5]);
                    //////////////SetText("Witdth[10]" + width[10]);
                    //////////////SetText("l_start" + l_start);
                    //////////////SetText("右上拐点       ");
                    //////////////SetText("(" + right_turn_up[1] + "," + right_turn_up[0] + ")");


                    if (left_turn_down[0] == 0 && rou_of_left < 30 && right_turn_up[1] > 2 || left_turn_down[0] == 0 && rou_of_left < 30 && l_start == 0 && rou_of_right < 10)
                    {
                        status_roundabout = 7;
                    }
                }
                else if (flag_left_roundabout == 1)
                {
                    find_leftup_point(16, 68, 1);
                    //////////////SetText("Width[5]" + width[5]);
                    //////////////SetText("Witdth[10]" + width[10]);
                    //////////////SetText("r_start" + r_start);
                    //////////////SetText("左上拐点       ");
                    //////////////SetText("(" + left_turn_up[1] + "," + left_turn_up[0] + ")");

                    if (right_turn_down[0] == 0 && rou_of_right < 30 && left_turn_up[1] < 183)
                    {
                        status_roundabout = 7;
                    }
                }
            }
            else if (status_roundabout == 7)
            {
                if (flag_right_roundabout == 1)
                {
                    if (rou_of_left < 550 && rou_of_right < 550 && (r_start < 20 || right_turn_up[0] == 0 && r_start < 30))
                    {
                        status_roundabout = 8;
                    }
                }
                else if (flag_left_roundabout == 1)
                {
                    if (rou_of_right < 550 && rou_of_left < 550 && (l_start < 20 || left_turn_up[0] == 0 && l_start < 30))
                    {
                        status_roundabout = 8;
                    }
                }
            }
            //////////////SetText("************************************当前状态----" + status_roundabout + "*********************");


            if (flag_right_roundabout == 1)
            {
                uint8 j;
                if (status_roundabout == 1) //右下到右中拉线
                {
                    reg_right_up_y = reg_right_up_x = 0;
                    if (right_turn_down[0] > 5 && right_turn_middle[0] - 2 > right_turn_down[0])
                    {

                        advanced_regression(2, right_turn_down[0] - 2, right_turn_down[0], right_turn_middle[0] - 2, right_turn_middle[0]);
                        for (j = (uint8)right_turn_down[0]; j <= (uint8)right_turn_middle[0]; j++)
                        {
                            int jicun = (int)(k * j + b);
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                            //LCenter[j] = (uint8)((R_black[j] + L_black[j]) / 2);
                        }
                        k_before_R_roundabout = k;
                        b_before_R_roundabout = b;
                    }
                    else
                    {
                        int delta = right_turn_middle[0] - 0;
                        if (delta == 0) delta = 1;
                        float k = (right_turn_middle[1] - R_black[0]) * 1.0f / delta;
                        float b = R_black[0];
                        for (j = (uint8)0; j <= (uint8)right_turn_middle[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }
                }
                else if (status_roundabout == 2)  //右中到右下角拉线
                {

                    int delta = right_turn_middle[0] - 0;
                    if (delta == 0) delta = 1;
                    float k = (right_turn_middle[1] - R_black[0]) * 1.0f / delta;
                    float b = R_black[0];
                    for (j = (uint8)0; j <= (uint8)right_turn_middle[0]; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        R_black[j] = (uint8)jicun;
                    }
                }
                else if (status_roundabout == 3)
                {
                    uint8 i;
                    uint8 right_breakpoint = 0;

                    for (i = 1; i < 67; i++)
                    {
                        if (R_black[i] - R_black[i - 1] >= 20)
                        {
                            right_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + right_breakpoint);
                    //////////////SetText("真正的右上拐点       ");
                    //////////////SetText("(" + R_black[right_breakpoint] + "," + right_breakpoint + ")");
                    //if(right_turn_up[0] >10 &&)
                    int delta = right_breakpoint - 3;
                    if (delta <= 0) delta = 1;
                    k = (R_black[right_breakpoint] - L_black[3]) * 1.0f / (delta * 1.0f);
                    b = L_black[3] - 3 * k;
                    for (j = (uint8)3; j <= (uint8)right_breakpoint; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        L_black[j] = (uint8)jicun;
                    }
                    last_k = k;
                    last_b = b;
                    break_hangshu = right_breakpoint;
                    reg_right_up_y = right_breakpoint;
                    reg_right_up_x = R_black[right_breakpoint];
                }
                else if (status_roundabout == 4)
                {
                    uint8 i;
                    uint8 right_breakpoint = 0;

                    for (i = 1; i < 67; i++)
                    {
                        if (R_black[i] - R_black[i - 1] >= 20)
                        {
                            right_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + right_breakpoint);
                    //////////////SetText("真正的右上拐点       ");
                    //////////////SetText("(" + R_black[right_breakpoint] + "," + right_breakpoint + ")");
                    k = (R_black[right_breakpoint] - 184) / (right_breakpoint - 1);
                    b = R_black[right_breakpoint] - right_breakpoint * k;
                    for (j = 1; j <= right_breakpoint; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        L_black[j] = (uint8)jicun;
                        R_black[j] = 0;
                    }
                    for (uint8 s = 0; s <= right_breakpoint; s++)
                    {
                        LCenter[s] = (uint8)((L_black[s] + R_black[s]) / 2);
                    }
                    breakhang_hold(2, 15, right_breakpoint);
                    //////////////SetText(" reg_right_up_y :" + reg_right_up_y);
                }
                else if (status_roundabout == 5)
                {
                    reg_right_up_y = reg_right_up_x = 0; //清除状态3、4用的拉线

                    if (old_flag == 0)
                    {
                        old = 40;
                        old_flag = 1;
                    }
                    else
                    { }

                    for (j = 0; j < 69; j++)
                    {
                        uint8 i;
                        for (i = old; i >= 0 && i < 184; i++)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                L_black[j] = i;
                                break;
                            }
                            L_black[j] = 184;
                        }
                        for (i = old; i <= 185 && i > 1; i--)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                R_black[j] = i;
                                break;
                            }
                            R_black[j] = 0;
                        }
                        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);

                        if ((Trans_Pixels(j,LCenter[j]) == 0) && Trans_Pixels(j+1,LCenter[j])==0)
                        {
                            break_hangshu = j;
                            if (break_hangshu >= 15)    //防止在一开始就break
                            {
                                break;
                            }
                        }
                        else break_hangshu = 69;
                        old = LCenter[j];
                        //环岛内正常扫线
                    }
                    //////////////SetText("Break" + break_hangshu);
                    old = LCenter[3];
                }
                else if (status_roundabout == 6)
                {
                    //////////////SetText("********************Status_6专属扫线**************************");


                    find_rightdown_point(2, (uint8)My_Min(47, (int)break_hangshu), 1);
                    find_leftdown_point(2, (uint8)My_Min(47, (int)break_hangshu), 1);
                    //////////////SetText("Status_6再找一次左下拐点");
                    //////////////SetText("左下拐点       " + "右下拐点         ");
                    //////////////SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                    uint8 i;
                    uint8 flag_of_rightbreak = 0;
                    for (i = 0; i < 70; i++)
                    {
                        //右线操作
                        if (rightfindflag[i] == 0)       //未扫到线
                        {
                            if (flag_of_rightbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
                            {
                                r_start_sec++;
                            }
                        }
                        else    //扫到线
                        {
                            //lostright_times不继续增加
                            flag_of_rightbreak = 1;  //break标志成立
                        }
                    }

                    //////////////SetText("R_start_sec: " + r_start_sec);
                    if (left_turn_down[0] > 5)
                    {
                        int delta = r_start_sec - (left_turn_down[0] - 5);
                        if (delta <= 0) delta = 1;
                        k = (0 - left_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = left_turn_down[1] - (left_turn_down[0] - 5) * k;

                        for (j = (uint8)(left_turn_down[0] - 5); j < (uint8)r_start_sec; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }
                    else
                    {
                        int delta = r_start_sec - left_turn_down[0];
                        if (delta <= 0) delta = 1;
                        k = (10 - left_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = left_turn_down[1] - left_turn_down[0] * k;

                        for (j = (uint8)left_turn_down[0]; j <= (uint8)r_start_sec; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }

                }
                else if (status_roundabout == 7)
                {
                    if (right_turn_down[0] > 0 && right_turn_up[0] > 0)
                    {
                        int delta = right_turn_up[0] - right_turn_down[0];
                        if (delta <= 0) delta = 1;
                        k = (right_turn_up[1] - right_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = right_turn_down[1] - right_turn_down[0] * k;

                        for (j = (uint8)0; j <= (uint8)right_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }
                    else if (right_turn_up[0] > 0 && right_turn_up[0] < 50)
                    {
                        regression(2, right_turn_up[0], right_turn_up[0] + 5);
                        for (j = (uint8)0; j <= (uint8)right_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }
                    else if (right_turn_middle[0] > 0)
                    {
                        for (j = (uint8)0; j <= (uint8)right_turn_middle[0]; j++)
                        {
                            R_black[j] = (uint8)R_End[j];
                        }
                    }
                    else
                    {
                        regression(2, 27, 32);
                        for (j = (uint8)5; j <= (uint8)right_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }

                }
                else if (status_roundabout == 8)
                {
                    flag_roundabout = status_roundabout = flag_right_roundabout = flag_left_roundabout = reg_right_up_y = reg_right_up_x = 0;
                }
                //////////////SetText("************************************右环岛处理完毕********************");
            }

            else if (flag_left_roundabout == 1)
            {
                uint8 j;

                if (status_roundabout == 1)
                {
                    reg_left_up_y = reg_left_up_x = 0;
                    if (left_turn_down[0] > 5 && left_turn_middle[0] - 2 > left_turn_down[0])
                    {

                        advanced_regression(1, left_turn_down[0] - 2, left_turn_down[0], left_turn_middle[0] - 2, left_turn_middle[0]);
                        for (j = (uint8)left_turn_down[0]; j <= (uint8)left_turn_middle[0]; j++)
                        {
                            int jicun = (int)(k * j + b);
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                            //LCenter[j] = (uint8)((R_black[j] + L_black[j]) / 2);
                        }
                        k_before_L_roundabout = k;
                        b_before_R_roundabout = b;
                    }
                    else
                    {
                        int delta = left_turn_middle[0] - 0;
                        if (delta == 0) delta = 1;
                        float k = (left_turn_middle[1] - L_black[0]) * 1.0f / delta;
                        float b = L_black[0];
                        for (j = (uint8)0; j <= (uint8)left_turn_middle[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }
                }
                else if (status_roundabout == 2)
                {

                    int delta = left_turn_middle[0] - 0;
                    if (delta == 0) delta = 1;
                    float k = (left_turn_middle[1] - L_black[0]) * 1.0f / delta;
                    float b = L_black[0];
                    for (j = (uint8)0; j <= (uint8)left_turn_middle[0]; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        L_black[j] = (uint8)jicun;
                    }
                }
                else if (status_roundabout == 3)
                {
                    uint8 i;
                    uint8 left_breakpoint = 0;
                    for (i = 1; i < 67; i++)
                    {
                        if (L_black[i] - L_black[i - 1] <= -20)
                        {
                            left_breakpoint = i;
                            break;
                        }
                    }
                    //////////////SetText("断点为" + left_breakpoint);
                    //////////////SetText("真正的左上拐点       ");
                    //////////////SetText("(" + L_black[left_breakpoint] + "," + left_breakpoint + ")");
                    //if(right_turn_up[0] >10 &&)
                    int delta = left_breakpoint - 3;
                    if (delta <= 0) delta = 1;
                    k = (L_black[left_breakpoint] - R_black[3]) * 1.0f / (delta * 1.0f);
                    b = R_black[3] - 3 * k;
                    for (j = (uint8)3; j <= (uint8)left_turn_up[0]; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        R_black[j] = (uint8)jicun;
                    }
                    last_k = k;
                    last_b = b;
                    reg_left_up_y = left_breakpoint;
                    reg_left_up_x = L_black[left_breakpoint];
                }
                else if (status_roundabout == 4)
                {
                    uint8 i;
                    uint8 left_breakpoint = 0;

                    for (i = 1; i < 67; i++)
                    {
                        if (L_black[i - 1] - L_black[i] >= 20)
                        {
                            left_breakpoint = i;
                            break;
                        }
                    }

                    //////////////SetText("断点为" + left_breakpoint);
                    //////////////SetText("真正的左上拐点       ");
                    //////////////SetText("(" + L_black[left_breakpoint] + "," + left_breakpoint + ")");
                    k = (L_black[left_breakpoint] - 0) / (left_breakpoint - 1);
                    b = L_black[left_breakpoint] - left_breakpoint * k;
                    for (j = 1; j <= left_breakpoint; j++)
                    {
                        int jicun = ((int)(k * j + b));
                        if (jicun >= 185) jicun = 185;
                        else if (jicun <= 0) jicun = 0;
                        L_black[j] = 185;
                        R_black[j] = (uint8)jicun;
                    }
                    for (uint8 s = 0; s <= left_breakpoint; s++)
                    {
                        LCenter[s] = (uint8)((L_black[s] + R_black[s]) / 2);
                    }
                    breakhang_hold(2, 15, left_breakpoint);
                    //////////////SetText(" reg_left_up_y :" + reg_left_up_y);
                }
                else if (status_roundabout == 5)
                {
                    reg_left_up_y = reg_left_up_x = 0; //清除状态3、4用的拉线
                                                       //环岛内正常扫线
                    if (old_flag == 0)
                    {
                        old = 145;
                        old_flag = 1;
                    }
                    else
                    { }
                    for (j = 0; j < 69; j++)
                    {
                        uint8 i;
                        for (i = old; i >= 0 && i < 184; i++)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                L_black[j] = i;
                                break;
                            }
                            L_black[j] = 184;
                        }
                        for (i = old; i <= 185 && i > 1; i--)
                        {
                            if (Trans_Pixels(j,i) == 0)
                            {
                                R_black[j] = i;
                                break;
                            }
                            R_black[j] = 0;
                        }
                        LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);

                        if (((Trans_Pixels(j,LCenter[j])) == 0) && (Trans_Pixels(j+1,LCenter[j]) == 0))
                        {
                            break_hangshu = j;
                            if (break_hangshu >= 15)    //防止在一开始就break
                            {
                                break;
                            }

                        }
                        else
                        {
                            break_hangshu = 69;
                        }

                        old = LCenter[j];
                        //环岛内正常扫线
                    }
                    //////////////SetText("Break" + break_hangshu);
                    old = LCenter[3];

                }
                else if (status_roundabout == 6)
                {
                    //////////////SetText("********************Status_6专属扫线**************************");

                    find_rightdown_point(2, (uint8)My_Min(47, break_hangshu), 1);
                    find_leftdown_point(2, (uint8)My_Min(47, break_hangshu), 1);
                    //////////////SetText("Status_6再找一次右下拐点");
                    //////////////SetText("左下拐点       " + "右下拐点         ");
                    //////////////SetText("(" + left_turn_down[1] + "," + left_turn_down[0] + ")          (" + right_turn_down[1] + "," + right_turn_down[0] + ")");

                    uint8 i;
                    uint8 flag_of_leftbreak = 0;
                    for (i = 0; i < 70; i++)
                    {
                        //右线操作
                        if (leftfindflag[i] == 0)       //未扫到线
                        {
                            if (flag_of_leftbreak == 0)     //如果在这一行之前没有遭遇断线，则计数
                            {
                                l_start_sec++;
                            }
                        }
                        else    //扫到线
                        {
                            //lostright_times不继续增加
                            flag_of_leftbreak = 1;  //break标志成立
                        }
                    }

                    //////////////SetText("L_start_sec: " + l_start_sec);

                    if (right_turn_down[0] > 5)
                    {
                        int delta = l_start_sec - (right_turn_down[0] - 5);
                        if (delta <= 0) delta = 1;
                        k = (175 - right_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = right_turn_down[1] - (right_turn_down[0] - 5) * k;

                        for (j = (uint8)(right_turn_down[0] - 5); j < (uint8)l_start_sec; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }
                    else
                    {
                        int delta = l_start_sec - right_turn_down[0];
                        if (delta <= 0) delta = 1;
                        k = (175 - right_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = right_turn_down[1] - right_turn_down[0] * k;

                        for (j = (uint8)right_turn_down[0]; j <= (uint8)l_start_sec; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            R_black[j] = (uint8)jicun;
                        }
                    }

                }
                else if (status_roundabout == 7)
                {
                    if (left_turn_down[0] > 0 && left_turn_up[0] > 0)
                    {
                        int delta = left_turn_up[0] - left_turn_down[0];
                        if (delta <= 0) delta = 1;
                        k = (left_turn_up[1] - left_turn_down[1]) * 1.0f / (delta * 1.0f);
                        b = left_turn_down[1] - left_turn_down[0] * k;

                        for (j = (uint8)0; j <= (uint8)left_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }
                    else if (left_turn_up[0] > 0 && left_turn_up[0] < 50)
                    {
                        regression(1, left_turn_up[0], left_turn_up[0] + 5);
                        for (j = (uint8)0; j <= (uint8)left_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }
                    else if (left_turn_middle[0] > 0)
                    {
                        for (j = (uint8)5; j <= (uint8)left_turn_middle[0]; j++)
                        {
                            L_black[j] = (uint8)L_End[j];
                        }
                    }
                    else
                    {
                        regression(1, 27, 32);
                        for (j = (uint8)0; j <= (uint8)left_turn_up[0]; j++)
                        {
                            int jicun = ((int)(k * j + b));
                            if (jicun >= 185) jicun = 185;
                            else if (jicun <= 0) jicun = 0;
                            L_black[j] = (uint8)jicun;
                        }
                    }

                }
                else if (status_roundabout == 8)
                {
                    flag_roundabout = status_roundabout = flag_right_roundabout = flag_left_roundabout = reg_left_up_y = reg_left_up_x = 0;
                }
                //////////////SetText("************************************左环岛处理完毕********************");
            }

        }
        //uint8 reg = LCenter[break_hangshu];


        if (status_roundabout != 4 && status_roundabout != 5)
        {
            for (uint8 j = 0; j <= break_hangshu; j++)
            {
                LCenter[j] = (uint8)((L_black[j] + R_black[j]) / 2);
            }
            breakhang_hold(2, 15, break_hangshu);
        }
        else if (status_roundabout == 5)
        {

        }
        else
        {

        }
        //for (uint8 s = break_hangshu; s < 70; s++)
        //{
        //    LCenter[s] = reg;
        //}
    }


}
void symbol_judge()
{
        f_turn_left = f_turn_right = f_straight = 0;
        error = (92 - LCenter[line]);

        L_Cur = regression(1, line-15, My_Min(line+10,break_hangshu) );
        R_Cur = regression(2, line-15, My_Min(line+10, break_hangshu) );

        if (podao_up == 1)
        {
            error = (92 - LCenter[2]);
            // if(flag_left_podao)
            // {
            //     reg_center = LCenter[2] - 10;
            // }
            // else if(flag_right_podao)
            // {
            //     reg_center = LCenter[2] + 10;
            // }
            // else
            // {
            //     reg_center = LCenter[2];
            // }
            kp = kp_straight;
            kd = kd_straight;
        }
        else if (podao_top == 1)
        {
            error = (92 - LCenter[0]);
            kp = kp_straight;
            kd = kd_straight;
        }
        else if (podao_down == 1)
        {
            error = 92 - LCenter[0];
            kp = kp_straight;
            kd = kd_straight;
        }
        else if(podao_lock != 0 ) //不确定是否来得及拐弯
        {
            kp = kp_turn;
            kd = kd_turn;
        }
        else if (status_roundabout >= 3 && status_roundabout <= 6)
        {
            if (flag_right_roundabout == 1)
            {
                f_turn_right = 1;
                kp = kp_roundabout;
                kd = kd_roundabout;
            }
            else if (flag_left_roundabout == 1)
            {
                f_turn_left = 1;
                kp = kp_roundabout;
                kd = kd_roundabout;
            }
        }
        else if (LCenter[line] - 92 <= -15 && L_Cur <= 0 && (R_Cur <= 0 || R_Cur - L_Cur > 3) )
        {
            f_turn_right = 1;

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
            else
            {
                kp = kp_turn;
                kd = kd_turn;
            }

        }
        else if (LCenter[line] - 92 >= 15 && (L_Cur >= 0 || R_Cur - L_Cur > 3) && R_Cur >= 0 )
        {
            f_turn_left = 1;
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
            else
            {
                kp = kp_turn;
                kd = kd_turn;
            }

        }
        else
        {
            f_straight = 1;
            kp = kp_straight;
            kd = kd_straight;
        }

        steer_out = (uint16)(middle - kp*error - kd*(error - last_error));
        if(steer_out >= middle + 80)
            steer_out = middle + 80;
        else if(steer_out <= middle - 80)
            steer_out = middle -80;
        last_error =error;


        My_SdCard_Save();
}


