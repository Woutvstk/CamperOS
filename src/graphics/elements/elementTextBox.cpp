#include "elementTextBox.h"

namespace graphics
{

    bool elementTextBox::draw(GFXcanvas16 *screen)
    {
        // use temporary canvas so that text wrapping can do its thing
        GFXcanvas16 textBox = GFXcanvas16(size_x_px, size_y_px);
        if (enableFill)
        {
            textBox.fillScreen(fillColor);
        }
        else // copy the current background onto the temporary canvas for transparent background
        {
            pageElement::extractRGBBitmap(screen, pos_x_px, pos_y_px, &textBox);
        }

        for (uint8_t i = 0; i < borderWidth, i++)
        {
            textBox.drawRect(pos_x_px + i, pos_y_px + i, size_x_px - 2 * i, size_y_px - 2 * i, borderColor);
        }

        textBox.setCursor(0, 0);
        textBox.setTextSize(textSize);
        textBox.setTextColor(textColor);
        textBox.print(text);

        screen->drawRGBBitmap(pos_x_px, pos_y_px, textBox.getBuffer(), size_x_px, size_y_px);
        return false;
    };

}
