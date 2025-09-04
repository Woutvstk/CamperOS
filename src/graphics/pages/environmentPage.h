#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>

#define environmentPageElementCount 3

namespace graphics
{
    class environmentPage : public Page
    {

    public:
        environmentPage();

        elementRectangle Rectangle0;
        elementCircle Circle0;
        elementGraph Graph0;

        pageElement *pageElements[environmentPageElementCount];
    };

    extern environmentPage environment;

}
