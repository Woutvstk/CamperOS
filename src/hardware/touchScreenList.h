#pragma once
#include "hardware/touchScreen.h"
#include "pinDefinitions.h"
#include "globals.h"

// include hardware specific libraries here

// for touchScreen0
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library
#include "touchInput_XPT2046.h"

namespace hardware
{
    // declare all touchScreen objects here, keep screen and touch objects invisible

    // declare touchScreen0 object
    extern touchScreen touchScreen0;
}
