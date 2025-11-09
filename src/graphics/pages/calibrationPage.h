#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>
#include "array"

#define calibrationPageElementCount 2

namespace graphics
{
    class calibrationPage : public Page
    {

    public:
        calibrationPage();

        elementRectangle Background;
        elementCross Cross;

        std::array<pageElement *, calibrationPageElementCount> pageElements;
    };

    extern calibrationPage calibration;
}
