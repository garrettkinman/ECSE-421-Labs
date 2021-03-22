#include "Arduino_SensorKit.h"

#define LED 3
#define POTENTIOMETER A0

void setup() {
  // initialize pins for IO
  pinMode(LED, OUTPUT);
  pinMode(POTENTIOMETER, INPUT);

  // set up fast PWM on TIMER2
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2B = 50; // default to (arbitrary) ~20% duty cycle on pin D3
}

void loop() {
  // map the potentiometer values to be valid 8-bit numbers
  int value = map(analogRead(POTENTIOMETER), 0, 1023, 0, 255);
  pwm(value);
}

// function to adjust the duty cycle
// val must be 0 to 255, as PWM works by adjusting what the timer counts up to
// and timer is 8-bit
void pwm(int val) {
  OCR2B = val;
}
