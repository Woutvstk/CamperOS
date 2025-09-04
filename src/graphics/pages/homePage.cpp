#include "homePage.h"

namespace graphics
{
    homePage::homePage() :

                           Page(pageElements, homePageElementCount),
                           Rectangle0(20, 20, 50, 50, 0xc956),
                           Circle0(100, 50, 45, 45, 0xca25)
    {
        pageElement *pageElements[homePageElementCount] =
            {
                &Rectangle0,
                &Circle0};
    };

    homePage home = homePage();

}
