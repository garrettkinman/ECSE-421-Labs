#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define BUZZER 5
#define LED 6

// variables to store the last time the tasks were called
unsigned long ledTime = 0;
unsigned long buzzTime = 0;
unsigned long messageTime = 0;

int ledState = LOW; // LOW => off; HIGH => on
int buzzState = false; // false => noTone; true => tone
int messageState = false; // false => clear; true => "Hello, world!"

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  Oled.begin();
  Oled.setFlipMode(true);
}

void buzzTask() {
  // update buzzTime so next call of buzzTask won't happen until another second has passed
  buzzTime = millis();
  
  // if buzzer is currently on, turn it off
  // if buzzer is currently off, turn it on
  if (buzzState) {
    buzzState = false;
    noTone(BUZZER);
  } else {
    buzzState = true;
    tone(BUZZER, 85);
  }

  // print to the terminal
  Serial.println("buzzTask running");
}

void ledTask() {
  // update ledTime so next call of ledTask won't happen until another 500 ms have passed
  ledTime = millis();

  // don't need if statements since turning on and off can directly use state variable, unlike buzzer
  ledState = !ledState;
  digitalWrite(LED, ledState);

  // print to the terminal
  Serial.println("ledTask running");
}

void messageTask() {
  // update messageTime so next call of ledTask won't happen until another 500 ms have passed
  messageTime = millis();

  // if message is currently displayed, clear it
  // if display is currently clear, display the message
  if (messageState) {
    messageState = false;
    Oled.clear();
  } else {
    messageState = true;
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 33);
    Oled.print("Hello, world!"); 
    Oled.refreshDisplay();
  }

  // print to the terminal
  Serial.println("messageTask running");
}

void loop() {
  // time the loop and print results to terminal
  loopTimer.check(Serial);

  // only call a task if enough time has elapsed since its last call
  if ((millis() - ledTime) > 500) ledTask();
  if ((millis() - buzzTime) > 1000) buzzTask();
  if ((millis() - messageTime) > 2000) messageTask();
}
