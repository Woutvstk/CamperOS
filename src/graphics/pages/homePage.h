#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>

#define homePageElementCount 2

namespace homePage
{

    extern graphics::pageElement *homePageElements[homePageElementCount];

    extern graphics::pageElement *(*p_homePageElements)[homePageElementCount];
}

namespace graphics
{
    extern Page<pageElement *, homePageElementCount> home;
}
