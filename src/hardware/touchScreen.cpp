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

    void touchScreen::touchRead(uint16_t *x, uint16_t *y, uint8_t *z)
    {
        uint16_t rawX, rawY;
        touch->readRaw(&rawX, &rawY, z);
        *x = (rawX - touchCalibrationMinX) * screenSizeY / (touchCalibrationMaxX - touchCalibrationMinX);
        *y = (rawY - touchCalibrationMinY) * screenSizeX / (touchCalibrationMaxY - touchCalibrationMinY);
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

    void touchScreen::drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
    {
        screen->drawRGBBitmap(x, y, bitmap, w, h);
    }
}