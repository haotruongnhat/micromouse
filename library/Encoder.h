#ifndef _ENCODER_H
#define _ENCODER_H

#define ENC_LA                2
#define ENC_LB                4
#define ENC_RA                8
#define ENC_RB                12

volatile long left,right;
volatile long left_enc, right_enc;
void pciSetup(byte pin);

#endif
