#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>
#include "array"

#define environmentPageElementCount 7

namespace graphics
{
    class environmentPage : public Page
    {

    public:
        environmentPage();

        elementRectangle Rectangle0;
        elementCircle Circle0;
        elementGraph Graph0;
        elementTextBox Text0;
        elementGraph Graph1;
        elementCross Cross0;
        elementCross Cross1;

        std::array<pageElement *, environmentPageElementCount> pageElements;
    };

    extern environmentPage environment;
}
