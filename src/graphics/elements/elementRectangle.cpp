#include "elementRectangle.h"

namespace graphics
{
    bool elementRectangle::drawAbsolute(GFXcanvas16 *screen)
    {
        screen->fillRect(this->pos_x_px, this->pos_y_px, this->size_x_px, this->size_y_px, color);
        return true;
    };

    touchInputEvent elementRectangle::getTouchInputEvent(uint16_t touchPos_x, uint16_t touchPos_y, uint8_t touch_z)
    {
        touchInputEvent event;
        event.sourceElement = this;
        event.data.unsignedNumber = 7;
        return event;
    }
}
