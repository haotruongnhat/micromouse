#include "library/include.h"

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))



void setup() {
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
  Serial.begin(9600);
  Sensor_pin_config();
  setupEncoder();
  SoftPWMBegin();
  Timer1.initialize(5000);
  Timer1.attachInterrupt(dcm);

  instantiate();

}
coord desired[] = { { X / 2 - 1, Y / 2 - 1 }, { X / 2 - 1, Y / 2 }, { X / 2, Y / 2 - 1 }, { X / 2, Y / 2 } };
int numDesiredArray = sizeof(desired) / 2;
int currentWall;

void loop() {

  
  while (1) {
    while (Serial.available() > 0)

    //read current wall - user input
      currentWall = Serial.read();
      Serial.print("Doc tuong: ");Serial.println(currentWall);
      maze[globalCoord.y][globalCoord.x].walls = currentWall;
      floodFill(desired, globalCoord, 1);
      Serial.print("Vi tri hien tai: ");
      Serial.print("x: ");Serial.print(globalCoord.x);
      Serial.print("y: ");Serial.print(globalCoord.y);
      Serial.println();
      
      
  }

//  turn90Right(100,100);
//  delay(500);
//  turn90Left(100,100);
//  delay(500);
}
void dcm() {
  readSensor();
  PID();
  left_enc = getLeftEncCount();
  right_enc = getRightEncCount();
  //    Serialprint();
}
void Serialprint() {
  /// IR Sensors
  Serial.print(IR_value_FL + IR_value_FL_offset);
  Serial.print(" ");
  Serial.print(IR_value_L + IR_value_L_offset);
  Serial.print(" ");
  Serial.print(IR_value_R + IR_value_R_offset);
  Serial.print(" ");
  Serial.print(IR_value_FR + IR_value_FR_offset);
  Serial.print(" ");
  ///Encoder
  Serial.print(left_enc);
  Serial.print(" ");
  Serial.print(right_enc);
  Serial.println(" ");
}

