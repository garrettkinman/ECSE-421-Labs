#include "Arduino_SensorKit.h"

#define BUTTON 2
#define LED 6

volatile byte state = LOW;

void setup() {
  // initialize pins for IO
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  // attach the interrupt to trigger on a button press or release
  // note that sometimes it double detects a press or release; this is accounted for in the ISR to still be correct
  attachInterrupt(digitalPinToInterrupt(BUTTON), blink, CHANGE);

  // for debug purposes
  Serial.begin(115200);
}

void loop() {
  delay(100);
}

// ISR
void blink() {
  // digital read (and not simply `state = !state`) to avoid the "double detection" problem stated earlier
  state = digitalRead(BUTTON);
  digitalWrite(LED, state);
  if (state == HIGH) Serial.println("on");
  else Serial.println("off");
}
