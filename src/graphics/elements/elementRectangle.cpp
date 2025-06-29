#include "elementRectangle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementRectangle::draw(uint8_t *elementDataStart) const
    {

        Serial.printf("Now drawing rectangle element (in derived rectangle class)\n");

        return false;
    };

}
