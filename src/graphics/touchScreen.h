#include <Arduino.h>
#include <Adafruit_GFX.h>     // include Adafruit graphics library
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library

#include "pinDefinitions.h"

namespace graphics
{
    
    class touchScreen
    {

    public:
        // initiate screen object using initializer list because Adafruit_ILI9341 does not have default constructor TODO: also define touch input object here
        touchScreen(SPIClass &screenSpi, uint8_t screenDc, uint8_t screenCs, uint8_t screenRst, uint8_t screenBacklight) : screen(&screenSpi, screenDc, screenCs, screenRst)
        {
            pinScreenBacklight = screenBacklight;
        }

        void init();
        void setRotation(uint8_t rotation);
        void setBrightness(uint8_t brightness);
        void drawNumber(uint8_t number);

    private:
        uint8_t pinScreenBacklight;
        Adafruit_ILI9341 screen;
        // declare touchInput object here
    };

}
