#pragma once
#include <Arduino.h>
#include "hardware/touchScreen.h"

extern SPIClass spiHandle;

namespace hardware
{
    //  create screen0 object
    extern Adafruit_ILI9341 screen0;
    extern touchScreen touchScreen0;
}