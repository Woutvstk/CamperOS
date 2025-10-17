#include "elementTextBox.h"

namespace graphics
{

    bool elementTextBox::draw(GFXcanvas16 *screen)
    {
        // use temporary canvas so that text wrapping can do its thing

        if (enableFill)
        {
            screen->fillRect(pos_x_px, pos_y_px, size_x_px, size_y_px, fillColor);
        }

        for (uint8_t i = 0; i < borderWidth; i++)
        {
            screen->drawRect(pos_x_px + i, pos_y_px + i, size_x_px - 2 * i, size_y_px - 2 * i, borderColor);
        }

        printString(screen, text.c_str(), text.length());

        return false;
    };

    void elementTextBox::printString(GFXcanvas16 *screen, const char *buffer, uint16_t size)
    {
        uint16_t cursor_x = pos_x_px + padding + borderWidth;
        uint16_t cursor_y = pos_y_px + padding + borderWidth;

        while (size--)
        {

            if (*buffer == '\n')
            {                                                // Newline?
                cursor_x = pos_x_px + padding + borderWidth; // Reset x to zero,
                cursor_y += textSize * 8;                    // advance y one line
            }
            else if (*buffer != '\r')
            { // Ignore carriage returns
                if ((cursor_x + textSize * 6 + padding + borderWidth) > pos_x_px + size_x_px)
                {                                                // Off right?
                    cursor_x = pos_x_px + padding + borderWidth; // Reset x to zero,
                    cursor_y += textSize * 8;                    // advance y one line
                    if (*buffer == 0x20)                         // if first character on new line is a space, skip character
                    {
                        buffer++;
                    }
                }
                screen->drawChar(cursor_x, cursor_y, *buffer, textColor, textColor, textSize,
                                 textSize);
                cursor_x += textSize * 6; // Advance x one char
            }
            buffer++;
        }
    }

}
