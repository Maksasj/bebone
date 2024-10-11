#include "opengl_window.h"

namespace bebone::gfx {
    GLWindow::GLWindow(const std::string& title, const int& width, const int& height, const WindowProperties& properties) : Window(title, width, height, properties) {
        glfwMakeContextCurrent(get_backend());

        LOG_TRACE("Initialized OpenGL window");
    }

    GfxAPI GLWindow::get_api() const {
        return GfxAPI::OpenGL;
    }
}
