#include "calibrationPage.h"

namespace graphics
{
    calibrationPage::calibrationPage() :

                                         Page(pageElements.data(), calibrationPageElementCount),
                                         Background(0, 0, 320, 240, 0xffff),
                                         Cross(0, 0, 20, 20, 0x0000)
    {
        pageElements = {
            &Background,
            &Cross};
    };

    calibrationPage calibration = calibrationPage();
}
