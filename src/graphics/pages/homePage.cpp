#include "homePage.h"

namespace graphics
{
    homePage::homePage() :

                           Page(pageElements.data(), homePageElementCount),
                           Background(0, 0, 320, 240, 0x0000),
                           Rectangle0(5, 5, 50, 50, 0xc956),
                           Circle0(100, 50, 15, 15, 0xca25)
    {
        pageElements = {
            &Background,
            &Rectangle0,
            &Circle0};
    };

    homePage home = homePage();
}
