#pragma once
#include <stdio.h>
#include "pageElement.h"
#include "globals.h"

namespace graphics
{

    // max of 255 elements on a page
    class Page
    {
    public:
        Page(pageElement **pageElements, uint8_t elementCount) : pageElements(pageElements), elementCount(elementCount) {};

        // fill screen black and draw page, return the amount of elements drawn
        uint8_t draw(GFXcanvas16 *screen)
        {

            if (pageElements == NULL)
            {
                Serial.println(" [Page.draw] - ERROR: elementArrayPtr is NULL");
            }
            else
            {
                screen->fillScreen(0); // fill screen black

                uint16_t elementDataOffset = 0;
                for (uint8_t i = 0; i < elementCount; i++)
                {
                    pageElements[i]->draw(screen);
                }
            }

            return 0;
        };

    private:
        pageElement **pageElements;
        uint8_t elementCount;
    };

}
