#ifndef _BEBONE_GFX_OPENGL_OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"

namespace bebone::gfx {
    /// EBO
    class GLElementBufferObject final : public GLBufferObject {
        public:
            /*!
             * Generates EBO and assigns unique ID
             * @param indices - array of indices (could be null if usage set to GL_DYNAMIC_DRAW)
             * @param size - array size in bytes
             * @param usage - EBO usage. Specifies the expected usage pattern of the data store
             */
            GLElementBufferObject(const void* indices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW);

            /// Destroys the EBO
            ~GLElementBufferObject();

            /*!
             * Updates a subset of a EBO data store. Automatically binds and unbinds the EBO. To use this method EBO usage must be set to GL_DYNAMIC_DRAW
             * @param offset - specifies the offset into the EBO where data replacement will begin, measured in bytes.
             * @param size - specifies the size in bytes of the data store region being replaced.
             * @param data - specifies a pointer to the new data that will be copied into the data store
             */
            void buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data);

            /// Binds EBO
            void bind();

            /// Unbinds EBO
            void unbind();

            /// Destroys EBO. Calls automatically in the destructor
            void destroy();
    };
}

#endif
