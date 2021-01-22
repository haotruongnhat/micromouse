#ifndef _GYRO_H
#define _GYRO_H


#include "MechaQMC5883.h"
#include "SimpleKalmanFilter.h"

MechaQMC5883 qmc;

SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.12);

double gyroDirection;
void readGyro();
void setupGyro();
#endif
