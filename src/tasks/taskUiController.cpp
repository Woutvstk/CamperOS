#include "taskUiController.h"

void taskUiController(void *parameter)
{

    hardware::touchScreen0.init();
    hardware::touchScreen0.screen->setRotation(display0Rotation);

    uint8_t rotaryValue = 70;
    bool rotary_direction = false;
    SdrawerInstruction struct0 = {&graphics::home, hardware::touchScreen0.screen};

    vTaskDelay(100);

    hardware::touchScreen0.setBrightness(100);

    while (true)
    {

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(60000 / UiUpdateRate)); // wait for UiUpdateRate or notification, portMAX_DELAY for no timeout

        /*
        // draw home version 1
        graphics::home.Circle0.pos_x_px = 100;
        struct0 = {&graphics::home, &(touchScreen0.screen)};

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage V1, circlePosX = 100, now wait 5sec");
        vTaskDelay(2000);


        // draw home version 2
        graphics::home.Circle0.pos_x_px = 30;

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage V2, circlePosX = 30, now wait 5sec");
        vTaskDelay(5000);
        */

        // draw environment with graphs on it

        struct0.page = &(graphics::environment);
        uint8_t graphPoints[] = {115, 157, 145, 112, 158, 123, 145, 185, 124, 168, 112, 112, 235, 224, 220, 115, 145, 118, 148, 159, 169, 170};
        graphics::environment.Graph0.data = (uint8_t *)&graphPoints[0];
        graphics::environment.Graph0.pointCount = sizeof(graphPoints) / sizeof(graphPoints[0]);
        graphics::environment.Graph0.graphLineWidth = 3;
        graphics::environment.Graph0.graphFill = true;
        graphics::environment.Graph0.graphLineColor = ILI9341_GREEN;
        graphics::environment.Graph0.graphFillColor = ILI9341_DARKGREEN;

        uint8_t graphPoints2[] = {124, 168, 112, 112, 235, 224, 220, 115, 145, 118, 148, 159, 169, 170};
        graphics::environment.Graph1.data = (uint8_t *)&graphPoints2[0];
        graphics::environment.Graph1.pointCount = sizeof(graphPoints2) / sizeof(graphPoints2[0]);
        graphics::environment.Graph1.graphFill = false;
        graphics::environment.Graph1.graphLineColor = ILI9341_RED;
        graphics::environment.Graph1.axesLabelMaxX = 10;
        graphics::environment.Graph1.axesLabelMinX = -10;
        graphics::environment.Graph1.axesLabelMaxY = 999;
        graphics::environment.Graph1.axesLabelMinY = 0;
        graphics::environment.Graph1.axesLabelColor = ILI9341_GREEN;
        graphics::environment.Graph1.frameAllSides = true;
        graphics::environment.Graph1.axesWidth = 0;

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);
    }
}
