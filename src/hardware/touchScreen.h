#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>     // include Adafruit graphics library
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library

#include "pinDefinitions.h"

namespace hardware
{

    class touchScreen
    {

    public:
        Adafruit_SPITFT *screen;
        // initiate screen object using initializer list because adf_screenType does not have default constructor TODO: also define touch input object here
        touchScreen(Adafruit_SPITFT *screen, uint8_t screenBacklight) : screen(screen)
        {
            pinScreenBacklight = screenBacklight;
        }

        void init()
        {
            pinMode(pinScreenBacklight, OUTPUT);
            screen->begin(0);
        }

        void setBrightness(uint8_t brightness)
        {
            analogWrite(pinScreenBacklight, brightness);
        }

    private:
        uint8_t pinScreenBacklight;
        // declare touchInput object here
    };

}
