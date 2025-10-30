#pragma once
#include <stdio.h>
#include <Adafruit_GFX.h>
#include "globals.h"

namespace graphics
{

    class pageElement; // forward declaration to avoid circular include with hardware/touchScreen.h

    // forward declare touchInputEvent so Page can return it without including touchScreen.h
    struct touchInputEvent;

    // max of 255 elements on a page
    class Page
    {
    public:
        // Construct Page with an array of pageElement* and its element count
        Page(pageElement **pageElements, uint8_t elementCount);

        // fill screen black and draw page, return the amount of elements drawn
        uint8_t draw(GFXcanvas16 *screen);

        // process a touch input event and return the resulting touchInputEvent
        touchInputEvent getInputEvent(const uint16_t touchPos_x, const uint16_t touchPos_y, const uint8_t touch_z);

    private:
        pageElement **pageElements;
        uint8_t elementCount;
    };

}
