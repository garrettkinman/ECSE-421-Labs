#include "Arduino_SensorKit.h"

#define LED 6
#define POTENTIOMETER A0

void setup() {
  // begin serial communication
  Serial.begin(9600);
  // set potentiometer and LED pins as input and outputs, respectively
  pinMode(POTENTIOMETER, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  int sensor_value = analogRead(POTENTIOMETER);

  Serial.print("Potentiometer value: ");
  Serial.println(sensor_value);

  if (sensor_value >= 512) {
    // turn LED on
    digitalWrite(LED, HIGH);
  } else {
    // turn LED off
    digitalWrite(LED, LOW);
  }
  delay(500);
}
