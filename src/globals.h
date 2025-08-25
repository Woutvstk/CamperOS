#pragma once
#include <Arduino.h>
#include "hardware/touchScreen.h"







extern SPIClass spiHandle;

//  create screen0 object
extern hardware::touchScreen<Adafruit_ILI9341> touchScreen0;

// pageTypes for screen
// maximum of 255 pages
enum pageTypesEnum : uint8_t
{
    INVALID = 0,
    BOOT = 1,
    HOME = 2,
    PAGE1 = 3
};
