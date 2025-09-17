#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    bool fail = false;

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from taskUiController to start drawing

        SdrawerInstruction currentInstruction;

        if (!xQueueReceive(QtaskUIController2taskDrawer, &currentInstruction, 0)) // check if something was received from queue
        {
            Serial.println(" [taskUiDrawer] - received notification but no item in queue, not drawing");
            fail = true;
        }

        if (&currentInstruction == nullptr)
        {
            Serial.println(" [taskUiDrawer] - currentInstruction is a NULL pointer, not drawing");
            fail = true;
        }

        if ((currentInstruction.page) == nullptr)
        {
            Serial.println(" [taskUiDrawer] - currentInstruction.page is a null pointer, not draWing");
            fail = true;
        }

        if (currentInstruction.touchScreen->screen == nullptr)
        {
            Serial.println(" [taskUiDrawer] - currentInstruction.screen is a nullptr, not drawing");
            fail = true;
        }

        if (!fail)
        {
            (currentInstruction.page)->draw(currentInstruction.touchScreen->screen);
        }

        fail = false;
    }
}
