#include "elementCircle.h"

namespace graphics
{

    bool elementCircle::draw(GFXcanvas16 *screen)
    {
        uint16_t radius = min(this->size_x_px, this->size_y_px) / 2;
        screen->fillCircle(this->pos_x_px + radius, this->pos_y_px + radius, radius, color);
        return true;
    };

}
