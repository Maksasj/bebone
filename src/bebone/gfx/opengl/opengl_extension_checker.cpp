#include "opengl_extension_checker.h"

namespace bebone::gfx::opengl {
    GLExtensionChecker::GLExtensionChecker() {
        update_extension_set();
    }

    void GLExtensionChecker::update_extension_set() {
        GLint no_of_extensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &no_of_extensions);

        for (int i = 0; i < no_of_extensions; ++i)
            m_extensions.insert((const char*)glGetStringi(GL_EXTENSIONS, i));
    }

    bool GLExtensionChecker::check(const std::string& extension) const {
        return m_extensions.find(extension) != m_extensions.end();
    }

    bool GLExtensionChecker::available(const std::string& extension) {
        static GLExtensionChecker checker;
        return checker.check(extension);
    }
}
