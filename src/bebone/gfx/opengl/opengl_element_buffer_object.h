#ifndef _OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    class GLElementBufferObject : public GLBufferObject {
        public:
            GLElementBufferObject(const std::vector<GLuint>& indices);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
