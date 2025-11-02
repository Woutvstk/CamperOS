#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() : Page(pageElements.data(), environmentPageElementCount),
                                         Rectangle0(20, 20, 100, 25, 0xc956),
                                         Circle0(100, 50, 45, 45, 0xca25),
                                         Graph0(150, 10, 160, 100, 0xcff5),
                                         Text0(150, 100, 50, 50, 0xFFFF),
                                         Graph1(150, 110, 80, 100, 0xffff)
    {
        pageElements = {
            &Rectangle0,
            &Circle0,
            &Graph0,
            &Text0,
            &Graph1};
    };

    environmentPage environment = environmentPage();
}
