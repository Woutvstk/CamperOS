#include "testCalibrationPage.h"

namespace graphics
{
    testCalibrationPage::testCalibrationPage() :

                                                 Page(pageElements.data(), testCalibrationPageElementCount),
                                                 Background(0, 0, 1, 1, 0x0000),
                                                 buttonCalibrate(0.09, 0.8, 0.40, 0.12, 0x0000),
                                                 buttonDone(0.51, 0.8, 0.40, 0.12, 0x0000),
                                                 Circle0(0.5 - 0.08 / 2, 0.5 - 0.08 / 2, 0.08, 0.08, 0xca25)
    {
        pageElements = {
            &Background,
            &buttonCalibrate,
            &buttonDone,
            &Circle0};
    };

    testCalibrationPage testCalibration = testCalibrationPage();
}
