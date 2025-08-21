#include "../Page.h"
#include "../elements_list.h"
#include "../pageElement.h"
#include <stdio.h>

#define homePageElementCount 2
#define homePageType HOME

namespace graphics
{

    extern pageElement *homePageElements[homePageElementCount];

    extern pageElement *(*p_homePageElements)[homePageElementCount];

    extern Page<pageElement *, homePageElementCount> home;
}
