#include "elementGraph.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) \
    {                       \
        int16_t t = a;      \
        a = b;              \
        b = t;              \
    }
#endif

namespace graphics
{

    bool elementGraph::draw(Adafruit_SPITFT *screen)
    {
        bool functionSucces = true;

        if (graphLineWidth == 0)
        {
            graphLineWidth = 1;
        }

        if (data != nullptr && pointCount != 0)
        {
            screen->startWrite();
            if (!graphWriteFrame(screen))
            {
                functionSucces = false;
            }
            if (!graphWriteData(screen))
            {
                functionSucces = false;
            }
            screen->endWrite();
            return functionSucces;
        }
        else
        {
            Serial.println("Cannot draw graph: *data == NULL or pointCount == 0");
            return false;
        }
    };

    bool elementGraph::graphWriteFrame(Adafruit_SPITFT *screen)
    {
        bool functionSucces = true;
        // draw axes
        for (uint8_t i = 0; i < axesWidth; i++)
        {
            screen->writeFastVLine(pos_x_px + i, pos_y_px, size_y_px, axesColor);
            screen->writeFastHLine(pos_x_px, pos_y_px + size_y_px - i, size_x_px, axesColor);
        }

        data_pos_x = pos_x_px + axesWidth;
        data_pos_y = pos_y_px;
        data_size_x = size_x_px - axesWidth;
        data_size_y = size_y_px - axesWidth;

        return functionSucces;
    }

    bool elementGraph::graphWriteData(Adafruit_SPITFT *screen)
    {
        bool functionSucces = true;
        uint16_t x1 = 0;
        uint16_t y1 = 0;
        uint16_t x0 = 0;
        uint16_t y0 = 0;

        for (uint8_t i = 0; i < pointCount; i++)
        {
            x1 = data_pos_x + data_size_x * i / pointCount;
            y1 = data_pos_y + data_size_y - data_size_y * data[i] / UINT8_MAX;

            if (i != 0)
            {
                if (!graphWriteDataSectionCollumn(x0, y0, x1, y1, screen))
                {
                    functionSucces = false;
                }
            }

            x0 = x1;
            y0 = y1;
        }

        return functionSucces;
    }

    // based on Bresenham's line algorithm implementation by adafruit, thx adafruit_GFX
    bool elementGraph::graphWriteDataSectionCollumn(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                                    Adafruit_SPITFT *screen)
    {
        bool functionSucces = true;
        int16_t steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep)
        {
            _swap_int16_t(x0, y0);
            _swap_int16_t(x1, y1);
        }

        if (x0 > x1)
        {
            _swap_int16_t(x0, x1);
            _swap_int16_t(y0, y1);
        }

        int16_t dx, dy;
        dx = x1 - x0;
        dy = abs(y1 - y0);

        int16_t err = dx / 2;
        int16_t ystep;

        if (y0 < y1)
        {
            ystep = 1;
        }
        else
        {
            ystep = -1;
        }

        for (; x0 <= x1; x0++)
        {
            if (steep)
            {
                screen->writeFastVLine(y0, data_pos_y, x0 - data_pos_y, graphBackgroundColor);
                screen->writeFastVLine(y0, x0, graphLineWidth, graphLineColor);
                if (graphFill)
                {
                    screen->writeFastVLine(y0, x0 + graphLineWidth, data_pos_y + data_size_y - x0 - graphLineWidth, graphFillColor);
                }
                else
                {
                    screen->writeFastVLine(y0, x0 + graphLineWidth, data_pos_y + data_size_y - x0 - graphLineWidth, graphBackgroundColor);
                }
            }
            else
            {
                screen->writeFastVLine(x0, data_pos_y, y0 - data_pos_y, graphBackgroundColor);
                screen->writeFastVLine(x0, y0, graphLineWidth, graphLineColor);
                if (graphFill)
                {
                    screen->writeFastVLine(x0, y0 + graphLineWidth, data_pos_y + data_size_y - y0 - graphLineWidth, graphFillColor);
                }
                else
                {
                    screen->writeFastVLine(x0, y0 + graphLineWidth, data_pos_y + data_size_y - y0 - graphLineWidth, graphBackgroundColor);
                }
            }
            err -= dy;
            if (err < 0)
            {
                y0 += ystep;
                err += dx;
            }
        }

        return functionSucces;
    };

}