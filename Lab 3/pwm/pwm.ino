#include "Arduino_SensorKit.h"

#define LED 3

void setup() {
  // initialize pins for IO
  // set LED as OUTPUT
  pinMode(LED, OUTPUT);

  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 180;
  OCR2B = 50;
}

void loop() {
}

// val must be 0 to 255
void pwm(int val) {
  OCR2A = val;
}
