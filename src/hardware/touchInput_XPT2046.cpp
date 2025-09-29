#include "touchInput_XPT2046.h"

namespace hardware
{

    bool touchInput_XPT2046::begin()
    {
        return touch.begin(*spiHandle);
    };

    bool touchInput_XPT2046::touched()
    {
        return touch.touched();
    };

}