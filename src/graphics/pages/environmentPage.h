#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>

#define environmentPageElementCount 2

namespace graphics
{
    class environmentPage : public Page
    {

    public:
        environmentPage();

        elementRectangle Rectangle0;
        elementCircle Circle0;

        pageElement *pageElements[environmentPageElementCount];
    };

    extern environmentPage environment;

}
