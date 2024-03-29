#ifndef _BEBONE_GFX_OPENGL_OPENGL_UNIFORM_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_UNIFORM_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    /// UBO
    class GLUniformBufferObject final : public GLBufferObject {
        private:
            u64 size;

        public:
            /*!
             * Default constructor
             * @param _size - desired buffer size
            */
            GLUniformBufferObject(const u64& _size);

            ~GLUniformBufferObject();

            /*!
             * Binds buffer to specific binding
             * @param binding - binding index
            */
            void bind_buffer_base(const i32& binding) const;

            /*!
             * Maps buffer to accessible memory region
             * @return - pointer to mapped memory region
            */
            void* map() const;

            /// Unmaps uniform buffer
            void unmap() const;

            /// Binds UBO
            void bind();

            /// Unbinds UBO
            void unbind();

            /// Destroys UBO. Calls automatically in the destructor
            void destroy();
    };
}

#endif
