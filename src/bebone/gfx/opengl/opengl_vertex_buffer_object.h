#ifndef _BEBONE_GFX_OPENGL_OPENGL_VERTEX_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_VERTEX_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    /// VBO
    class GLVertexBufferObject final : public GLBufferObject {
        public:
            /*!
             * Initializes VBO. GL_STATIC_DRAW usage is set by default. Automatically binds it
             * @param vertices - vertex data (could be null if usage set to GL_DYNAMIC_DRAW)
             * @param size - array size in bytes
             * @param usage - VBO usage. Specifies the expected usage pattern of the data store
             */
            GLVertexBufferObject(const void* vertices, const GLsizeiptr& size, const GLenum& usage = GL_STATIC_DRAW);

            /// Destroys VBO
            ~GLVertexBufferObject();

            /*!
             * Updates a subset of a VBO data store. Automatically binds and unbinds the VBO. To use this method VBO usage must be set to GL_DYNAMIC_DRAW
             * @param offset - specifies the offset into the VBO where data replacement will begin, measured in bytes.
             * @param size - specifies the size in bytes of the data store region being replaced.
             * @param data - specifies a pointer to the new data that will be copied into the data store
             */
            void buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data);

            /// Binds VBO
            void bind();

            /// Unbinds VBO
            void unbind();

            /// Destroys VBO. Calls automatically in the destructor
            void destroy();
    };
}

#endif
