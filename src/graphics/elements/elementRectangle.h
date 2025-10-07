#pragma once
#include "../pageElement.h"

namespace graphics
{

    class elementRectangle : public pageElement
    {
    public:
        uint16_t color;

        elementRectangle(uint16_t p_pos_x_px, uint16_t p_pos_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px, uint16_t p_color)
            : pageElement(p_pos_x_px, p_pos_y_px, p_size_x_px, p_size_y_px), color(p_color) {};
        bool draw(GFXcanvas16 *screen) override;
    };
}
