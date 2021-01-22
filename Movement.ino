void moveInstruction(int globalHeading,int nextHeading) {
  

  
}


void PID() {
      if(IR_value_L > L_wall && IR_value_R > R_wall){
        errorP = IR_value_R - IR_value_L - (R_middle_wall - L_middle_wall);
        errorD = errorP - oldErrorP;
      }
      else if(IR_value_L > L_wall && IR_value_R < R_wall){
        errorP = (L_middle_wall - IR_value_L);
        errorD = errorP - oldErrorP;
      }        
      else if(IR_value_L < L_wall && IR_value_R > R_wall){
        errorP = (IR_value_R - R_middle_wall);
        errorD = errorP - oldErrorP;
      }
      else if(IR_value_L < L_wall && IR_value_R < R_wall){
        errorP = 0;
        errorD = 0;
      }
      forward_left_pwm = targetLeft;
      forward_right_pwm = targetRight;
      if (turning == 0) {
        totalError = KP * errorP + KD * errorD;
        oldErrorP = errorP;
        forward_left_pwm = targetLeft - totalError;
        forward_right_pwm = targetRight + totalError;
      }
      Motor_L(forward_left_pwm);
      Motor_R(forward_right_pwm);
}
void stop(int time){
  turning = 1;
  targetLeft = 0;
  targetRight = 0;
  delay(time);
  while(1);
}
void goForward(int time, int left_pwm_speed,int right_pwm_speed) {
  Motor_L(forward_left_pwm);
  Motor_R(forward_right_pwm);
  delay(time);
}
void goForwardandStop(int time, int left_pwm_speed,int right_pwm_speed) 
{
  targetLeft = left_pwm_speed;
  targetRight = right_pwm_speed;
  //Motor_L(forward_left_pwm);
  //Motor_R(forward_right_pwm);
  delay(time);
}

void forwardDistance(int distance, int left_speed, int right_speed, bool coast) {
  int curEnc = left_enc;
  while (left_enc - curEnc < distance) {
    targetLeft = left_speed;
    targetRight = right_speed;
  }
  if (!coast) {
    targetLeft = 0;
    targetRight = 0;
  }
}
void turnRight(int time, int left_pwm_speed,int right_pwm_speed) {
  turning = 1;
  Motor_L(left_pwm_speed);
  Motor_R(-right_pwm_speed);
  delay(time);
//  turning = 0;  
}
void turnLeft(int time, int left_pwm_speed,int right_pwm_speed) {
  turning = 1;
  Motor_L(-left_pwm_speed);
  Motor_R(right_pwm_speed);
  delay(time);
//  turning = 0;
}

//void turnDegrees(int degrees, int direction) {
//  int curAng;
//  curAng = angle;
//  if(direction == 1)
//  {
//    while (angle-curAng < degrees) { 
//      targetLeft = -50*direction;
//      targetRight = 50*direction;
//    }
//  }
//  else if(direction == -1)
//  {
//      while (angle-curAng > degrees) { 
//      targetLeft = -50*direction;
//      targetRight = 50*direction;
//    }
//  }
//  targetLeft = 0;
//  targetRight = 0;
//}
void turn90Left(int left_pwm_speed,int right_pwm_speed){
  resetRightEncCount();
  resetLeftEncCount();
  left_enc = 0;
  right_enc = 0;
  turning = 1;
  while(left_enc > -500 || right_enc < 500){
    turnLeft(0,60,60);
  }
  turning = 0;
  targetLeft = 0;
  targetRight = 0;
}

void turn90Right(int left_pwm_speed,int right_pwm_speed) {
  resetRightEncCount();
  resetLeftEncCount();
  left_enc = 0;
  right_enc = 0;
  turning = 1;
  while(left_enc< 500 || right_enc> -500){
    turnRight(0,left_pwm_speed,right_pwm_speed);
  }
  turning = 0;  
  targetLeft = 0;
  targetRight = 0;
}

void turnRightAngleRight(int leftSpeed, int rightSpeed) {
  int curRenc = right_enc;
  int curLenc = left_enc;
  turning = 1;
  while (left_enc - curLenc < 1150 || curRenc - right_enc < 1150){
    targetLeft = leftSpeed;
    targetRight = -rightSpeed;
  }
  turning = 0;
  targetLeft = 0;
  targetRight = 0;
}
void turnRightAngleLeft(int leftSpeed, int rightSpeed) {
  int curRenc = right_enc;
  int curLenc = left_enc;
  turning = 1;
  while (right_enc - curRenc < 1150 || curLenc - left_enc < 1150) {
    targetLeft = -leftSpeed;
    targetRight = rightSpeed;
  }
  turning = 0;
  targetLeft = 0;
  targetRight = 0;
}

