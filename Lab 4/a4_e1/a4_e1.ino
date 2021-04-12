#include <Arduino_FreeRTOS.h>
#include "Arduino_SensorKit.h"
#include "loopTimer.h"
#include <semphr.h>

#define BUZZER 5
#define LED 6

// declare tasks
void buzzTask(void *pvParameters);
void ledTask(void *pvParameters);
void messageTask(void *pvParameters);

// declare global mutex for the serial port
SemaphoreHandle_t serialMutex;

void setup() {
  Serial.begin(9600);

  // create a mutex for the serial port
  serialMutex = xSemaphoreCreateMutex();
  if (serialMutex == NULL) Serial.println("Mutex cannot be created!");
  
  // construct tasks to run concurrently
  // loopTimer seems to take up too much memory, hence its absence
  // all tasks are at same priority level, as none is really any more important than the others
  xTaskCreate(
    ledTask,
    "Blink",
    128, // stack size
    NULL,
    2, // priority (1-3, where 3 is highest)
    NULL);
  xTaskCreate(
    buzzTask,
    "Buzz",
    128, // stack size
    NULL,
    2, // priority (1-3, where 3 is highest)
    NULL);
  xTaskCreate(
    messageTask,
    "Hello, world!",
    128, // stack size
    NULL,
    2, // priority (1-3, where 3 is highest)
    NULL);
}

void buzzTask(void *pvParameters) {
  (void) pvParameters;

  // setup
  pinMode(BUZZER, OUTPUT);

  // loop
  for (;;) {
    // turn on for 100 ms
    // then turn off for a second
    // vTaskDelay(...) hands control back over to the RTOS so other tasks can run
    // mutex is here to protect serial port
    tone(BUZZER, 85);
    xSemaphoreTake(serialMutex, portMAX_DELAY);
    Serial.println("'buzz buzz buzz' -a bee, probably");
    xSemaphoreGive(serialMutex);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    noTone(BUZZER);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void ledTask(void *pvParameters) {
  (void) pvParameters;

  // setup
  pinMode(LED, OUTPUT);

  // loop
  for (;;) {    
    // turn on for half a second
    // then turn off for half a second
    // vTaskDelay(...) hands control back over to the RTOS so other tasks can run
    // mutex is here to protect serial port
    digitalWrite(LED, HIGH);
    xSemaphoreTake(serialMutex, portMAX_DELAY);
    Serial.println("THIS LED IS ON FIIIIIIIIRE");
    xSemaphoreGive(serialMutex);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void messageTask(void *pvParameters) {
  (void) pvParameters;

  // setup
  Oled.begin();
  Oled.setFlipMode(true);

  // loop
  for (;;) {
    // display for 2 seconds
    // then remain clear for 2 seconds
    // vTaskDelay(...) hands control back over to the RTOS so other tasks can run
    // mutex is here to protect serial port
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 33);
    Oled.print("Hello, world!"); 
    Oled.refreshDisplay();
    xSemaphoreTake(serialMutex, portMAX_DELAY);
    Serial.println("'Hello, world!' is your first program, but is 'Goodbye, cruel world!' your last?");
    xSemaphoreGive(serialMutex);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    Oled.clear();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void loop() {
  // empty because all the work is done in tasks (also to make FreeRTOS happy)
}
