#include "touchScreen.h"

namespace graphics
{

    void touchScreen::init()
    {
        screen.begin();
        pinMode(pinScreenBacklight, OUTPUT);
    }

    void touchScreen::setRotation(uint8_t rotation)
    {
        screen.setRotation(rotation);
    }

    void touchScreen::setBrightness(uint8_t brightness)
    {
        analogWrite(pinScreenBacklight, brightness);
    }

    void touchScreen::drawNumber(uint8_t number)
    {
        screen.fillScreen(ILI9341_BLACK);
        screen.setCursor(10, 10);
        screen.setTextColor(ILI9341_WHITE);
        screen.setTextSize(15);
        screen.print(number);
    }

}


