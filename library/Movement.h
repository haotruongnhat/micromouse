#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "include.h"

#define KP  0.3
#define KI  0
#define KD  5

int errorP, errorD, oldErrorP;
int forward_left_pwm;
int targetLeft = 50;
int forward_right_pwm;
int targetRight = 50;
int turning = 0;
float totalError;
#endif

