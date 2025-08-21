#include "taskUiController.h"

// TaskUiController
// Gathers information and adds it to an array for the taskUiDrawer task
// handles user input (rotary, touchscreen, ...)
void taskUiController(void *parameter)
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