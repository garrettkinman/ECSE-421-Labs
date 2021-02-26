#include "Arduino_SensorKit.h"

// pin declarations
#define BUTTON 4
#define BUZZER 5
#define POTENTIOMETER A0

// state types
#define NORMAL 1
#define PROGRAMMING 2
#define ALARM 3
#define FIRST_PRESS 4
#define SNOOZE 5

// global variables
int button = 0;
unsigned long currentTime = millis();
unsigned long alarmTime = 0;
unsigned long buttonTime = 0;

char* formatTime(unsigned long ms) {
  // TODO
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  pinMode(BUZZER, OUTPUT);
  Oled.begin();
  Oled.setFlipMode(true);
}

void loop() {
  button = digitalRead(BUTTON);
  currentTime = millis();

  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 3);
  Oled.print("Value: ");
  Oled.print(random_value);
  delay(250);
}
