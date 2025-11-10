#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() : Page(pageElements.data(), environmentPageElementCount),
                                         Rectangle0(0.02, 0.02, 0.2, 0.2, 0xc956),
                                         Circle0(0.1, 0.1, 0.2, 0.2, 0xca25),
                                         Graph0(0.2, 0.2, 0.3, 0.3, 0xcff5),
                                         Text0(0.6, 0.2, 0.3, 0.3, 0xFFFF),
                                         Graph1(0.2, 0.7, 0.3, 0.3, 0xffff)
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
