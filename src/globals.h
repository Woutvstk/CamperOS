#pragma once
#include <Arduino.h>
#include "hardware.h"

extern SPIClass spiHandle;

//  create screen0 object
extern hardware::touchScreen<Adafruit_ILI9341> touchScreen0;
