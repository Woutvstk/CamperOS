#pragma once
#include "../pageElement.h"

// data size for circle is 3 bytes, RGB values
#define elementCircleDataSize 3

namespace graphics
{

    class elementCircle : public pageElement
    {
    public:
        const uint16_t redColorOffset = 0;
        const uint16_t greenColorOffset = 1;
        const uint16_t blueColorOffset = 2;

        elementCircle(uint16_t p_start_x_px, uint16_t p_start_y_px, uint16_t p_size_x_px, uint16_t p_size_y_px)
            : pageElement(p_start_x_px, p_start_y_px, p_size_x_px, p_size_y_px, elementCircleDataSize) {};
        bool draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const override;
    };

}
