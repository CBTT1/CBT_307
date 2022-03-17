#ifndef _IMAGE_DEAL_H
#define _IMAGE_DEAL_H

#define CROSSROAD    0;
#define ROUNDISLAND  1;

void init_saoxian();
void get_centerline();
void get_centerline_sec();
void print_centerline();
void Cal_losttimes(int times);
double my_sqrt(double t);
float my_min(float a, float b);
int My_Min(int x, int y);
int My_Max(int x, int y);
int My_Abs(int x);

float process_curvity(uint8 x1, uint8 y1, uint8 x2, uint8 y2, uint8 x3, uint8 y3);
float regression(int type, int startline, int endline);
void advanced_regression(int type, int startline1, int endline1, int startline2, int endline2);
void Cal_Line(float k, float b, uint8 start_point, uint8 end_point, uint8 ArryName);
int Cal_estimator(uint8 type);
void Cal__estimator(uint8 type, uint8 startline, uint8 endline);
void Drew_Line(float k, float b, int StartLine, int EndLine, int type);

void find_rightdown_point(uint8 start_point, uint8 end_point, uint8 RoadName);
void find_leftdown_point(uint8 start_point, uint8 end_point, uint8 RoadName);
void find_rightmiddle_point(uint8 start_point, uint8 end_point);
void find_leftmiddle_point(uint8 start_point, uint8 end_point);
void find_rightup_point(uint8 start_point, uint8 end_point, uint8 RoadName);
void find_leftup_point(uint8 start_point, uint8 end_point, uint8 RoadName);
int juge_if_same_fuhao(float a, float b);
void fork(int16 dir);
void check_starting_line_l();
void ruku_l();
void check_starting_line_r();
void ruku_r();
void ruku(uint8 s);
void chuku(uint8 s);
void crossroad();
void huandao();
void podao();
void symbol_judge();
void breakhang_hold(uint8 startline, uint8 endline, uint8 j);

void juge_lineContinuity(uint8 start_point, uint8 end_point,int positive_T,int negatie_T,uint8 ArryName);


#endif
