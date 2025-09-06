#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() : Page(pageElements.data(), environmentPageElementCount),
                                         Rectangle0(20, 20, 50, 50, 0xc956),
                                         Circle0(100, 50, 45, 45, 0xca25),
                                         Circle1(30, 150, 10, 10, 0xcff5),
                                         Graph0(10, 10, 300, 200, 0xffff)
    {
        pageElements = {
            &Rectangle0,
            &Circle0,
            &Circle1,
            &Graph0};
    };

    environmentPage environment = environmentPage();
}
