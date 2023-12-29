#ifndef _BEBONE_GFX_OPENGL_OPENGL_EXTENSION_CHECKER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_EXTENSION_CHECKER_H_

#include "../gfx_backend.h"

#include <set>
#include <string>

namespace bebone::gfx::opengl {
    class GLExtensionChecker : private core::NonCopyable {
    private:
        std::set<std::string> m_extensions;

        GLExtensionChecker();

        void update_extension_set();

        bool check(const std::string& extension) const;

    public:

        static bool available(const std::string& extension);
    };
}

#endif
