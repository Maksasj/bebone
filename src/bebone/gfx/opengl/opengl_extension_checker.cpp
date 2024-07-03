#include "opengl_extension_checker.h"

namespace bebone::gfx {
    GLExtensionChecker::GLExtensionChecker() {
        update_extension_set();
    }

    void GLExtensionChecker::update_extension_set() {
        GLint num_of_extensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &num_of_extensions);

        for (int i = 0; i < num_of_extensions; ++i)
            extensions.insert((const char*)glGetStringi(GL_EXTENSIONS, i));
    }

    bool GLExtensionChecker::check(const std::string& extension) const {
        return extensions.find(extension) != extensions.end();
    }

    bool GLExtensionChecker::available(const std::string& extension) {
        static GLExtensionChecker checker;
        return checker.check(extension);
    }
}
