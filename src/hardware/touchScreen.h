#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h> // include Adafruit graphics library
#include "Adafruit_SPITFT.h"

namespace hardware
{
    class touchScreen
    {

    public:
        const uint16_t screenWidth;
        const uint16_t screenHeight;
        Adafruit_SPITFT *screen;
        // initiate screen object using initializer list because adf_screenType does not have default constructor TODO: also define touch input object here
        touchScreen(Adafruit_SPITFT *screen, uint8_t screenBacklight, uint16_t screenWidth, uint16_t screenHeight) : screen(screen),
                                                                                                                     screenWidth(screenWidth), screenHeight(screenHeight)
        {
            pinScreenBacklight = screenBacklight;
        }

        void init();
        void setBrightness(uint8_t brightness);

    private:
        uint8_t pinScreenBacklight;
        // declare touchInput object here
    };
}
