// C++ wrappers
extern "C" {

#include "gfx.h"

}

namespace ugfx {

struct display
{
    GDisplay* d;

public:
    display(GDisplay* d = GDISP) : d(d) {}

    inline coord_t width() { return gdispGGetWidth(d); }
    inline coord_t height() { return gdispGGetHeight(d); }

    inline void clear(color_t clear_to_color = Black) 
    { gdispGClear(d, clear_to_color); }
};

}