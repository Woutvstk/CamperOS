#include "elementCross.h"

namespace graphics
{
    bool elementCross::draw(GFXcanvas16 *screen)
    {
        screen->fillRect(pos_x_px + size_x_px / 2 - width / 2, pos_y_px, width, size_y_px, color);
        screen->fillRect(pos_x_px, pos_y_px + size_y_px / 2 - width / 2, size_x_px, width, color);
        return true;
    };
}
