#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from taskUiController to start drawing
        SdrawerInstruction currentInstruction;
        if (xQueueReceive(QtaskUIController2taskDrawer, &currentInstruction, 0)) // check if something was received from queue
        {
            currentInstruction.page->draw(currentInstruction.dataStart, *currentInstruction.screen);
        }

    }
}
