#include "homePage.h"

namespace graphics
{
    homePage::homePage() :

                           Page(pageElements.data(), homePageElementCount),
                           Background(0, 0, 1, 1, 0x0000),
                           Rectangle0(0.01, 0.01, 0.2, 0.2, 0xc956),
                           Circle0(0.5 - 0.08 / 2, 0.5 - 0.08 / 2, 0.08, 0.08, 0xca25)
    {
        pageElements = {
            &Background,
            &Rectangle0,
            &Circle0};
    };

    homePage home = homePage();
}
