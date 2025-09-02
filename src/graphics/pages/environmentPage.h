#include "../Page.h"
#include "../elementList.h"
#include "../pageElement.h"
#include <stdio.h>

#define environmentPageElementCount 2

namespace environmentPage
{

    extern graphics::pageElement *environmentPageElements[environmentPageElementCount];

    extern graphics::pageElement *(*p_environmentPageElements)[environmentPageElementCount];
}

namespace graphics
{
    extern Page<pageElement *, environmentPageElementCount> environment;
}
