#ifndef _control_h
#define _control_h


extern float kp_straight,kd_straight;
extern float kp_turn,kd_turn;
extern float kp_roundabout,kd_roundabout;
extern float kp_speed,ki_speed;
extern int f_longstraight;
extern float chasu;

void Incremental_pwm();
void pwm_out();
void turn_control();
void duty_control(int x);
void line_control_new();
void line_control_new2();

#endif
