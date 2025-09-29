#include "touchScreen.h"

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
        *x = (rawX - touchCalibrationMinX) * screenHeight / (touchCalibrationMaxX - touchCalibrationMinX);
        *y = (rawY - touchCalibrationMinY) * screenWidth / (touchCalibrationMaxY - touchCalibrationMinY);
    }

}
