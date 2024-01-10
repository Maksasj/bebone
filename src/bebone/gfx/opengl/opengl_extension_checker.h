#ifndef _BEBONE_GFX_OPENGL_OPENGL_EXTENSION_CHECKER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_EXTENSION_CHECKER_H_

#include "../gfx_backend.h"

#include <set>
#include <string>

namespace bebone::gfx::opengl {
    /// Class used fort checking if specific opengl gl extension is available on device
    class GLExtensionChecker : private core::NonCopyable {
        private:
            std::set<std::string> m_extensions;

            /// Default constructor
            GLExtensionChecker();

            /// Function that updates extension set
            void update_extension_set();

            /// Internal function that checks if extension is available
            bool check(const std::string& extension) const;

        public:
            /*!
             * Static method that checks if extension is available on the device
             * @param extension - extension string representations
             * @return True if device is available, false if not
            */
            static bool available(const std::string& extension);
    };
}

#endif
