#ifndef _BEBONE_GFX_WINDOW_OPENGL_WINDOW_H_
#define _BEBONE_GFX_WINDOW_OPENGL_WINDOW_H_

#include "window.h"

namespace bebone::gfx {
    /// The class implements a window specifically for OpenGL graphics api
    class GLWindow : public Window {
        public:
            /*!
             * Default constructor
             * @param title - desired window title
             * @param width - desired window width
             * @param height - desired window height
            */
            GLWindow(const std::string& title, const int& width, const int& height, const WindowProperties& properties = {});
    };
}

#endif
