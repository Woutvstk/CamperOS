#include "environmentPage.h"

namespace environmentPage
{
    graphics::elementRectangle Rectangle0 = graphics::elementRectangle(10, 10, 35, 50); // TODO: move this to pageData so elements can be moved/resized
    graphics::elementCircle Circle0 = graphics::elementCircle(150, 50, 10, 40);

    graphics::pageElement *environmentPageElements[] =
        {
            &Rectangle0,
            &Circle0

    };

    graphics::pageElement *(*p_environmentPageElements)[sizeof(environmentPageElements) / sizeof(environmentPageElements[0])] = &environmentPageElements;

}

namespace graphics
{
    Page<pageElement *, environmentPageElementCount> environment(environmentPage::p_environmentPageElements);
}
