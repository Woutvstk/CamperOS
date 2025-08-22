#pragma once

#include <stdio.h>
#include "pageElement.h"
#include <Arduino.h>       //TODO remove
#include "elementList.h" //TODO remove

namespace graphics
{

    // maximum of 255 pages
    enum pageTypesEnum : uint8_t
    {
        INVALID = 0,
        BOOT = 1,
        HOME = 2,
        PAGE1 = 3
    };

    // max of 255 elements on a page
    template <typename pointerType, uint8_t arrayCount>
    class Page
    {
    public:
        Page(pageTypesEnum pageType, const pointerType (*elementArrayPtr)[arrayCount]) : pageType(pageType), elementArrayPtr(elementArrayPtr) {};

        // pageTypesEnum getpageType() { return pageType; };

        // fill screen black and draw page, return the amount of elements drawn
        uint8_t draw(uint8_t *pageDataStart, Adafruit_SPITFT &screen)
        {
            if (pageDataStart == NULL)
            {
                Serial.println("#### ERROR:  pageDataStart is nullpointer  #####");
            }
            else
            {

                if (elementArrayPtr == NULL)
                {
                    Serial.println("###### ERROR: elementArrayPtr is NULL (in page.h)###");
                }
                else
                {
                    screen.fillScreen(0); // fill screen black

                    uint16_t elementDataOffset = 0;
                    for (uint8_t i = 0; i < arrayCount; i++)
                    {
                        (*elementArrayPtr)[i]->draw(screen, pageDataStart + elementDataOffset);
                        elementDataOffset += (*elementArrayPtr)[i]->data_size;
                    }
                }
            }

            return 0;
        };

        // only update changed elements
        // uint8_t update(unsigned char *pageDataStart);

    private:
        pageTypesEnum pageType;
        const pointerType (*elementArrayPtr)[arrayCount];
    };

}
