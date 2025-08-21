#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>     // include Adafruit graphics library
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library

#include "pinDefinitions.h"

namespace hardware
{

    template <typename adf_screenType>
    class touchScreen
    {

    public:
        adf_screenType screen;
        // initiate screen object using initializer list because adf_screenType does not have default constructor TODO: also define touch input object here
        touchScreen(SPIClass &screenSpi, uint8_t screenDc, uint8_t screenCs, uint8_t screenRst, uint8_t screenBacklight) : screen(&screenSpi, screenDc, screenCs, screenRst)
        {
            pinScreenBacklight = screenBacklight;
        }

        void init()
        {
            screen.begin();
            pinMode(pinScreenBacklight, OUTPUT);
        }
        void setBrightness(uint8_t brightness)
        {
            analogWrite(pinScreenBacklight, brightness);
        }

        void drawNumber(uint8_t number) // TODO remove, use adafruit gfx directly with pages
        {
            screen.fillScreen(ILI9341_BLACK);
            screen.setCursor(10, 10);
            screen.setTextColor(ILI9341_WHITE);
            screen.setTextSize(15);
            screen.print(number);
        }

    private:
        uint8_t pinScreenBacklight;
        // declare touchInput object here
    };

}
