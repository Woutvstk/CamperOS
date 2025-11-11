#include "elementGraphSimple.h"

namespace graphics
{

    bool elementGraphSimple::drawAbsolute(GFXcanvas16 *screen)
    {

        if (data != nullptr && pointCount != 0)
        {
            uint16_t pointX = 0;
            uint16_t pointY = 0;
            uint16_t lastX = 0;
            uint16_t lastY = 0;

            screen->drawFastVLine(pos_x_px, pos_y_px, size_y_px, color);
            screen->drawFastHLine(pos_x_px, pos_y_px + size_y_px, size_x_px, color);

            for (uint8_t i = 0; i < pointCount; i++)
            {
                pointX = pos_x_px + size_x_px * i / pointCount;
                pointY = pos_y_px + size_y_px - size_y_px * data[i] / UINT8_MAX;

                if (i != 0)
                {
                    screen->drawLine(lastX, lastY, pointX, pointY, color);
                }

                lastX = pointX;
                lastY = pointY;
            }

            return true;
        }
        else
        {
            Serial.println("Cannot draw graphSimple: *data == NULL or pointCount == 0");
            return false;
        }
    };
}
