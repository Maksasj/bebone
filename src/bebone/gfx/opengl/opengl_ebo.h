#ifndef _OPENGL_EBO_H_
#define _OPENGL_EBO_H_

#include "opengl_buffer.h"

namespace bebone::gfx::opengl {
    class GLElementBufferObject : public GLBufferObject {
        public:
            GLElementBufferObject(GLuint* indices, GLsizeiptr size);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
