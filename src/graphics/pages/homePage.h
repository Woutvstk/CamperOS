

#include "../Page.h"
#include "../elements_list.h"
#include "../pageElement.h"

namespace graphics
{
    elementRectangle Rectangle0 = elementRectangle(10, 10, 50, 50);
    elementCircle Circle0 = elementCircle(60, 60, 50, 50);

    pageElement *homePageElements[] =
        {

            &Rectangle0,
            &Circle0

    };

    pageTypesEnum homePageType = HOME;
    pageElement *(*p_homePageElements)[sizeof(homePageElements) / sizeof(homePageElements[0])] = &homePageElements;
    Page<pageElement *, sizeof(homePageElements) / sizeof(homePageElements[0])> home(homePageType, p_homePageElements);

}
