#include "touchInput_XPT2046.h"

namespace hardware
{

    bool touchInput_XPT2046::begin(SPIClass *spiHandle)
    {
        return touch.begin(*spiHandle);
    };

    bool touchInput_XPT2046::touched()
    {
        return touch.touched();
    };

    void touchInput_XPT2046::read(uint16_t *x, uint16_t *y, uint8_t *z) {

    };

}