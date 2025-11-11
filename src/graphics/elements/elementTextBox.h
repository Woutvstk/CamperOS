#pragma once
#include "../pageElement.h"

namespace graphics
{
    enum alignment
    {
        LEFT = 0,
        CENTRE = 1,
        RIGHT = 2
    };
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
        alignment textAlign = LEFT;

        elementTextBox(float pos_x_rel, float pos_y_rel, float size_x_rel, float size_y_rel, uint16_t color)
            : pageElement(pos_x_rel, pos_y_rel, size_x_rel, size_y_rel), textColor(color) {};
        bool drawAbsolute(GFXcanvas16 *screen) override;
        touchInputEvent getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z) override;

    private:
        void printString(GFXcanvas16 *textBox, const char *buffer, uint16_t size);
        uint16_t getCharsOnLine(const char *buffer);
    };

}
