#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define BUZZER 5

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
}

void buzzTask() {
  // buzz for 1 second, then turn off for 1 second
  tone(BUZZER, 85);
  delay(1000);
  noTone(BUZZER);
  delay(1000);
}

void loop() {
  // time the loop and print results to terminal
  loopTimer.check(Serial);
  buzzTask();
}
