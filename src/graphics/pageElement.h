#pragma once
#include <stdio.h>
#include "hardware/touchScreen.h"
#include "Adafruit_GFX.h"

namespace graphics
{

    class pageElement
    {

    public:
        // absolute position and size
        // calculated from relative position and size or manually set
        uint16_t pos_x_px;
        uint16_t pos_y_px;
        uint16_t size_x_px;
        uint16_t size_y_px;

        // relative position and size
        // set manually
        float pos_x_rel;
        float pos_y_rel;
        float size_x_rel;
        float size_y_rel;

        bool visible = true;
        bool touchAble = false;

        // constructor that takes the relative start position and (rectangular) size
        pageElement(float pos_x_rel, float pos_y_rel, float size_x_rel, float size_y_rel)
            : pos_x_rel(pos_x_rel), pos_y_rel(pos_y_rel), size_x_rel(size_x_rel), size_y_rel(size_y_rel)
        {
            pos_x_px = pos_x_rel;
            pos_y_px = pos_y_rel;
            size_x_px = size_x_rel;
            size_y_px = size_y_rel;
        };

        bool draw(GFXcanvas16 *screen)
        {
            pos_x_px = screen->width() * pos_x_rel;
            size_x_px = screen->width() * size_x_rel;
            pos_y_px = screen->height() * pos_y_rel;
            size_y_px = screen->height() * size_y_rel;
            return drawAbsolute(screen);
        }

        // return true for succesfully drawing element
        virtual bool drawAbsolute(GFXcanvas16 *screen) = 0;
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
