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

            GLShaderProgram(const GLShaderProgram &) = delete;
            void operator=(const GLShaderProgram &) = delete;
            GLShaderProgram(GLShaderProgram &&) = delete;
            GLShaderProgram &operator=(GLShaderProgram &&) = delete;

            void set_uniform(const char* uniformName, GLint value);
            void set_uniform(const char* uniformName, GLuint value);
            void set_uniform(const char* uniformName, GLfloat value);

            void enable();
            void destroy();
    };
}

#endif
