#include "Arduino_SensorKit.h"

#define BUTTON 2
#define LED 6

void setup() {
  // initialize pins for IO
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON, turnOn, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON, turnOff, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void turnOn() {
  digitalWrite(LED, HIGH);
}

void turnOff() {
  digitalWrite(LED, LOW);
}
