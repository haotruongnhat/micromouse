#include "include.h"
void setupGyro() {
  Wire.begin();
    qmc.init();
  qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_8G,OSR_512);
}


void readGyro() {
  double dir;
  int x,y,z;
  qmc.read(&x,&y,&z);

  if(y>0) 
    dir= 90 - (atan(double(x)/double(y)) * 180 / PI);
  else if(y<0)
    dir = 270 - (atan(double(x)/double(y)) * 180 / PI);
  else if(y==0)
    if(x<0)
     dir = 180.0;
    else
      dir =0.0;
  else;
  
  gyroDirection = simpleKalmanFilter.updateEstimate(dir);

  
}

