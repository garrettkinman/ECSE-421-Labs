#include "Arduino_SensorKit.h"

#define LED 6

void setup() {
  // initialize pins for IO
  pinMode(LED, OUTPUT);

  // setup timer
  TCCR1A = (TCCR1A & B00111100) | B10000010;
  TCCR1B = (TCCR1B & B11100000) | B00010001;
  ICR1 = 0xFFFF;
}

void loop() {
  //Increasing pulse
  for(unsigned int i=0;i<65535;i++){
    pwm_16(i);
  }
  //Decreasing pulse
  for(unsigned int j=65535;j!=0;j--){
    pwm_16(j);
  }
}

void pwm_16(int_val) {
  OCR1A = val;
}
