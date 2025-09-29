#pragma once
#include <Arduino.h>
#include <SPI.h>

#define UINT12_MAX 4095
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
    };
}