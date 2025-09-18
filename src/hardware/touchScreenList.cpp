#include "touchScreenList.h"

namespace hardware
{
    //  create touchScreen0 object
    Adafruit_ILI9341 screen0 = Adafruit_ILI9341(&spiHandle, touchScreen0_screen_DataCommand, touchScreen0_screen_ChipSelect, touchScreen0_screen_Reset);
    touchScreen touchScreen0 = touchScreen(&screen0, touchScreen0_screen_BackLight, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT);
}