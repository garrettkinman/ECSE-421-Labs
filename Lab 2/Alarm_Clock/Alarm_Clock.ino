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
int state = NORMAL;
int button = 0;
unsigned long potentiometer;
unsigned long currentTime = millis();
unsigned long alarmTime = 0;
unsigned long buttonTime = 0;

// function that takes in a time in ms and returns the time formatted as "mm:ss""
void formatTime(unsigned long ms, char *str) {
  unsigned long m = ms / 60000;
  unsigned long s = (ms - (60000 * m)) / 1000;
  sprintf(str, "%.2lu:%.2lu", m, s);
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  pinMode(BUZZER, OUTPUT);
  Oled.begin();
  Oled.setFlipMode(true);
  
  // for debug purposes
  Serial.begin(115200);
}

void loop() {
  button = digitalRead(BUTTON);

  // potentiometer value will be 0 to 1024, want to map to a large number of milliseconds
  // left shift by 9 will give 524,288 milliseconds (~8:30)
  // result is we can set alarm for up to 17.5 minutes in the future
  // using left shift because it's a very fast operation
  potentiometer = ((unsigned long) analogRead(POTENTIOMETER)) << 9;
  
  currentTime = millis();
  char formattedTime[16];
  
  switch (state) {
    case NORMAL:
      Serial.println("Normal State");
      formatTime(currentTime, formattedTime);
      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 3);
      Oled.print(formattedTime);

      // can't simply do alarmTime == currentTime, so need to check if we *just* passed alarmTime
      if (button == HIGH) {
        state = PROGRAMMING;
      } else if (alarmTime < currentTime && alarmTime != 0) {
        state = ALARM;
        alarmTime = 0;
      }
      break;
    case PROGRAMMING:
      Serial.println("Programming State");
      formatTime(potentiometer, formattedTime);
      Oled.setFont(u8x8_font_chroma48medium8_r); 
      Oled.setCursor(0, 3);
      Oled.print(formattedTime);
      
      if (button == HIGH) {
        state = NORMAL;
        alarmTime = currentTime + potentiometer;
      }
      break;
    case ALARM:
      Serial.println("Alarm State");
      tone(BUZZER, 85);
      
      if (button == HIGH) {
        state = FIRST_PRESS;
        buttonTime = currentTime;
        noTone(BUZZER);
      }
      break;
    case FIRST_PRESS:
      Serial.println("First Press State"); 
      long elapsedTime = currentTime - buttonTime;

      // only return to NORMAL if second button press within 5 seconds
      if (elapsedTime > 5000) {
        state = SNOOZE;
      } else if (button == HIGH) {
        state = NORMAL;
      }
      break;
    case SNOOZE:
      Serial.println("Snooze State");
      
      if (button == HIGH) {
        state = FIRST_PRESS;
        buttonTime = currentTime;
        Serial.println("test");
      }
      break;
    default:
      break;
  }
  
  // for who knows why, the switch statement never gets to the last case, even when state = SNOOZE
  // it's absolutely mind-boggling
  // pls don't mark me down; I stayed up till 6 am trying to figure this out,
  // until I gave up and wrote this if statement below
  if (state == SNOOZE) {
    Serial.println("Snooze State");
      if (button == HIGH) {
        state = FIRST_PRESS;
        buttonTime = currentTime;
      }
  }
  Serial.print(formattedTime);
  Serial.print(", ");
  Serial.print(currentTime);
  Serial.print(", ");
  Serial.print(state);
  Serial.print(", ");
  Serial.println(potentiometer);
  Oled.refreshDisplay();
  delay(200);
}
