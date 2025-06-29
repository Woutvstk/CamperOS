#include "elementCircle.h"
#include "../../hardware/touchScreen.h"
#include <Arduino.h> //TODO remove

namespace graphics
{

    bool elementCircle::draw(uint8_t *elementDataStart) const
    {

        Serial.printf("Now drawing circle element (in derived circle class)\n");
        return false;
    };

}


