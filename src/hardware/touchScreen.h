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
        uint16_t touchCalibrationMinX = 3750;
        uint16_t touchCalibrationMaxX = 220;
        uint16_t touchCalibrationMinY = 3750;
        uint16_t touchCalibrationMaxY = 350;

        // initiate screen object using initializer list because adf_screenType does not have default constructor
        touchScreen(uint8_t screenBacklight, uint16_t screenWidth, uint16_t screenHeight, Adafruit_SPITFT *screen = nullptr, touchInput_Base *touch = nullptr)
            : screen(screen),
              screenWidth(screenWidth),
              screenHeight(screenHeight),
              pinScreenBacklight(screenBacklight),
              touch(touch) {}

        void init();
        void setBrightness(uint8_t brightness);
        void touchRead(uint16_t *x, uint16_t *y, uint8_t *z);

    private:
        uint8_t pinScreenBacklight;
        // declare touchInput object here
    };
}
