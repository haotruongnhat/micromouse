
void Sensor_pin_config(){
  pinMode(IRENABLE_F,OUTPUT);   digitalWrite(IRENABLE_F,LOW);
  pinMode(IRENABLE_LR,OUTPUT);  digitalWrite(IRENABLE_LR,LOW);
  pinMode(IR_FL,INPUT);
  pinMode(IR_FR,INPUT);
  pinMode(IR_L,INPUT);
  pinMode(IR_R,INPUT);
}
void readSensor(){
  long alo = micros();
  IR_value_L=analogRead(IR_L);
  IR_value_R=analogRead(IR_R);
  IR_value_FL=analogRead(IR_FL);
  IR_value_FR=analogRead(IR_FR);
  digitalWrite(IRENABLE_LR,HIGH);
    delayMicroseconds(70);
  IR_value_L=analogRead(IR_L)-IR_value_L;
  IR_value_R=analogRead(IR_R)-IR_value_R;
  digitalWrite(IRENABLE_LR,LOW);
  digitalWrite(IRENABLE_F,HIGH);
    delayMicroseconds(70);
  IR_value_FL=analogRead(IR_FL)-IR_value_FL;
  IR_value_FR=analogRead(IR_FR)-IR_value_FR;
  digitalWrite(IRENABLE_F,LOW);
//  Serial.println(micros()-alo);
}


