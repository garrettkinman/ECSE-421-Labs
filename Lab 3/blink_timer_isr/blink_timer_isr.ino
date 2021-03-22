#include "Arduino_SensorKit.h"

#define LED 6

volatile byte state = LOW;

void setup() {
  // initialize pins for IO
  // set LED as OUTPUT
  DDRD = B01000000;

  // setup timer
  cli(); // disable interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0; // init counter to 0
  OCR1A = 7811; // set counter compare value
  TCCR1B |= (1 << WGM12); // enable CTC mode
  TCCR1B |= (1 << CS12)|(1 << CS10); // set prescalar
  TIMSK1 |= (1 << OCIE1A); // enable timer interrupt
  sei(); // re-enable interrupts
}

void loop() {
}

// ISR for timer
ISR(TIMER1_COMPA_vect) {
  // toggle on/off at every timer interrupt
  state = !state;
  switch (state) {
    case LOW:
      // set LED to LOW
      PORTD = B00000000;
      break;
    case HIGH:
      // set LED to HIGH
      PORTD = B01000000;
      break;
  }
}
