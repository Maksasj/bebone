#ifndef _BEBONE_GFX_WINDOW_WINDOW_HANDLER_H_
#define _BEBONE_GFX_WINDOW_WINDOW_HANDLER_H_

#include <memory>
#include <string>

#include "../gfx_backend.h"

#include "window_size_listener.h"

namespace bebone::gfx {
    class WindowHandler : private core::NonCopyable {
        private:
            WindowSizeListener windowSizeListener;

        public:
            WindowHandler(Window* window);

            const WindowSizeListener& get_window_size_listener() const;
    };
}

#endif
