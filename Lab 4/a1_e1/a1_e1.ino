#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define LED 6

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void ledTask() {
  // turn on for 500 ms, then off for 500 ms
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}

void loop() {
  // time the loop and print results to terminal
  loopTimer.check(Serial);
  ledTask();
}
