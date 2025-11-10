#include "elementTextBox.h"

#define fontHeight 8
#define fontWidth 6

namespace graphics
{

    bool elementTextBox::drawAbsolute(GFXcanvas16 *screen)
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
        uint16_t cursor_x;
        uint16_t cursor_y;

        cursor_x = pos_x_px + padding + borderWidth;
        cursor_y = pos_y_px + padding + borderWidth;
        while (size > 0) // loop over lines of text in buffer until out of chars
        {
            if ((cursor_y + textSize * fontHeight) > pos_y_px + size_y_px) // check if the new line will still be within bounds
            {
                break;
            }

            uint16_t chars = min(size, getCharsOnLine(buffer)); // How many chars should be printed on this line

            if (chars == 0) // at newline character
            {
                size--;
                buffer++;
            }
            else
            {
                switch (textAlign)
                {
                case LEFT:

                    cursor_x = pos_x_px + padding + borderWidth;
                    break;
                case CENTRE:

                    cursor_x = pos_x_px + size_x_px / 2 - chars * fontWidth * textSize / 2;
                    break;
                case RIGHT:

                    cursor_x = pos_x_px + size_x_px - padding - borderWidth - chars * fontWidth * textSize;
                    break;

                default:
                    break;
                }

                for (uint16_t i = 0; i < chars; i++) // loop over amount of chars that should be printed on this line
                {

                    screen->drawChar(cursor_x, cursor_y, *buffer, textColor, textColor, textSize,
                                     textSize);

                    cursor_x += textSize * fontWidth; // Advance x one char
                    size--;
                    buffer++;
                }

                cursor_y += textSize * fontHeight; // change cursor_y to new line
            }
        }
    }

    uint16_t elementTextBox::getCharsOnLine(const char *buffer)

    {
        uint16_t maxCharsOnLine = ((size_x_px - 2 * (padding + borderWidth)) / (textSize * fontWidth));

        for (uint16_t i = 0; i < maxCharsOnLine; i++)
        {
            if (*buffer == 0xa) // check if current char is newline
            {
                return i;
            }
            buffer++;
        }
        return maxCharsOnLine;
    }

    touchInputEvent elementTextBox::getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z)
    {
        touchInputEvent event;
        event.sourceElement = this;
        event.data.unsignedNumber = 5;
        return event;
    }
}
