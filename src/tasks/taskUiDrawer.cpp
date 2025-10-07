#include "taskUiDrawer.h"

void taskUiDrawer(void *parameter)
{

    unsigned long tempMillis;
    unsigned long renderTime;
    unsigned long transferTime;

    while (true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification from taskUiController to start drawing

        SdrawerInstruction currentInstruction;

        if (!xQueueReceive(QtaskUIController2taskDrawer, &currentInstruction, 0)) // in case of race condition around controller->drawer queue
        {
            // Serial.println(" [taskUiDrawer] - received notification but no item in queue, not drawing");
        }
        else if (&currentInstruction == nullptr) // in case of programming error in UiController
        {
            Serial.println(" [taskUiDrawer] - currentInstruction is a NULL pointer, not drawing");
        }
        else if ((currentInstruction.page) == nullptr) // in case of programming error in UiController
        {
            Serial.println(" [taskUiDrawer] - currentInstruction.page is a null pointer, not draWing");
        }
        else if (currentInstruction.touchScreen->hasScreen() == 0) // in case the touchScreen does not have a screen defined
        {
            Serial.println(" [taskUiDrawer] - currentInstruction.touchScreen has no screen, not drawing");
        }
        else // all is good to start drawing
        {
            GFXcanvas16 *canvas = new GFXcanvas16(currentInstruction.touchScreen->screenSizeX, currentInstruction.touchScreen->screenSizeY);

            // rotate canvas instead of screen so that rotation calculations happen during rendering instead of data transfer
            canvas->setRotation(currentInstruction.touchScreen->rotation);

            tempMillis = millis();
            (currentInstruction.page)->draw(canvas);
            renderTime = millis() - tempMillis;

            tempMillis = millis();
            // always touchScreen->screenSizeX as width because screen rotation is kept at 0
            currentInstruction.touchScreen->drawRGBBitmap(0, 0, canvas->getBuffer(), currentInstruction.touchScreen->screenSizeX, currentInstruction.touchScreen->screenSizeY);
            transferTime = millis() - tempMillis;
            delete canvas;

            // Serial.printf(" [taskUiDrawer] - renderTime is: %d, transferTime is: %d. Total time: %d\n", renderTime, transferTime, renderTime + transferTime);
        }
    }
}
