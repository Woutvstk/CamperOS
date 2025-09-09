#pragma once
#include "../pageElement.h"

namespace graphics
{
    class elementGraph : public pageElement
    {
    public:
        uint16_t axesColor;
        uint16_t graphLineColor;
        uint16_t graphFillColor;
        uint8_t graphLineWidth = 1;
        bool graphFill = false;

        uint8_t *data = NULL;
        uint8_t pointCount = 0;

        elementGraph(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_color)
            : pageElement(p_pos_x_px, p_pos_y_px, p_size_x_px, p_size_y_px), axesColor(p_color), graphLineColor(p_color), graphFillColor(p_color) {};
        bool draw(Adafruit_SPITFT *screen) override;
    };
}
