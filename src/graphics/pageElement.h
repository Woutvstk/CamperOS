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

        bool touchAble = false;

        // constructor that takes the start position and (rectangular) size in pixels
        pageElement(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px)
            : pos_x_px(p_pos_x_px), pos_y_px(p_pos_y_px), size_x_px(p_size_x_px), size_y_px(p_size_y_px) {};

        //@return true for succesfully drawing element
        virtual bool draw(GFXcanvas16 *screen)
        {
            Serial.println("Now inside element.draw (class definition of draw), this version of .draw shoud never be called");
            return false;
        };
        // return true to claim touch event and add touchEvent to queue
        bool checkHitbox(const uint16_t touchPos_x, const uint16_t touchPos_y, const uint8_t touch_z)
        {
            if ((touchPos_x > pos_x_px) && touchPos_x < (pos_x_px + size_x_px) && touchPos_y > pos_y_px && touchPos_y < (pos_y_px + size_y_px))
            {
                return true;
            }
            return false;
        }

        // return a touchInputEvent when this element handles a touch
        virtual touchInputEvent getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z)
        {
            touchInputEvent dummy;
            return dummy;
        }
    };

}
