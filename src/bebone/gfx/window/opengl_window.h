#ifndef _OPENGL_WINDOW_H_
#define _OPENGL_WINDOW_H_

#include "window.h"

namespace bebone::gfx {
    class GLWindow : public Window {
        public:
            GLWindow(const std::string& title, const int& width, const int& height);
    };
}

#endif
