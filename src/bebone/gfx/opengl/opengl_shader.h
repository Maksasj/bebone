#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

namespace bebone::gfx::opengl {
    class GLShader : private core::NonCopyable {
        private:
            GLuint shader;

        public:
            GLShader(ShaderCode& code, GLenum shaderType);
            GLuint get_shader() const;
            void destroy();
    };

    class GLShaderProgram : private core::NonCopyable {
        private:
            GLuint id;

        public:
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);

            void set_uniform(const char* uniformName, GLint value);
            void set_uniform(const char* uniformName, GLuint value);
            void set_uniform(const char* uniformName, GLfloat value);
            void set_uniform(const char* uniformName, bebone::core::Mat4f value);

            void enable();
            void destroy();
    };
}

#endif
