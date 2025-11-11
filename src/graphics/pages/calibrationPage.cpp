#include "calibrationPage.h"

namespace graphics
{
    calibrationPage::calibrationPage() :

                                         Page(pageElements.data(), calibrationPageElementCount),
                                         Background(0, 0, 1, 1, 0xffff),
                                         Cross(0, 0, 0.08, 0.08, 0x0000)
    {
        pageElements = {
            &Background,
            &Cross};
    };

    calibrationPage calibration = calibrationPage();
}
