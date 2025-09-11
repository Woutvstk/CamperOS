#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>
#include "array"

#define environmentPageElementCount 4

namespace graphics
{
    class environmentPage : public Page
    {

    public:
        environmentPage();

        elementRectangle Rectangle0;
        elementCircle Circle0;
        elementGraph Graph0;
        elementGraph Graph1;

        std::array<pageElement *, environmentPageElementCount> pageElements;
    };

    extern environmentPage environment;
}
