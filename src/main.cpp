

#include <Arduino.h>
#include "pinDefinitions.h"
#include "queues.h"
#include "config.h"
#include "hardware.h"
#include "graphics.h" // pages, pageElements, ...

SPIClass spiHandle = SPIClass(FSPI);
//  create screen object
graphics::touchScreen<Adafruit_ILI9341> touchScreen0(spiHandle, touchScreen0_screen_DataCommand, touchScreen0_screen_ChipSelect, touchScreen0_screen_Reset, touchScreen0_screen_BackLight);

// Task handles
static TaskHandle_t xtaskUIControllerHandle = NULL;

// Update user interface screen
// run at rate UiUpdateRate or when receiving notification
// This task gathers information, adds it to a struct for the currently displayed page and calls the graphics class to draw this page.

void taskUIController(void *parameter)
{

  uint8_t rotaryValue = 70;
  bool rotary_direction = false;

  uint8_t pageData[] = {0, 0, 150, 0, 200, 0};
  uint8_t *pageDataStart = &pageData[0];

  if (pageDataStart == NULL)
  {
    Serial.println("pageDataStart null pointer in task, not drawing page");
  }
  else
  {
    touchScreen0.setBrightness(125);
    graphics::home.draw(pageDataStart, touchScreen0.screen);
  }

  delay(5000);

  while (true)
  {
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(60000 / UiUpdateRate)); // wait for UiUpdateRate or notification

    xQueueSend(QrotaryISR2taskUIController, (void *)&rotary_direction, 0); // TODO remove, simulates encoder rotation

    // check and process if there is anything in the queue from rotaryEncISR
    while (xQueueReceive(QrotaryISR2taskUIController, (void *)&rotary_direction, 0) == pdTRUE)
    {
      if (rotary_direction)
      {
        rotaryValue -= 10;
        // touchScreen0.setBrightness(rotaryValue);
        //  touchScreen0.drawNumber(rotaryValue);
      }
      else
      {
        rotaryValue += 10;
        // touchScreen0.setBrightness(rotaryValue);
        // touchScreen0.drawNumber(rotaryValue);
      }
    }

    Serial.printf("Current rotary position is: %d \n\r", rotaryValue);
  }
}

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
    xTaskNotifyGive(xtaskUIControllerHandle); // notify taskUIController that an update is needed
  }

} // rotaryISR

void setup()
{
  // wait for serial monitor
  delay(4000);

  Serial.begin(115200);
  delay(100);
  // Configure led pin
  pinMode(led_pin, OUTPUT);

  // configure rotary pins
  pinMode(rotary_ClkPin, INPUT_PULLUP);
  pinMode(rotary_DtPin, INPUT_PULLUP);

  // initialize SPI bus
  spiHandle.begin();

  // TODO: move this to UIDrawer task
  touchScreen0.init();
  touchScreen0.screen.setRotation(3);

  delay(200);
  // begin serial to PC

  // enable interupts
  // attachInterrupt(digitalPinToInterrupt(rotary_ClkPin), rotaryISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(rotary_DtPin), rotaryISR, CHANGE);

  // FreeRTOS tasks
  //  User interface task that does the drawing

  xTaskCreatePinnedToCore(      // Use xTaskCreate() in vanilla FreeRTOS
      taskUIController,         // Function to be called
      "Task UI",                // Name of task
      8192,                     // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                     // Parameter to pass to function
      2,                        // Task priority (0 to configMAX_PRIORITIES - 1)
      &xtaskUIControllerHandle, // Task handle
      tskNO_AFFINITY);          // Run on one core for demo purposes (ESP32 only)  tskNO_AFFINITY

  // If this was vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in
  // main after setting up your tasks.

  // delete task setup() and loop()
  vTaskDelete(NULL);
}

void loop()
{
  Serial.println("inside loop = problem");
  delay(500);
  // scheduler should never get here. Arduino requeres this do be defined
}
