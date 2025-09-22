#pragma once
#include "hardware/touchScreen.h"
#include "pinDefinitions.h"
#include "globals.h"

// hardware specific libraries
// for touchScreen0
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library
#include "touchInput_XPT2046.h"

namespace hardware
{
    //  declare touchScreen0 object
    extern Adafruit_ILI9341 screen0;
    extern touchInput_XPT2046 touch0;
    extern touchScreen touchScreen0;
}