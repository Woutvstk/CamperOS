#include "elementCircle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementCircle::draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const
    {

        Serial.printf("Now drawing circle element (in derived circle class)\n");

        uint16_t radius = min(this->size_x_px, this->size_y_px) / 2;
        screen.fillCircle(this->start_x_px + radius, this->start_y_px + radius, radius, 0xF800);
        return false;
    };

}
