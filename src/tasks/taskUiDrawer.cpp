#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); //wait for notification from taskUiController to start drawing


    }
}