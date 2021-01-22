#ifndef _MOTORCONTROL_H
#define _MOTORCONTROL_H

#define PWM_1                 3
#define PWM_2                 9
#define PWM_3                 10
#define PWM_4                 11


extern void Motor_config();
extern void Motor_L(int);
extern void Motor_R(int);

#endif
