#pragma once
#include <stdio.h>
#include <Arduino.h> //TODO remove
#include "hardware.h"

namespace graphics
{

    class pageElement
    {

    public:
        const uint16_t start_x_px;
        const uint16_t start_y_px;
        const uint16_t size_x_px;
        const uint16_t size_y_px;
        const uint16_t data_size;

        // constructor that takes the start position, (rectangular) size in pixels and data size in number of bytes
        pageElement(uint16_t p_start_x_px, uint16_t p_start_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_data_size)
            : start_x_px(p_start_x_px), start_y_px(p_start_y_px), size_x_px(p_size_x_px), size_y_px(p_size_y_px), data_size(p_data_size) {};

        //@param dataStart pointer to start of data for this element
        //@return true for succesfully drawing element
        virtual bool draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const
        {
            Serial.println("Now inside element.draw (class definition of draw)");
            return false;
        };
        uint16_t getDataSize() { return data_size; };
    };

}
