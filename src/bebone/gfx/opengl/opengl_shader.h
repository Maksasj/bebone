#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLShader {
        private:
            GLuint shader;

        public:
            GLShader(const char* fileName, GLenum shaderType);
            GLuint get_shader() const;
            void destroy();
    };

    class GLShaderProgram {
        private:
            GLuint id;

        public:
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);
            void enable();
            void destroy();
    };
}

#endif
