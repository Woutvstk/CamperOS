#include <Arduino.h>
#include "globals.h"
#include "pinDefinitions.h"
#include "queues.h"

// List of freeRTOStasks
#include "tasks/taskUiController.h"
#include "tasks/taskUiDrawer.h"

TaskHandle_t xtaskUiControllerHandle = NULL;
TaskHandle_t xtaskUiDrawerHandle = NULL;

// Encoder interrupt routine for both pins. Notifies taskUIController of rotary encoder input
// if they are valid and have rotated a full indent
void IRAM_ATTR rotaryISR()
{

  // code found at: https://garrysblog.com/2021/03/20/reliably-debouncing-rotary-encoders-with-arduino-and-esp32/

  static uint8_t old_AB = 3;                                                               // Lookup table index
  static int8_t encval = 0;                                                                // Encoder value
  static const int8_t enc_states[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0}; // Lookup table
  static bool rotary_direction = 0;
  static bool full_indent_passed = false;

  old_AB <<= 2; // Remember previous state

  if (digitalRead(rotary_ClkPin)) // TODO change digitalRead to PORT read
    old_AB |= 0x02;               // Add current state of pin A
  if (digitalRead(rotary_DtPin))
    old_AB |= 0x01; // Add current state of pin B

  encval += enc_states[(old_AB & 0x0f)];

  // Update counter if encoder has rotated a full indent, that is at least 4 steps
  if (encval > 3)
  { // Four steps forward
    encval = 0;
    rotary_direction = false;
    full_indent_passed = true;
  }
  else if (encval < -3)
  { // Four steps backwards
    encval = 0;
    rotary_direction = true;
    full_indent_passed = true;
  }

  if (full_indent_passed)
  {
    full_indent_passed = false;
    // check if queue is full and no value was added
    if (xQueueSend(QrotaryISR2taskUIController, (void *)&rotary_direction, 0) != pdTRUE) // add an entry to the queue telling taskUIController that a full indent passed with the direction
    {
      Serial.println("### WARNING: QrotaryISR2taskUIController is full, rotary indent was missed ###");
    }
    xTaskNotifyGive(xtaskUiControllerHandle); // notify taskUIController that an update is needed
  }

} // rotaryISR

void setup()
{
  // wait for serial monitor
  delay(1000);

  /*
  Initialize communication busses
  */

  // Initialize serial monitor
  Serial.begin(115200);
  // initialize SPI bus
  spiHandle.begin();
  delay(100);

  /*
  Initialize hardware pins
  */

  // Configure led pin
  pinMode(led_pin, OUTPUT);

  // configure rotary pins
  pinMode(rotary_ClkPin, INPUT_PULLUP);
  pinMode(rotary_DtPin, INPUT_PULLUP);

  delay(200);

  /*
  enable interupts for rotary
  */

  attachInterrupt(digitalPinToInterrupt(rotary_ClkPin), rotaryISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotary_DtPin), rotaryISR, CHANGE);

  /*
   FreeRTOS tasks
  */

  // Start tasks

  //---taskUicontroller
  xTaskCreatePinnedToCore(      // Use xTaskCreate() in vanilla FreeRTOS
      taskUiController,         // Function to be called
      "taskUiController",       // Name of task
      8192,                     // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                     // Parameter to pass to function
      10,                       // Task priority (0 to configMAX_PRIORITIES - 1) (default 0 to 24)
      &xtaskUiControllerHandle, // Task handle
      tskNO_AFFINITY);          // Select core or tskNO_AFFINITY (ESP32 only)

  //---taskUiDrawer
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
      taskUiDrawer,         // Function to be called
      "taskUiDrawer",       // Name of task
      16000,                // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                 // Parameter to pass to function
      8,                    // Task priority (0 to configMAX_PRIORITIES - 1) (default 0 to 24)
      &xtaskUiDrawerHandle, // Task handle
      tskNO_AFFINITY);      // Select core or tskNO_AFFINITY (ESP32 only)

  // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
  // main after setting up your tasks.

  // delete this task: setup() and loop()
  vTaskDelete(NULL);
}

void loop()
{
  Serial.println("#### ERROR: inside loop, should not happen ####");
  delay(500);
  // scheduler should never get here. Arduino requeres this do be defined
}
