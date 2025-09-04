#pragma once
#include "../pageElement.h"

namespace graphics
{

    class elementGraph : public pageElement
    {
    public:
        uint16_t color;
        uint8_t *data;
        uint8_t dataSize;

        elementGraph(uint16_t p_start_x_px, uint16_t p_start_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_color)
            : pageElement(p_start_x_px, p_start_y_px, p_size_x_px, p_size_y_px), color(p_color) {};
        bool draw(Adafruit_SPITFT &screen) const override;
    };

}
