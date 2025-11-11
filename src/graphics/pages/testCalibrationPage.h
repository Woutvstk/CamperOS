#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>
#include "array"

#define testCalibrationPageElementCount 4

namespace graphics
{
    class testCalibrationPage : public Page
    {

    public:
        testCalibrationPage();

        elementRectangle Background;
        elementTextBox buttonCalibrate;
        elementTextBox buttonDone;
        elementCircle Circle0;

        std::array<pageElement *, testCalibrationPageElementCount> pageElements;
    };

    extern testCalibrationPage testCalibration;
}
