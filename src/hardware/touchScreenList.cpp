#include "touchScreenList.h"

// add macro's for needed touchScreen objects here

//  touchScreen0 pin definitions
#define touchScreen0_screen_ChipSelect 10
#define touchScreen0_screen_DataCommand 5
#define touchScreen0_screen_BackLight 6
#define touchScreen0_screen_Reset 4
#define touchScreen0_touch_ChipSelect 9
#define touchScreen0_touch_IrqPin 46

namespace hardware
{
    // define screen, touch and touchScreen objects here

    //  define touchScreen0 object
    Adafruit_ILI9341 screen0 = Adafruit_ILI9341(&spiHandle, touchScreen0_screen_DataCommand, touchScreen0_screen_ChipSelect, touchScreen0_screen_Reset);
    touchInput_XPT2046 touch0 = touchInput_XPT2046(&spiHandle, touchScreen0_touch_ChipSelect, touchScreen0_touch_IrqPin);
    touchScreen touchScreen0 = touchScreen(touchScreen0_screen_BackLight, ILI9341_TFTWIDTH, ILI9341_TFTHEIGHT, &screen0, &touch0);
}
