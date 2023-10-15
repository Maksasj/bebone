#ifndef _OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    class GLElementBufferObject final : public GLBufferObject {
        public:
            GLElementBufferObject(const std::vector<GLuint>& indices);

            // Todo lets write destructor

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
