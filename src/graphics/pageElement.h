#pragma once
#include <stdio.h>
#include "hardware/touchScreen.h"

namespace graphics
{

    class pageElement
    {

    public:
        uint16_t pos_x_px;
        uint16_t pos_y_px;
        uint16_t size_x_px;
        uint16_t size_y_px;

        // constructor that takes the start position and (rectangular) size in pixels
        pageElement(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px)
            : pos_x_px(p_pos_x_px), pos_y_px(p_pos_y_px), size_x_px(p_size_x_px), size_y_px(p_size_y_px) {};

        //@return true for succesfully drawing element
        virtual bool draw(Adafruit_SPITFT *screen) const
        {
            Serial.println("Now inside element.draw (class definition of draw), this version of .draw shoud never be called");
            return false;
        };
    };

}
