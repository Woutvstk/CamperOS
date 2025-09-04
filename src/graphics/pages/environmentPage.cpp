#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() :

                                         Page(pageElements, environmentPageElementCount),
                                         Rectangle0(50, 50, 100, 100, 0x381f),
                                         Circle0(120, 80, 90, 90, 0x4e85),
                                         Graph0(10, 10, 300, 200, 0xffff)
    {
        pageElement *pageElements[environmentPageElementCount] =
            {
                &Rectangle0,
                &Circle0,
                &Graph0};
    };

    environmentPage environment = environmentPage();

}
