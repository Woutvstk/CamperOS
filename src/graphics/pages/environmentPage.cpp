#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() : Page(pageElements.data(), environmentPageElementCount),
                                         Rectangle0(20, 20, 50, 50, 0xc956),
                                         Circle0(100, 50, 45, 45, 0xca25),
                                         Graph0(150, 10, 150, 100, 0xcff5),
                                         Graph1(10, 100, 120, 120, 0xffff)
    {
        pageElements = {
            &Rectangle0,
            &Circle0,
            &Graph0,
            &Graph1};
    };

    environmentPage environment = environmentPage();
}
