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

        // uint8_t pageData[] = {0, 0, 150, 0, 200, 0};

        // uint8_t *pageData2 = new uint8_t[6];

        // delete[] pageData2;

        // if(thisArraySize == lastArraySize) {

        touchScreen0.setBrightness(125);
        graphics::home.Circle0.pos_x_px = 100;

        SdrawerInstruction struct0 = {&graphics::home, &touchScreen0.screen};
        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage, circlePosX = 100, now wait 5sec");
        vTaskDelay(5000);

        graphics::home.Circle0.pos_x_px = 30;

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for homePage, circlePosX = 30, now wait 5sec");
        vTaskDelay(5000);

        struct0 = {&graphics::environment, &touchScreen0.screen};
        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);

        Serial.println("Given command for environmentPage, now wait 5sec");
        vTaskDelay(5000);
    }
}
