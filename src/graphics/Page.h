#pragma once

#include <stdio.h>
#include "pageElement.h"
#include <Arduino.h>       //TODO remove
#include "elements_list.h" //TODO remove

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
        uint8_t draw(uint8_t *pageDataStart)
        {
            Serial.printf("Now drawing pageType Nr: %d\n", pageType);

            if (pageDataStart == NULL)
            {
                Serial.println("#### ERROR:  pageDataStart is nullpointer  #####");
            }
            else
            {

                Serial.printf("Content of first byte of pageDataStart: %d\n", *pageDataStart);

                if (elementArrayPtr == NULL)
                {
                    Serial.println("###### ERROR: elementArrayPtr is NULL (in page.h)###");
                }
                else
                {
                    Serial.printf("now calling first element draw, pointer to elements is: %p\n", elementArrayPtr);
                    for (uint8_t i = 0; i < arrayCount; i++)
                    {
                        (*elementArrayPtr)[i]->draw(pageDataStart);
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
