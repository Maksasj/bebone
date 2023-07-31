#ifndef _BEBONE_GFX_OPENGL_ELEMENT_BUFFER_OBJECT_TPP_
#define _BEBONE_GFX_OPENGL_ELEMENT_BUFFER_OBJECT_TPP_

#include <vector>

#include "gl_buffer_object.h"

namespace bebone::gfx {
    template<class IndicesType>
    class GLElementBufferObject : public GLBufferObject {
        public:
            GLElementBufferObject(const std::vector<IndicesType>& indices) {
                glGenBuffers(1, &_ID);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(IndicesType), indices.data(), GL_STATIC_DRAW);
            }

            void bind() const override {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
            }
            void unbind() const override {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            };
            
            void terminate() const override {
                glDeleteBuffers(1, &_ID);
            };
    };
}

#endif
