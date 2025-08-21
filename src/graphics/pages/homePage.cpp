#include "homePage.h"

namespace graphics
{
    elementRectangle Rectangle0 = elementRectangle(50, 50, 100, 100); // TODO: move this to pageData so elements can be moved/resized
    elementCircle Circle0 = elementCircle(120, 80, 90, 90);

    pageElement *homePageElements[] =
        {
            &Rectangle0,
            &Circle0

    };

    pageElement *(*p_homePageElements)[sizeof(homePageElements) / sizeof(homePageElements[0])] = &homePageElements;

    Page<pageElement *, homePageElementCount> home(homePageType, p_homePageElements);
}
