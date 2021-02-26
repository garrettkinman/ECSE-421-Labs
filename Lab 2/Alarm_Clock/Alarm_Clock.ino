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
unsigned long potentiometer;
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
      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 3);
      Oled.print(formatTime(currentTime);

      // can't simply do alarmTime == currentTime, so need to check if we *just* passed alarmTime
      if (button == HIGH) {
        state = PROGRAMMING;
      } else if (alarmTime < currentTime && alarmTime != 0) {
        state = ALARM;
      }
      break;
    case PROGRAMMING:
      // potentiometer value will be 0 to 1024, want to map to a large number of milliseconds
      // left shift by 10 will give 1,048,576 milliseconds (~17:30)
      // result is we can set alarm for up to 17.5 minutes in the future
      // using left shift because it's a very fast operation
      unsigned long potentiometer = analogRead(POTENTIOMETER) << 10)
      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 3);
      Oled.print(formatTime(potentiometer));

      if (button == HIGH) {
        state = NORMAL;
        alarmTime = currentTime + potentiometer;
      }
      break;
    case ALARM:
      tone(BUZZER, 85);
      // TODO: flash

      if (button == HIGH) {
        state = FIRST_PRESS;
        buttonTime = currentTime;
        noTone(BUZZER);
      }
      break;
    case FIRST_PRESS:
      // TODO: flash
      unsigned long elapsedTime = currentTime - buttonTime;

      if (elapsedTime > 5000) {
        state = SNOOZE;
      } else if (button == HIGH) {
        state = NORMAL;
      }
      break;
    case SNOOZE:
      // TODO: flash

      if (button == HIGH) {
        buttonTime = currentTime;
      }
      break;
  }

  delay(250);
}
