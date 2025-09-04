#include "elementRectangle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementRectangle::draw(Adafruit_SPITFT &screen) const
    {

        screen.fillRect(this->pos_x_px, this->pos_y_px, this->size_x_px, this->size_y_px, color);

        return true;
    };

}
