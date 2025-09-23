#include "touchInput_Base.h"
#include "XPT2046_Touchscreen.h"

namespace hardware
{

    class touchInput_XPT2046 : public touchInput_Base
    {

    public:
        touchInput_XPT2046(SPIClass *spiHandle, uint8_t CS, uint8_t IRQ_PIN = 255) : touchInput_Base(spiHandle, IRQ_PIN), touch(CS) {};
        bool begin();
        bool touched();
        void read(uint16_t *x, uint16_t *y, uint8_t *z);

    private:
        XPT2046_Touchscreen touch;
    };

}