#include "elementRectangle.h"

namespace graphics
{
    bool elementRectangle::draw(Adafruit_SPITFT *screen) 
    {
        screen->fillRect(this->pos_x_px, this->pos_y_px, this->size_x_px, this->size_y_px, color);
        return true;
    };
}
