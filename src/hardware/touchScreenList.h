#pragma once
#include "hardware/touchScreen.h"
#include "pinDefinitions.h"
#include "globals.h"

// hardware specific libraries
#include <Adafruit_ILI9341.h> // include Adafruit ILI9341 TFT library

namespace hardware
{
    //  create touchScreen0 object
    extern Adafruit_ILI9341 screen0;
    extern touchScreen touchScreen0;
}