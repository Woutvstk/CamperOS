#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() : Page(pageElements.data(), environmentPageElementCount),
                                         Rectangle0(20, 20, 100, 25, 0xc956),
                                         Circle0(100, 50, 45, 45, 0xca25),
                                         Graph0(150, 10, 160, 100, 0xcff5),
                                         Text0(150, 100, 50, 50, 0xFFFF),
                                         Graph1(150, 110, 80, 100, 0xffff),
                                         Cross0(75, 75, 25, 25, 0xffff),
                                         Cross1(185, 140, 25, 25, 0xffff)
    {
        pageElements = {
            &Rectangle0,
            &Circle0,
            &Graph0,
            &Text0,
            &Graph1,
            &Cross0,
            &Cross1};
    };

    environmentPage environment = environmentPage();
}
