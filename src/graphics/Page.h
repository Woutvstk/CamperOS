#include <stdio.h>
#include "pageElement.h"

namespace graphics
{

    template<uint8_t elementCnt>
    class Page
    {

    public:


        Page(uint8_t pageNr) : pageNr(pageNr){};

        // private:

    private:

        uint8_t pageNr;
        pageElement elements[elementCnt];
        
    };

}

