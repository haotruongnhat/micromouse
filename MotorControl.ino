

void Motor_config() {
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(PWM_4, OUTPUT);
}
void Motor_L(int duty) {
  int mode;
  if(duty > 255) duty = 255;
  else if(duty < -255) duty = -255;
  if (duty == 0)
    mode = 0;
  else if (duty > 0)
    mode = 1;
  else   
    mode = 2;
  switch (mode) {
    case 0: SoftPWMSet(PWM_1, 0);  SoftPWMSet(PWM_2, 0);  break;
    case 1: SoftPWMSet(PWM_1, 0);  SoftPWMSet(PWM_2, abs(duty));  break; //thuan
    case 2: SoftPWMSet(PWM_1, abs(duty));  SoftPWMSet(PWM_2, 0);   break; //nghich
  }
}
void Motor_R(int duty) {
  int mode;
  if(duty > 255) duty = 255;
  else if(duty < -255) duty = -255;
  if (duty == 0)
    mode = 0;
  else if (duty > 0)
    mode = 1;
  else
    mode = 2;
  switch (mode) {
    case 0: SoftPWMSet(PWM_3, 0);  SoftPWMSet(PWM_4, 0);  break;
    case 1: SoftPWMSet(PWM_3, abs(duty));  SoftPWMSet(PWM_4, 0);   break; //thuan
    case 2: SoftPWMSet(PWM_3, 0);  SoftPWMSet(PWM_4,  abs(duty));   break; //nghich
  }
}



