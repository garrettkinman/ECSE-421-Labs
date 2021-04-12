#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define BUZZER 5
#define LED 6

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  Oled.begin();
  Oled.setFlipMode(true);
}

void buzzTask() {
  // buzz for 1 second, then turn off for 1 second
  tone(BUZZER, 85);
  delay(1000);
  noTone(BUZZER);
  delay(1000);
}

void ledTask() {
  // turn on for 500 ms, then off for 500 ms
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}

void messageTask() {
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 33);
  Oled.print("Hello, world!"); 
  Oled.refreshDisplay();
  delay(2000);
}

void loop() {
  // time the loop and print results to terminal
  loopTimer.check(Serial);
  ledTask();
  buzzTask();
  messageTask();
}
