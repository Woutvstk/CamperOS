#include "elementTextBox.h"

namespace graphics
{

    bool elementTextBox::draw(GFXcanvas16 *screen)
    {
        GFXcanvas16 textBox = GFXcanvas16(size_x_px, size_y_px);
        pageElement::extractRGBBitmap(screen, pos_x_px, pos_y_px, &textBox);

        textBox.setCursor(0, 0);
        textBox.setTextSize(textSize);
        textBox.setTextColor(textColor);
        textBox.print(text);

        screen->drawRGBBitmap(pos_x_px, pos_y_px, textBox.getBuffer(), size_x_px, size_y_px);
        return false;
    };

}
