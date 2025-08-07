#include "elementRectangle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementRectangle::draw(Adafruit_SPITFT &screen, uint8_t *elementDataStart) const
    {

        screen.fillRect(this->start_x_px, this->start_y_px, this->size_x_px, this->size_y_px,
                        screen.color565(*(elementDataStart + redColorOffset), *(elementDataStart + greenColorOffset), *(elementDataStart + blueColorOffset)));

        return false;
    };

}
