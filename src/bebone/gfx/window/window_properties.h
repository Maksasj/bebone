#ifndef _BEBONE_GFX_WINDOW_WINDOW_PROPERTIES_H_
#define _BEBONE_GFX_WINDOW_WINDOW_PROPERTIES_H_

namespace bebone::gfx {
    // Structured used for configuring window properties
    struct WindowProperties {
        bool enableResize = false;

        // Todo, default name, width and height can be moved there
    };
}

#endif
