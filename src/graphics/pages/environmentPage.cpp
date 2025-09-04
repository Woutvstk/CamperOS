#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() :

                                         Page(pageElements, environmentPageElementCount),
                                         Rectangle0(50, 50, 100, 100, 0x381f),
                                         Circle0(120, 80, 90, 90, 0x4e85)
    {
        pageElement *pageElements[environmentPageElementCount] =
            {
                &Rectangle0,
                &Circle0};
    };

    environmentPage environment = environmentPage();

}
