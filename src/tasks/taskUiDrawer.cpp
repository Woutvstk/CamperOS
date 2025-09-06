#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from taskUiController to start drawing

        SdrawerInstruction currentInstruction;

        if (xQueueReceive(QtaskUIController2taskDrawer, &currentInstruction, 0)) // check if something was received from queue
        {
            if (&currentInstruction == nullptr)
            {
                Serial.println("currentInstruction is a NULL pointer, not drawing");
            }
            else
            {
                if ((currentInstruction.page) == nullptr)
                {
                    Serial.println("currentInstruction.page is a null pointer, not draWing");
                }
                else
                {
                    if (currentInstruction.screen == nullptr)
                    {
                        Serial.println(" ####### currentInstruction.screen is a nullptr");
                    }
                    else
                    {

                        (currentInstruction.page)->draw(currentInstruction.screen);
                    }
                }
            }
        }
    }
}
