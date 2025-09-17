#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    bool fail = false;
    unsigned long tempMillis;
    unsigned long renderTime;
    unsigned long transferTime;

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
            GFXcanvas16 *canvas = NULL;
            if (currentInstruction.touchScreen->rotation & 1)
            {
                canvas = new GFXcanvas16(currentInstruction.touchScreen->screenHeight, currentInstruction.touchScreen->screenWidth);
            }
            else
            {
                canvas = new GFXcanvas16(currentInstruction.touchScreen->screenWidth, currentInstruction.touchScreen->screenHeight);
            }
            currentInstruction.touchScreen->screen->setRotation(currentInstruction.touchScreen->rotation);
            tempMillis = millis();
            (currentInstruction.page)->draw(canvas);
            renderTime = millis() - tempMillis;

            tempMillis = millis();
            currentInstruction.touchScreen->screen->drawRGBBitmap(0, 0, canvas->getBuffer(), canvas->width(), canvas->height());
            transferTime = millis() - tempMillis;
            delete canvas;

            //Serial.printf(" [taskUiDrawer] - renderTime is: %d, transferTime is: %d. Total time: %d\n", renderTime, transferTime, renderTime + transferTime);
        }

        fail = false;
    }
}
