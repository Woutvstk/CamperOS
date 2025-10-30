#pragma once
#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_SPITFT.h"          //adafruit screen base
#include "hardware/touchInput_Base.h" //touchInput base
#include "../graphics/Page.h"

namespace hardware
{

    class touchScreen
    {

    public:
        const uint16_t screenSizeX;
        const uint16_t screenSizeY;
        uint8_t rotation = 0;

        touchInput_Base *touch;
        std::function<void(void)> pIsrRoutine = NULL;
        volatile unsigned long isrTime = 0; // if 0, ISR has not run yet. otherwise: time of last isr
        const uint8_t isrIntervalMin = 100; // time in ms
        uint16_t touchCalibrationMinX = 3750;
        uint16_t touchCalibrationMaxX = 220;
        uint16_t touchCalibrationMinY = 3750;
        uint16_t touchCalibrationMaxY = 350;

        graphics::Page *currentPage = nullptr;

        // initiate screen object using initializer list because adf_screenType does not have default constructor
        touchScreen(uint8_t screenBacklight, uint16_t screenSizeX, uint16_t screenSizeY, Adafruit_SPITFT *screen = nullptr, touchInput_Base *touch = nullptr)
            : screen(screen),
              screenSizeX(screenSizeX),
              screenSizeY(screenSizeY),
              pinScreenBacklight(screenBacklight),
              touch(touch) {}

        void init();
        void setBrightness(uint8_t brightness);
        void touchRead(uint16_t *x, uint16_t *y, uint8_t *z);
        void enableTouchIsr(std::function<void(void)> intRoutine);
        void touchIsr();
        bool touchIsrWake();
        void handleTouchIsr(uint16_t *maxNextRunTime);
        bool hasScreen();
        void setRotation(uint8_t newRotation);
        void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
        void applyCalibration(uint16_t *touchPos_x, uint16_t *touchPos_y);

    private:
        Adafruit_SPITFT *screen;
        uint8_t pinScreenBacklight;
        // move touchInput object here
        uint16_t mapUint16(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);
    };
}

namespace graphics
{
    /*
    touchInputEvent
    */
    // union of size 32-bits
    union touchInputEventData
    {
        uint32_t unsignedNumber;
        int32_t signedNumber;
        float floatingPointNumber;
    };

    struct touchInputEvent
    {
        graphics::pageElement *sourceElement = NULL;
        touchInputEventData data;
    };

}