#include "homePage.h"

namespace homePage
{
    graphics::elementRectangle Rectangle0 = graphics::elementRectangle(50, 50, 100, 100); // TODO: move this to pageData so elements can be moved/resized
    graphics::elementCircle Circle0 = graphics::elementCircle(120, 80, 90, 90);

    graphics::pageElement *homePageElements[] =
        {
            &Rectangle0,
            &Circle0

    };

    graphics::pageElement *(*p_homePageElements)[sizeof(homePageElements) / sizeof(homePageElements[0])] = &homePageElements;

}

namespace graphics
{
    Page<pageElement *, homePageElementCount> home(homePage::p_homePageElements);
}
