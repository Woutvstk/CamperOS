#pragma once
#include "../pageElement.h"

namespace graphics
{
    class elementTextBox : public pageElement
    {

    public:
        String text;
        uint8_t textSize = 1;
        uint16_t textColor = 0xFFFF;
        bool enableFill = false;
        uint16_t fillColor = 0x0000;
        uint8_t borderWidth = 0;
        uint16_t borderColor = 0xFFFF;
        uint16_t padding = 3;

        elementTextBox(uint16_t pos_x_px, uint16_t pos_y_px, uint16_t size_x_px, uint16_t size_y_px, uint16_t color)
            : pageElement(pos_x_px, pos_y_px, size_x_px, size_y_px), textColor(color) {};
        bool draw(GFXcanvas16 *screen) override;

    private:
        void printString(GFXcanvas16 *textBox, const char *buffer, uint16_t size);
    };
}
