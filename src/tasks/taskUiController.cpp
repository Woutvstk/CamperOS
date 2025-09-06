#include "taskUiController.h"

void taskUiController(void *parameter)
{

    touchScreen0.init();
    touchScreen0.screen.setRotation(display0Rotation);

    uint8_t rotaryValue = 70;
    bool rotary_direction = false;

    vTaskDelay(100);

    while (true)
    {

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(60000 / UiUpdateRate)); // wait for UiUpdateRate or notification, portMAX_DELAY for no timeout

        touchScreen0.setBrightness(255);

        // draw home version 1
        graphics::home.Circle0.pos_x_px = 100;
        SdrawerInstruction struct0 = {&graphics::home, &(touchScreen0.screen)};

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage V1, circlePosX = 100, now wait 5sec");
        vTaskDelay(5000);

        // draw home version 2
        graphics::home.Circle0.pos_x_px = 30;

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage V2, circlePosX = 30, now wait 5sec");
        vTaskDelay(5000);

        // draw environment with graph on it
        struct0.page = &(graphics::environment);
        uint8_t graphPoints[] = {50, 70, 150, 100, 200, 250, 50, 75};
        graphics::environment.Graph0.data = (uint8_t *)&graphPoints;
        graphics::environment.Graph0.pointCount = sizeof(graphPoints) / sizeof(graphPoints[0]);

        if (graphics::environment.Graph0.data != nullptr)
        {
            xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
            xTaskNotifyGive(xtaskUiDrawerHandle);
        }
        else
        {
            Serial.println("graph0.data Pointing to NULL");
        }
        Serial.println("Given command for environmentPage, now wait 5sec");
        vTaskDelay(5000);
    }
}
