#include <Arduino_FreeRTOS.h>
#include "Arduino_SensorKit.h"
#include "loopTimer.h"

#define BUZZER 5
#define LED 6

// declare tasks
void buzzTask(void *pvParameters);
void ledTask(void *pvParameters);
void messageTask(void *pvParameters);

void setup() {
  Serial.begin(9600);
  
  // construct tasks to run concurrently
  xTaskCreate(
    ledTask,
    "Blink",
    128,
    NULL,
    2,
    NULL);
  xTaskCreate(
    buzzTask,
    "Buzz",
    128,
    NULL,
    2,
    NULL);
  xTaskCreate(
    messageTask,
    "Hello, world!",
    128,
    NULL,
    2,
    NULL);
}

void buzzTask(void *pvParameters) {
  (void) pvParameters;

  pinMode(BUZZER, OUTPUT);
  
  for (;;) {
    tone(BUZZER, 85);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    noTone(BUZZER);
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
  }
}

void ledTask(void *pvParameters) {
  (void) pvParameters;

  pinMode(LED, OUTPUT);

  for (;;) {    
    digitalWrite(LED, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void messageTask(void *pvParameters) {
  (void) pvParameters;
  
  Oled.begin();
  Oled.setFlipMode(true);

  for (;;) {
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 33);
    Oled.print("Hello, world!"); 
    Oled.refreshDisplay();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    Oled.clear();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void loop() {
}
