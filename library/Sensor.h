#ifndef _SENSOR_H
#define _SENSOR_H

#include <math.h>

#define IRENABLE_F            5
#define IRENABLE_LR           6
#define IR_FL                 A0
#define IR_FR                 A1
#define IR_L                  A2
#define IR_R                  A3

int IR_value_FL, IR_value_FR, IR_value_L, IR_value_R;
int L_wall = 70;
int R_wall = 70;
int FL_wall;
int FR_wall;
int L_middle_wall = 200;
int R_middle_wall = 200;
int FL_middle_wall = 200;
int FR_middle_wall = 200; 
int IR_value_FL_offset=0;
int IR_value_FR_offset=0;
int IR_value_L_offset=0; 
int IR_value_R_offset=0;


extern void Sensor_pin_config(void);
extern void readSensor(void);
extern void Run_front(int);
extern void Run_front_random(int);
extern void Set_pulse(int,int);
#endif
