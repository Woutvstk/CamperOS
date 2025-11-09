#include "taskUiController.h"

using namespace graphics;
using namespace hardware;

// forward declarations
void initializePages();

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
    SdrawerInstruction drawerInstruction = {&home, &(touchScreen0)};

    vTaskDelay(100);
    uint8_t startPoint = 0;

    uint16_t touchPos_x = 0;
    uint16_t touchPos_y = 0;
    uint8_t touchPos_z = 0;

    uint8_t calibrationStep = 0;

    initializePages();

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
                if (touchScreen0.currentPage != &calibration)
                {
                    touchScreen0.applyCalibration(&touchPos_x, &touchPos_y);
                    Serial.printf("calibrated position: x: %d, y: %d\n", touchPos_x, touchPos_y);
                    touchInputEvent event0 = touchScreen0.currentPage->getInputEvent(touchPos_x, touchPos_y, touchPos_z);

                    if (event0.sourceElement != nullptr)
                    {
                        if (touchScreen0.currentPage == &environment)
                        {
                            Serial.println("Page is environment");
                            if (event0.sourceElement == &environment.Circle0)
                            {
                                printf("touched circle with value: %d\n", event0.data.unsignedNumber);
                                drawerInstruction.page = &calibration;
                            }
                            else
                            {
                                printf("touched other with value: %d\n", event0.data.unsignedNumber);
                            }
                        }
                        else if (touchScreen0.currentPage == &home)
                        {
                            if (event0.sourceElement == &home.Rectangle0)
                            {
                                drawerInstruction.page = &calibration;
                            }
                            else if (event0.sourceElement == &home.Background)
                            {
                                home.Circle0.pos_x_px = touchPos_x - home.Circle0.size_x_px / 2;
                                home.Circle0.pos_y_px = touchPos_y - home.Circle0.size_y_px / 2;
                            }
                        }
                    }
                    else
                    {
                        Serial.println("event0.sourceElement is nullptr");
                    }
                    // Serial.printf("X: %d, Y: %d, Z: %d\n", touchPos_x, touchPos_y, touchPos_z);
                }
                else // touched calibration page
                {

                    switch (calibrationStep % 4)
                    {
                        static uint16_t calibrationPoints[8]; // Xmin1, Ymin1, Xmin2, Ymax1, Xmax1, Ymax2, Xmax2, Ymin2
                    case 0:

                        calibrationPoints[0] = touchPos_x;
                        calibrationPoints[1] = touchPos_y;
                        calibration.Cross.pos_x_px = touchScreen0.getRotatedSizeX() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_x_px / 2;
                        calibration.Cross.pos_y_px = touchScreen0.getRotatedSizeY() * (100 - touchScreen0.calibrationCrossPositions) / 100 - calibration.Cross.size_y_px / 2;
                        break;

                    case 1:
                        calibrationPoints[2] = touchPos_x;
                        calibrationPoints[3] = touchPos_y;
                        calibration.Cross.pos_x_px = touchScreen0.getRotatedSizeX() * (100 - touchScreen0.calibrationCrossPositions) / 100 - calibration.Cross.size_x_px / 2;
                        calibration.Cross.pos_y_px = touchScreen0.getRotatedSizeY() * (100 - touchScreen0.calibrationCrossPositions) / 100 - calibration.Cross.size_y_px / 2;
                        break;

                    case 2:
                        calibrationPoints[4] = touchPos_x;
                        calibrationPoints[5] = touchPos_y;
                        calibration.Cross.pos_x_px = touchScreen0.getRotatedSizeX() * (100 - touchScreen0.calibrationCrossPositions) / 100 - calibration.Cross.size_x_px / 2;
                        calibration.Cross.pos_y_px = touchScreen0.getRotatedSizeY() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_y_px / 2;
                        break;

                    case 3:
                        calibrationPoints[6] = touchPos_x;
                        calibrationPoints[7] = touchPos_y;

                        if (touchScreen0.updateCalibration(calibrationPoints))
                        {
                            delay(50);
                            printf("Updating calibration succesfull. Xratio: %f, Xoffset: %d, Yratio: %f, Yoffset: %d\n", touchScreen0.touchCalibrationRatioX, touchScreen0.touchCalibrationOffsetX, touchScreen0.touchCalibrationRatioY, touchScreen0.touchCalibrationOffsetY);
                            delay(50);
                        }
                        calibration.Cross.pos_x_px = touchScreen0.getRotatedSizeX() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_x_px / 2;
                        calibration.Cross.pos_y_px = touchScreen0.getRotatedSizeY() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_y_px / 2;
                        drawerInstruction.page = &home;
                        break;
                    }
                    calibrationStep++;
                    delay(200); // extra debounce
                }
            }
            else
            {
            }
            touchScreen0.handleTouchIsr(&nextRunTime);

            notifyWaitTime = nextRunTime - millis();
        }

        uint8_t graphPoints[] = {115, 157, 145, 112, 123, 145, 185, 124, 168, 112, 112, 235, 224, 220, 115, 145, 118, 148, 159, 169, 170, 210, 250, 150, 120, 140, 100, 80};
        environment.Graph0.data = (uint8_t *)&graphPoints[0];
        environment.Graph0.pointCount = (sizeof(graphPoints) / sizeof(graphPoints[0]));

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

        xQueueSend(QtaskUIController2taskDrawer, (void *)&drawerInstruction, 0);
        xTaskNotifyGive(xtaskUiDrawerHandle);
    }
}

void initializePages()
{
    // environment page
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
    environment.Cross0.width = 2;

    environment.Graph1.graphFill = false;
    environment.Graph1.graphLineColor = ILI9341_RED;
    environment.Graph1.axesLabelMaxX = 10;
    environment.Graph1.axesLabelMinX = -10;
    environment.Graph1.axesLabelMaxY = 999;
    environment.Graph1.axesLabelMinY = 0;
    environment.Graph1.axesLabelColor = ILI9341_GREEN;
    environment.Graph1.frameAllSides = true;
    environment.Graph1.axesWidth = 0;

    // calibration page
    calibration.Cross.pos_x_px = touchScreen0.getRotatedSizeX() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_x_px / 2;
    calibration.Cross.pos_y_px = touchScreen0.getRotatedSizeY() * touchScreen0.calibrationCrossPositions / 100 - calibration.Cross.size_y_px / 2;
    Serial.printf("initialized calib cross at x: %d, y: %d\n", calibration.Cross.pos_x_px, calibration.Cross.pos_y_px);
    calibration.Cross.width = 2;

    // home page
    home.Rectangle0.touchAble = true;
    home.Background.touchAble = true;
}