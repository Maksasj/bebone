#ifndef _BEBONE_GFX_OPENGL_OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "opengl_buffer_object.h"
#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// VAO
    class GLVertexArrayObject final : public GLBufferObject {
        public:
            /// Generates VAO and assigns unique ID
            GLVertexArrayObject();

            /// Destroys VAO
            ~GLVertexArrayObject();

            /*!
             * Interpret the vertex buffer data
             * @param vbo - vertex buffer object
             * @param layout - vertex shader layout
             * @param num_components - number of components
             * @param type - data type
             * @param stride - byte offset between consecutive vertex attributes
             * @param offset - an offset of the first component of the first vertex attribute in the array
             */
            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, const u64& offset);

            /*!
             * Interpret the vertex buffer data
             * @param vbo - vertex buffer object
             * @param layout - vertex shader layout
             * @param num_components - number of components
             * @param type - data type
             * @param stride - byte offset between consecutive vertex attributes
             * @param offset - an offset of the first component of the first vertex attribute in the array
            */
            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint num_components, GLenum type, GLsizeiptr stride, void* offset);

            /// Binds VAO
            void bind();

            /// Unbinds VAO
            void unbind();

            /// Destroys VAO. Calls automatically in the destructor
            void destroy();
    };
}

#endif
