#pragma once
#include <Arduino.h>
#include <SPI.h>

namespace hardware
{

    class touchInput_Base
    {

    public:
        const uint8_t IRQ_PIN;
        touchInput_Base(uint8_t IRQ_PIN) : IRQ_PIN(IRQ_PIN) {};
        virtual bool begin(SPIClass *spiHandle) = 0;
        virtual bool touched() = 0;
        virtual void read(uint16_t *x, uint16_t *y, uint8_t *z) = 0;
    };

}