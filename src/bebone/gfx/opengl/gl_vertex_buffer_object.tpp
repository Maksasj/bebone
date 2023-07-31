#ifndef _BEBONE_GFX_OPENGL_VERTEX_BUFFER_OBJECT_TPP_
#define _BEBONE_GFX_OPENGL_VERTEX_BUFFER_OBJECT_TPP_

#include <vector>

#include "gl_buffer_object.h"

namespace bebone::gfx {
    template<class VertexType>
    class GLVertexBufferObject : public GLBufferObject {
        public:
            GLVertexBufferObject(const std::vector<VertexType>& vertices) {
                glGenBuffers(1, &_ID);

                glBindBuffer(GL_ARRAY_BUFFER, _ID);
                glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexType), vertices.data(), GL_STATIC_DRAW);
            }

            void bind() const override {
                glBindBuffer(GL_ARRAY_BUFFER, _ID);
            }
            void unbind() const override {
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            };
            
            void terminate() const override {
                glDeleteBuffers(1, &_ID);
            };
    };
}

#endif
