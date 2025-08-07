

#include "../Page.h"
#include "../elements_list.h"
#include "../pageElement.h"
#include <stdio.h>

namespace graphics
{
    elementRectangle Rectangle0 = elementRectangle(50, 50, 100, 100); //TODO: move this to pageData so elements can be moved/resized
    elementCircle Circle0 = elementCircle(120, 80, 90, 90);

    pageElement *homePageElements[] =
        {

            &Rectangle0,
            &Circle0

    };

    pageTypesEnum homePageType = HOME;
    pageElement *(*p_homePageElements)[sizeof(homePageElements) / sizeof(homePageElements[0])] = &homePageElements;
    // original and working line:
    // Page<pageElement *, sizeof(homePageElements) / sizeof(homePageElements[0])> home(homePageType, p_homePageElements);

    // new line with error
    using ElementType = typename std::remove_reference<decltype(homePageElements[0])>::type;
    Page<ElementType, sizeof(homePageElements) / sizeof(homePageElements[0])> home(homePageType, p_homePageElements);
}
