#include "environmentPage.h"

namespace graphics
{
    environmentPage::environmentPage() :

                                         Page(pageElements, environmentPageElementCount),
                                         Rectangle0(50, 50, 100, 100),
                                         Circle0(120, 80, 90, 90)
    {
        pageElement *pageElements[environmentPageElementCount] =
            {
                &Rectangle0,
                &Circle0};
    };

    environmentPage environment = environmentPage();

}
