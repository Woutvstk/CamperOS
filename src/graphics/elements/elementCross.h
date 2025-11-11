#pragma once
#include "../pageElement.h"

namespace graphics
{

    class elementCross : public pageElement
    {
    public:
        uint16_t color;
        uint8_t width = 1;

        elementCross(float pos_x_rel, float pos_y_rel, float size_x_rel, float size_y_rel, uint16_t color)
            : pageElement(pos_x_rel, pos_y_rel, size_x_rel, size_y_rel), color(color) {};
        bool drawAbsolute(GFXcanvas16 *screen) override;
    };
}
