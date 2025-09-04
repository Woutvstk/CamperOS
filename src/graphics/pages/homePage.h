#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>

#define homePageElementCount 2

namespace graphics
{
    class homePage : public Page
    {

    public:
        homePage();

        elementRectangle Rectangle0;
        elementCircle Circle0;

        pageElement *pageElements[homePageElementCount];
    };

    extern homePage home;

}
