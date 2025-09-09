#include "elementGraph.h"

namespace graphics
{

    bool elementGraph::draw(Adafruit_SPITFT *screen)
    {

        if (graphLineWidth == 0)
        {
            graphLineWidth = 1;
        }

        if (data != nullptr && pointCount != 0)
        {
            uint16_t pointX = 0;
            uint16_t pointY = 0;
            uint16_t lastX = 0;
            uint16_t lastY = 0;

            uint16_t deltaCenterX = 0;
            uint16_t deltaCenterY = 0;
            uint16_t centerLength = 0;
            int16_t deltaLineX = 0;
            int16_t deltaLineY = 0;

            screen->drawFastVLine(pos_x_px, pos_y_px, size_y_px, axesColor);
            screen->drawFastHLine(pos_x_px, pos_y_px + size_y_px, size_x_px, axesColor);

            for (uint8_t i = 0; i < pointCount; i++)
            {
                pointX = pos_x_px + size_x_px * i / pointCount;
                pointY = pos_y_px + size_y_px - size_y_px * data[i] / UINT8_MAX;

                deltaCenterX = pointX - lastX;
                deltaCenterY = pointY - lastY;
                centerLength = sqrt(deltaCenterX * deltaCenterX + deltaCenterY * deltaCenterY);

                if (i != 0)
                {
                    for (int8_t offset = -((graphLineWidth - 1) / 2); offset <= (graphLineWidth - 1) / 2; offset++)
                    {

                        deltaLineX = deltaCenterY * offset / centerLength;
                        deltaLineY = deltaCenterX * offset / centerLength;

                        screen->drawLine(lastX + deltaLineX, lastY + deltaLineY, pointX + deltaLineX, pointY + deltaLineY, graphLineColor);
                    }
                }

                lastX = pointX;
                lastY = pointY;
            }

            return true;
        }
        else
        {
            Serial.println("Cannot draw graph: *data == NULL or pointCount == 0");
            return false;
        }
    };
}
