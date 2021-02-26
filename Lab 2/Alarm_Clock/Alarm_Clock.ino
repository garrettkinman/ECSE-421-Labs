#include "Arduino_SensorKit.h"

#define BUTTON 4
#define BUZZER 5
#define POTENTIOMETER A0

void setup() {
  Oled.begin();
  Oled.setFlipMode(true);
  pinMode(BUTTON, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  int random_value = random(0, 1023);   // create a random value

  Oled.setFont(u8x8_font_chroma48medium8_r); 
  Oled.setCursor(0, 3);
  Oled.print("Value: ");
  Oled.print(random_value);
  delay(1000);
}
