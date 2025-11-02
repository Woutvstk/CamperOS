#include "taskUiController.h"

using namespace graphics;
using namespace hardware;

IRAM_ATTR
void touchInputIsr(void)
{
    touchScreen0.touchIsr();

    // create variable to store if higher priority task has been woking by notification
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Give notification and store pdTRUE in xHigherPriorityTaskWoken if needed
    vTaskNotifyGiveFromISR(xtaskUiControllerHandle, &xHigherPriorityTaskWoken);

    // request context switch immediatly after ISR if needed
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void taskUiController(void *parameter)
{
    delay(1000);
    uint16_t notifyWaitTime = defaultUiControllerNotifyWait;
    uint16_t nextRunTime = 0;

    // initialize touchscreens
    touchScreen0.init();
    touchScreen0.enableTouchIsr(touchInputIsr);
    touchScreen0.setRotation(3);
    touchScreen0.setBrightness(255);

    uint8_t rotaryValue = 70;
    bool rotary_direction = false;
    SdrawerInstruction struct0 = {&home, &(touchScreen0)};

    vTaskDelay(100);
    uint8_t startPoint = 0;

    uint16_t touchPos_x = 0;
    uint16_t touchPos_y = 0;
    uint8_t touchPos_z = 0;

    while (true)
    {

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(notifyWaitTime)); // wait for UiUpdateRate or notification, portMAX_DELAY for no timeout
        notifyWaitTime = defaultUiControllerNotifyWait;          // change notifyWaitTime to default. Can be reduced during this run if needed

        // there was a touch change
        if (touchScreen0.touchIsrWake())
        {
            // touched or released
            if (touchScreen0.touch->touched())
            {
                touchScreen0.touchReadRaw(&touchPos_x, &touchPos_y, &touchPos_z);
                touchScreen0.applyCalibration(&touchPos_x, &touchPos_y);
                touchInputEvent event0 = touchScreen0.currentPage->getInputEvent(touchPos_x, touchPos_y, touchPos_z);
                if (event0.sourceElement != nullptr)
                {
                    if (touchScreen0.currentPage == &environment)
                    {
                        if (event0.sourceElement == &environment.Circle0)
                        {
                            printf("touched circle with value: %d\n", event0.data.unsignedNumber);
                        }
                        else
                        {
                            printf("touched other with value: %d\n", event0.data.unsignedNumber);
                        }
                    }
                    else if (touchScreen0.currentPage == &home)
                    {
                        printf("home page with value: %d\n", event0.data.unsignedNumber);
                    }
                }
                environment.Circle0.color = ILI9341_GREEN;
                Serial.printf("X: %d, Y: %d, Z: %d\n", touchPos_x, touchPos_y, touchPos_z);
            }
            else
            {
                environment.Circle0.color = ILI9341_BLUE;
            }
            touchScreen0.handleTouchIsr(&nextRunTime);

            notifyWaitTime = nextRunTime - millis();
        }

        // draw environment with graphs on it

        struct0.page = &(environment);
        uint8_t graphPoints[] = {115, 157, 145, 112, 123, 145, 185, 124, 168, 112, 112, 235, 224, 220, 115, 145, 118, 148, 159, 169, 170, 210, 250, 150, 120, 140, 100, 80};
        environment.Graph0.data = (uint8_t *)&graphPoints[0];
        environment.Graph0.pointCount = (sizeof(graphPoints) / sizeof(graphPoints[0]));
        environment.Graph0.graphLineWidth = 3;
        environment.Graph0.graphFill = true;
        environment.Graph0.graphLineColor = ILI9341_GREEN;
        environment.Graph0.graphFillColor = ILI9341_DARKGREEN;
        environment.Text0.text = "This is test\ntext 12345, and some\nmore text";
        environment.Text0.textSize = 1;
        environment.Text0.borderWidth = 3;
        environment.Text0.padding = 3;
        environment.Text0.borderColor = 0xFFFF;
        environment.Text0.textAlign = CENTRE;
        environment.Text0.size_y_px = 100;
        environment.Text0.size_x_px = 200;
        environment.Text0.fillColor = ILI9341_RED;
        environment.Text0.enableFill = true;
        environment.Circle0.touchAble = true;
        environment.Text0.touchAble = true;

        if (startPoint < 13)
        {
            startPoint++;
        }
        else
        {
            startPoint = 0;
        }

        environment.Graph1.data = (uint8_t *)&graphPoints[startPoint];
        environment.Graph1.pointCount = 14;
        environment.Graph1.graphFill = false;
        environment.Graph1.graphLineColor = ILI9341_RED;
        environment.Graph1.axesLabelMaxX = 10;
        environment.Graph1.axesLabelMinX = -10;
        environment.Graph1.axesLabelMaxY = 999;
        environment.Graph1.axesLabelMinY = 0;
        environment.Graph1.axesLabelColor = ILI9341_GREEN;
        environment.Graph1.frameAllSides = true;
        environment.Graph1.axesWidth = 0;

        xQueueSend(QtaskUIController2taskDrawer, (void *)&struct0, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);
    }
}
