#ifndef _BVAONE_GFX_OPENGL_VERTEX_ARRAY_OBJECT_TPP_
#define _BVAONE_GFX_OPENGL_VERTEX_ARRAY_OBJECT_TPP_

#include <vector>

#include "gl_buffer_object.h"

namespace bebone::gfx {
    class GLVertexArrayObject : public GLBufferObject {
        public:
            GLVertexArrayObject() {
                glGenVertexArrays(1, &_ID);
            }

            void link_attribute(unsigned long index, unsigned long componentsNumber, unsigned long type, unsigned long strideSize, void* offset) {
                glVertexAttribPointer(index, componentsNumber, type, GL_FALSE, strideSize, offset);
                glEnableVertexAttribArray(index);
            }

            void bind() const override {
                glBindVertexArray(_ID);
            }

            void unbind() const override {
                glBindVertexArray(0);
            }
            
            void terminate() const override {
                glDeleteVertexArrays(1, &_ID);
            };
    };
}

#endif