#include "elementRectangle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementRectangle::draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const
    {

        Serial.printf("Now drawing rectangle element (in derived rectangle class)\n");
        screen.fillRect(this->start_x_px, this->start_y_px, this->size_x_px, this->size_y_px, 0x001F);

        return false;
    };

}
