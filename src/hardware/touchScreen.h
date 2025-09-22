#pragma once
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_SPITFT.h"          //adafruit screen base
#include "hardware/touchInput_Base.h" //touchInput base

namespace hardware
{
    class touchScreen
    {

    public:
        const uint16_t screenWidth;
        const uint16_t screenHeight;
        uint8_t rotation = 0;
        Adafruit_SPITFT *screen;
        touchInput_Base *touch;
        SPIClass *touchSpiHandle = nullptr;
        // initiate screen object using initializer list because adf_screenType does not have default constructor TODO: also define touch input object here
        touchScreen(Adafruit_SPITFT *screen, uint8_t screenBacklight, uint16_t screenWidth, uint16_t screenHeight, touchInput_Base *touch, SPIClass *touchSpiHandle)
            : screen(screen),
              screenWidth(screenWidth),
              screenHeight(screenHeight),
              pinScreenBacklight(screenBacklight),
              touch(touch),
              touchSpiHandle(touchSpiHandle) {}

        void init();
        void setBrightness(uint8_t brightness);

    private:
        uint8_t pinScreenBacklight;
        // declare touchInput object here
    };
}
