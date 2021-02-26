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
int state = 1;
int button = 0;
unsigned long currentTime = millis();
unsigned long alarmTime = 0;
unsigned long buttonTime = 0;

// function that takes in a time in ms and returns the time formatted as "mm:ss""
char* formatTime(unsigned long ms) {
  unsigned long s = ms / 1000;
  ms %= 1000;
  
  unsigned long m = s / 60;
  s %= 60;

  char timeFormatted[8];
  sprintf(timeFormatted, "%u:%u", m, s);

  return timeFormatted;
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
  switch (state) {
    case NORMAL:
      Oled.print(formatTime(currentTime);
    case PROGRAMMING:

    case ALARM:

    case FIRST_PRESS:

    case SNOOZE:
    
  }
  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 3);
  Oled.print("Value: ");
  Oled.print(random_value);
  delay(250);
}
