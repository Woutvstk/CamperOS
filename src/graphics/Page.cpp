#include "Page.h"
#include "pageElement.h"
#include <Arduino.h>

namespace graphics
{

    Page::Page(pageElement **pageElements, uint8_t elementCount) : pageElements(pageElements), elementCount(elementCount) {}

    uint8_t Page::draw(GFXcanvas16 *screen)
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
                if (pageElements[i])
                {
                    pageElements[i]->draw(screen);
                }
            }
        }

        return 0;
    }

    touchInputEvent Page::getInputEvent(const uint16_t touchPos_x, const uint16_t touchPos_y, const uint8_t touch_z)
    {
        touchInputEvent empty;
        if (pageElements == NULL)
        {
            Serial.println(" [Page.getInputEvent] - ERROR: elementArrayPtr is NULL");
            return empty;
        }

        for (int i = elementCount - 1; i >= 0; i--)
        {
            if (pageElements[i] && pageElements[i]->touchAble && pageElements[i]->checkHitbox(touchPos_x, touchPos_y, touch_z))
            {
                return pageElements[i]->getTouchInputEvent(touchPos_x, touchPos_y, touch_z);
            }
        }

        return empty;
    }

} // namespace graphics
