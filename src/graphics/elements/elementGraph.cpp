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

    bool elementGraph::draw(GFXcanvas16 *screen)
    {
        bool functionSucces = true;

        int_pos_x_px = pos_x_px;
        int_pos_y_px = pos_y_px;
        int_size_x_px = size_x_px;
        int_size_y_px = size_y_px;

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

    bool elementGraph::graphWriteFrame(GFXcanvas16 *screen)
    {
        bool functionSucces = true;
        // write labels and update drawing window for next part of element
        // placement of labels is aimed for 3 character labels (e.g. 879, -25, ...)
        const uint8_t characterWidth = 6;
        const uint8_t characterHeight = 8;

        if (axesWidth < 1)
        {
            axesWidth = 1;
        }
        // write marking for labels
        for (uint8_t i = 0; i < axesWidth; i++)
        {
            screen->writeFastHLine(int_pos_x_px + 3 * characterWidth, int_pos_y_px + i, characterWidth, axesColor);
            screen->writeFastHLine(int_pos_x_px + 3 * characterWidth, int_pos_y_px + int_size_y_px - 4 * characterWidth - i, characterWidth, axesColor);
            screen->writeFastVLine(int_pos_x_px + 4 * characterWidth + i, int_pos_y_px + int_size_y_px - 4 * characterWidth, characterWidth, axesColor);
            screen->writeFastVLine(int_pos_x_px + int_size_x_px - i, int_pos_y_px + int_size_y_px - 4 * characterWidth, characterWidth, axesColor);
        }

        // end open write because print has its own start/end write
        screen->endWrite();
        screen->setTextColor(axesLabelColor);
        screen->setTextSize(axesLabelSize);
        screen->setCursor(int_pos_x_px + 1, int_pos_y_px + axesWidth);
        screen->print(axesLabelMaxY);

        screen->setCursor(int_pos_x_px + 1, int_pos_y_px + int_size_y_px - 4 * characterWidth - axesWidth - characterHeight);
        screen->print(axesLabelMinY);

        screen->setCursor(int_pos_x_px + 4 * characterWidth + axesWidth + 1, int_pos_y_px + int_size_y_px - 4 * characterWidth + 3);
        screen->print(axesLabelMinX);

        screen->setCursor(int_pos_x_px + int_size_x_px - axesWidth - 1 - 3 * characterWidth, int_pos_y_px + int_size_y_px - 4 * characterWidth + 3);
        screen->print(axesLabelMaxX);
        screen->startWrite();

        int_pos_x_px = int_pos_x_px + 4 * characterWidth;
        // int_pos_y_px = int_pos_y_px + 0;
        int_size_x_px = int_size_x_px - 4 * characterWidth;
        int_size_y_px = int_size_y_px - 4 * characterWidth;

        // write axes/Frame and update drawing window for next part of element
        for (uint8_t i = 0; i < axesWidth; i++)
        {
            screen->writeFastVLine(int_pos_x_px + i, int_pos_y_px, int_size_y_px, axesColor);
            screen->writeFastHLine(int_pos_x_px, int_pos_y_px + int_size_y_px - i, int_size_x_px + 1, axesColor);
            if (frameAllSides)
            {
                screen->writeFastVLine(int_pos_x_px + int_size_x_px - i, int_pos_y_px, int_size_y_px, axesColor);
                screen->writeFastHLine(int_pos_x_px, int_pos_y_px + i, int_size_x_px, axesColor);
            }
        }
        if (frameAllSides)
        {
            int_pos_x_px = int_pos_x_px + axesWidth;
            int_pos_y_px = int_pos_y_px + axesWidth;
            int_size_x_px = int_size_x_px - 2 * axesWidth;
            int_size_y_px = int_size_y_px - 2 * axesWidth + 1;
        }
        else
        {
            int_pos_x_px = int_pos_x_px + axesWidth;
            int_pos_y_px = int_pos_y_px;
            int_size_x_px = int_size_x_px - axesWidth;
            int_size_y_px = int_size_y_px - axesWidth + 1;
        }

        return functionSucces;
    }

    bool elementGraph::graphWriteData(GFXcanvas16 *screen)
    {
        bool functionSucces = true;
        uint16_t x1 = 0;
        uint16_t y1 = 0;
        uint16_t x0 = 0;
        uint16_t y0 = 0;

        // write curve collumns as last part of element
        for (uint8_t i = 0; i < pointCount; i++)
        {
            x1 = int_pos_x_px + int_size_x_px * i / (pointCount - 1);
            y1 = int_pos_y_px + int_size_y_px - int_size_y_px * data[i] / UINT8_MAX;

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

    // based on Bresenham's line algorithm implementation by Adafruit, thx Adafruit_GFX
    bool elementGraph::graphWriteDataSectionCollumn(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                                                    GFXcanvas16 *screen)
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
                screen->writeFastVLine(y0, int_pos_y_px, x0 - int_pos_y_px, graphBackgroundColor);
                screen->writeFastVLine(y0, x0, graphLineWidth, graphLineColor);
                if (graphFill)
                {
                    screen->writeFastVLine(y0, x0 + graphLineWidth, int_pos_y_px + int_size_y_px - x0 - graphLineWidth, graphFillColor);
                }
                else
                {
                    screen->writeFastVLine(y0, x0 + graphLineWidth, int_pos_y_px + int_size_y_px - x0 - graphLineWidth, graphBackgroundColor);
                }
            }
            else
            {
                screen->writeFastVLine(x0, int_pos_y_px, y0 - int_pos_y_px, graphBackgroundColor);
                screen->writeFastVLine(x0, y0, graphLineWidth, graphLineColor);
                if (graphFill)
                {
                    screen->writeFastVLine(x0, y0 + graphLineWidth, int_pos_y_px + int_size_y_px - y0 - graphLineWidth, graphFillColor);
                }
                else
                {
                    screen->writeFastVLine(x0, y0 + graphLineWidth, int_pos_y_px + int_size_y_px - y0 - graphLineWidth, graphBackgroundColor);
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