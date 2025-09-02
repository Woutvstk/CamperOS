#include "taskUiController.h"

void taskUiController(void *parameter)
{

    touchScreen0.init();
    touchScreen0.screen.setRotation(3);

    uint8_t rotaryValue = 70;
    bool rotary_direction = false;

    uint8_t pageData[] = {0, 0, 150, 0, 200, 0};
    // uint8_t *pageDataStart = &pageData[0];

    if (&pageData[0] == NULL)
    {
        Serial.println("pageDataStart null pointer in task, not drawing page");
    }
    else
    {
        touchScreen0.setBrightness(125);
        SdrawerInstruction struct0 = {&graphics::home, &touchScreen0.screen, &pageData[0]};
        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage, now wait 5sec");
        vTaskDelay(5000);

        struct0 = {&graphics::environment, &touchScreen0.screen, &pageData[0]};
        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);
        
        Serial.println("Given command for environmentPage, now wait 5sec");
        vTaskDelay(5000);
    }

    delay(5000);

    while (true)
    {

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(60000 / UiUpdateRate)); // wait for UiUpdateRate or notification, portMAX_DELAY for no timeout

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