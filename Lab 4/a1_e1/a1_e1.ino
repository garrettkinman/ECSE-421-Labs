#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define LED 6

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void ledTask() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}

void loop() {
  loopTimer.check(Serial);
  ledTask();
}
