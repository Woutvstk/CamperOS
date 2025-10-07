#pragma once
#include <Arduino.h>
#include <SPI.h>

namespace hardware
{

    class touchInput_Base
    {

    public:
        const uint8_t IRQ_PIN;
        SPIClass *spiHandle = nullptr;

        touchInput_Base(SPIClass *spiHandle, uint8_t IRQ_PIN) : spiHandle(spiHandle), IRQ_PIN(IRQ_PIN) {};

        virtual bool begin() = 0;
        virtual bool touched() = 0;
        virtual void readRaw(uint16_t *x, uint16_t *y, uint8_t *z) = 0;
    };
}