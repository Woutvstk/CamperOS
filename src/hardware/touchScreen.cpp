#include "touchScreen.h"
#include "FunctionalInterrupt.h"

namespace hardware
{

    void touchScreen::init()
    {
        if (screen != nullptr)
        {
            // parameter 0 to comply to Adafruit_SPITFT.begin function definition
            // Actual begin function called is the one from a derived class
            screen->begin(0);
            pinMode(pinScreenBacklight, OUTPUT);
            analogWrite(pinScreenBacklight, 15);
        }

        if (touch != nullptr)
        {
            touch->begin();

            if (touch->IRQ_PIN != 255)
            {
                pinMode(touch->IRQ_PIN, INPUT);
            }
        }
    }

    void touchScreen::setBrightness(uint8_t brightness)
    {
        if (screen != nullptr)
        {
            analogWrite(pinScreenBacklight, brightness);
        }
        else
        {
            Serial.printf(" [touchScreen.setBrightness] - Cannot set brightness: screen == nullptr");
        }
    }

    void touchScreen::touchReadRaw(uint16_t *x, uint16_t *y, uint8_t *z)
    {
        if (touch != nullptr)
        {
            touch->readRaw(x, y, z);
        }
    }

    IRAM_ATTR
    void touchScreen::touchIsr()
    {
        detachInterrupt(digitalPinToInterrupt(touch->IRQ_PIN));
        isrTime = millis();
    }

    void touchScreen::enableTouchIsr(std::function<void(void)> intRoutine)
    {
        pIsrRoutine = intRoutine;
        attachInterrupt(touch->IRQ_PIN, intRoutine, CHANGE);
    }

    bool touchScreen::touchIsrWake()
    {
        return isrTime != 0;
    }

    void touchScreen::handleTouchIsr(uint16_t *NextRunTime)
    {
        if ((millis() - isrTime) < isrIntervalMin)
        {
            *NextRunTime = isrTime + isrIntervalMin;
        }
        else
        {
            isrTime = 0;
            if (touch->IRQ_PIN != 255)
            {

                if (this->pIsrRoutine == nullptr)
                {
                    Serial.println(" [touchScreen.handleTouchIsr] - pIsrRoutine is nullptr");
                }
                else
                {
                    this->enableTouchIsr(this->pIsrRoutine);
                }
            }
        }
    }

    bool touchScreen::hasScreen()
    {
        return (screen != nullptr);
    }

    void touchScreen::setRotation(uint8_t newRotation)
    {
        // keep screen at orientation 0 and rotate canvas
        rotation = newRotation % 4;
    }

    uint16_t touchScreen::getRotatedSizeX()
    {

        switch (rotation % 4)
        {
        case 0:
        case 2:
            return screenSizeX;
        case 1:
        case 3:
            return screenSizeY;
        }
        return 0; // avoid compiler complaints
    }

    uint16_t touchScreen::getRotatedSizeY()
    {

        switch (rotation % 4)
        {
        case 0:
        case 2:
            return screenSizeY;
        case 1:
        case 3:
            return screenSizeX;
        }
        return 0; // avoid compiler complaints
    }

    bool touchScreen::updateCalibration(uint16_t *calibrationPoints)
    {
        Serial.printf("Ymin1: %d", calibrationPoints[1]);
        // calibrationPoints[]: [0]Xmin1, [1]Ymin1, [2]Xmin2, [3]Ymax1, [4]Xmax1, [5]Ymax2, [6]Xmax2, [7]Ymin2
        touchCalibrationRatioX = (float)(2 * getRotatedSizeX() * (100 - 2 * calibrationCrossPositions)) / (calibrationPoints[0] + calibrationPoints[2] - calibrationPoints[4] - calibrationPoints[6]) / 100;
        touchCalibrationRatioY = (float)(2 * getRotatedSizeY() * (100 - 2 * calibrationCrossPositions)) / (calibrationPoints[1] + calibrationPoints[7] - calibrationPoints[3] - calibrationPoints[5]) / 100;

        // Calculate the X and Y offsets
        touchCalibrationOffsetX = (float)((calibrationPoints[0] + calibrationPoints[4]) - getRotatedSizeX() / touchCalibrationRatioX) / 2;
        touchCalibrationOffsetY = (float)((calibrationPoints[1] + calibrationPoints[3]) - getRotatedSizeY() / touchCalibrationRatioY) / 2;
        return true;
    }

    void touchScreen::applyCalibration(uint16_t *touchPos_x, uint16_t *touchPos_y)
    {
        Serial.printf("conversion before: %d, after: %f,  ", *touchPos_y, ((*touchPos_y - touchCalibrationOffsetY) * touchCalibrationRatioY));
        *touchPos_x = (uint16_t)(getRotatedSizeX() - (*touchPos_x - touchCalibrationOffsetX) * touchCalibrationRatioX);
        *touchPos_y = (uint16_t)(getRotatedSizeY() - (*touchPos_y - touchCalibrationOffsetY) * touchCalibrationRatioY);
    }

    void touchScreen::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
    {
        screen->drawRGBBitmap(x, y, bitmap, w, h);
    }

    uint16_t touchScreen::mapUint16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max)
    {
        const int32_t run = in_max - in_min;
        if (run == 0)
        {
            return -1;
        }
        const int32_t rise = out_max - out_min;
        const int32_t delta = x - in_min;
        return (uint16_t)((delta * rise) / run + out_min);
    }

}
