

#include "../Page.h"
#include "../elements_list.h"
#include "../pageElement.h"
#include <stdio.h>

namespace graphics
{

    const uint8_t homePageElementCount = 2;

    extern pageElement *homePageElements[homePageElementCount];

    const pageTypesEnum homePageType = HOME;
    
    extern pageElement *(*p_homePageElements)[homePageElementCount];

    extern Page<pageElement *, homePageElementCount> home;
}
