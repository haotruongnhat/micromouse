void pciSetup(byte pin){
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
  PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
  PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}
void setupEncoder() {
  pinMode(ENC_LA, INPUT);
  pinMode(ENC_RA, INPUT);
  pinMode(ENC_LB, INPUT);
  pinMode(ENC_RB, INPUT);
  pciSetup(ENC_RA);
  pciSetup(ENC_LA);  
}
ISR (PCINT0_vect){
  if(digitalRead(ENC_RA)^digitalRead(ENC_RB))
    right++;
  else
    right--;
}
volatile long getRightEncCount(){
  return right;
}
void resetRightEncCount(){
  right = 0;
}
ISR (PCINT2_vect) {
  if(digitalRead(ENC_LA)^digitalRead(ENC_LB))
    left--;
  else
    left++;
}
volatile long getLeftEncCount(){
  return left;
}
void resetLeftEncCount(){
  left = 0;
}

