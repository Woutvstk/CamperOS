#include "elementCircle.h"

namespace graphics
{

    bool elementCircle::drawAbsolute(GFXcanvas16 *screen)
    {
        uint16_t radius = min(this->size_x_px, this->size_y_px) / 2;
        screen->fillCircle(this->pos_x_px + radius, this->pos_y_px + radius, radius, color);
        return true;
    };

    touchInputEvent elementCircle::getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z)
    {
        touchInputEvent event;
        event.sourceElement = this;
        event.data.unsignedNumber = 5;
        return event;
    }

}
