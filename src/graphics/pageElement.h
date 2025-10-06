#pragma once
#include <stdio.h>
#include "hardware/touchScreen.h"
#include "Adafruit_GFX.h"

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
        virtual bool draw(GFXcanvas16 *screen)
        {
            Serial.println("Now inside element.draw (class definition of draw), this version of .draw shoud never be called");
            return false;
        };

    protected:
        static void extractRGBBitmap(GFXcanvas16 *original, uint16_t x, uint16_t y, GFXcanvas16 *extract)
        {
            for (uint16_t i = 0; i < extract->height(); i++)
            {
                for (int16_t j = 0; j < extract->width(); j++)
                {
                    extract->drawPixel(j, i, original->getPixel(x + j, y + i));
                }
            }
        }
    };

}
