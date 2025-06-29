#pragma once
#include "../pageElement.h"

// data size for rectangle is 3 bytes, RGB values
#define elementRectangleDataSize 1

namespace graphics
{

    class elementRectangle : public pageElement
    {
    public:
        elementRectangle(uint16_t p_start_x_px, uint16_t p_start_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px)
            : pageElement(p_start_x_px, p_start_y_px, p_size_x_px, p_size_y_px, elementRectangleDataSize) {};
        bool draw(uint8_t *elementDataStart) const override;
    };

}
