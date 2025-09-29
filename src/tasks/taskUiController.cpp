#include "taskUiController.h"

volatile unsigned long isrTime = 0; // if 0, ISR has not run yet. otherwise: time of last isr

IRAM_ATTR
void touchInputIsr(void)
{
    detachInterrupt(digitalPinToInterrupt(hardware::touchScreen0.touch->IRQ_PIN));
    isrTime = millis();

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
    const uint8_t isrIntervalMin = 100; // time in ms

    // initialize touchscreens
    hardware::touchScreen0.init();
    hardware::touchScreen0.rotation = 3;

    if (hardware::touchScreen0.touch->IRQ_PIN != 255)
    {
        pinMode(hardware::touchScreen0.touch->IRQ_PIN, INPUT);
        attachInterrupt(digitalPinToInterrupt(hardware::touchScreen0.touch->IRQ_PIN), touchInputIsr, CHANGE);
    }

    uint8_t rotaryValue = 70;
    bool rotary_direction = false;
    SdrawerInstruction struct0 = {&graphics::home, &(hardware::touchScreen0)};

    vTaskDelay(100);
    uint8_t startPoint = 0;

    while (true)
    {

        ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(notifyWaitTime)); // wait for UiUpdateRate or notification, portMAX_DELAY for no timeout
        notifyWaitTime = defaultUiControllerNotifyWait;          // change notifyWaitTime to default. Can be reduced during this run if needed

        if (isrTime > 0)
        {
            if (hardware::touchScreen0.touch->touched())
            {
                graphics::environment.Circle0.color = ILI9341_GREEN;
            }
            else
            {
                graphics::environment.Circle0.color = ILI9341_BLUE;
            }

            if ((millis() - isrTime) < isrIntervalMin)
            {
                notifyWaitTime = min<uint16_t>(isrIntervalMin, notifyWaitTime);
            }
            else
            {
                isrTime = 0;
                if (hardware::touchScreen0.touch->IRQ_PIN != 255)
                {
                    attachInterrupt(digitalPinToInterrupt(hardware::touchScreen0.touch->IRQ_PIN), touchInputIsr, CHANGE);
                }
            }
        }

        // draw environment with graphs on it

        struct0.page = &(graphics::environment);
        uint8_t graphPoints[] = {115, 157, 145, 112, 123, 145, 185, 124, 168, 112, 112, 235, 224, 220, 115, 145, 118, 148, 159, 169, 170, 210, 250, 150, 120, 140, 100, 80};
        graphics::environment.Graph0.data = (uint8_t *)&graphPoints[0];
        graphics::environment.Graph0.pointCount = (sizeof(graphPoints) / sizeof(graphPoints[0]));
        graphics::environment.Graph0.graphLineWidth = 3;
        graphics::environment.Graph0.graphFill = true;
        graphics::environment.Graph0.graphLineColor = ILI9341_GREEN;
        graphics::environment.Graph0.graphFillColor = ILI9341_DARKGREEN;

        if (startPoint < 13)
        {
            startPoint++;
        }
        else
        {
            startPoint = 0;
        }

        graphics::environment.Graph1.data = (uint8_t *)&graphPoints[startPoint];
        graphics::environment.Graph1.pointCount = 14;
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
