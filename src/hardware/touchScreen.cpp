#include "touchScreen.h"

namespace hardware
{

    void touchScreen::init()
    {
        pinMode(pinScreenBacklight, OUTPUT);
        analogWrite(pinScreenBacklight, 15);
        // parameter 0 to comply to Adafruit_SPITFT.begin function definition
        // Actual begin function called is the one from a derived class
        screen->begin(0);
    }

    void touchScreen::setBrightness(uint8_t brightness)
    {
        analogWrite(pinScreenBacklight, brightness);
    }

}
