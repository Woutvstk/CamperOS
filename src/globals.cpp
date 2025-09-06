#include "globals.h"

SPIClass spiHandle = SPIClass(FSPI);

//  create screen0 object
hardware::touchScreen<Adafruit_ILI9341> touchScreen0(spiHandle, touchScreen0_screen_DataCommand, touchScreen0_screen_ChipSelect, touchScreen0_screen_Reset, touchScreen0_screen_BackLight);