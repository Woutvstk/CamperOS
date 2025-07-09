#pragma once
#include "../pageElement.h"

// data size for circle is 3 bytes, RGB values
#define elementCircleDataSize 1

namespace graphics
{

    class elementCircle : public pageElement
    {
    public:
        elementCircle(uint16_t p_start_x_px, uint16_t p_start_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px)
            : pageElement(p_start_x_px, p_start_y_px, p_size_x_px, p_size_y_px, elementCircleDataSize) {};
        bool draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const override;
    };

}


