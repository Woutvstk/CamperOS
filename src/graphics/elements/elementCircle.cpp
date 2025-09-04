#include "elementCircle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementCircle::draw(Adafruit_SPITFT &screen) const
    {

        uint16_t radius = min(this->size_x_px, this->size_y_px) / 2;
        screen.fillCircle(this->start_x_px + radius, this->start_y_px + radius, radius, color);
        return true;
    };

}
