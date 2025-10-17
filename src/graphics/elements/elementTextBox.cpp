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

        for (uint8_t i = 0; i < borderWidth; i++)
        {
            textBox.drawRect(i, i, textBox.width() - 2 * i, textBox.height() - 2 * i, borderColor);
        }

        printString(&textBox, text.c_str(), text.length());

        screen->drawRGBBitmap(pos_x_px, pos_y_px, textBox.getBuffer(), size_x_px, size_y_px);
        return false;
    };

    void elementTextBox::printString(GFXcanvas16 *textBox, const char *buffer, uint16_t size)
    {
        uint16_t cursor_x = padding + borderWidth;
        uint16_t cursor_y = padding + borderWidth;

        while (size--)
        {
            uint8_t c = *buffer;
            if (c == '\n')
            {                                     // Newline?
                cursor_x = padding + borderWidth; // Reset x to zero,
                cursor_y += textSize * 8;         // advance y one line
            }
            else if (c != '\r')
            { // Ignore carriage returns
                if ((cursor_x + textSize * 6 + padding + borderWidth) > size_x_px)
                {                                     // Off right?
                    cursor_x = padding + borderWidth; // Reset x to zero,
                    cursor_y += textSize * 8;         // advance y one line
                }
                textBox->drawChar(cursor_x, cursor_y, c, textColor, textColor, textSize,
                                  textSize);
                cursor_x += textSize * 6; // Advance x one char
            }
            buffer++;
        }
    }

}
