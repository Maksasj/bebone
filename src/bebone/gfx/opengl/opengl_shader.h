#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLShader : private core::NonCopyable {
        private:
            GLuint shader;

        public:
            GLShader(const ShaderCode& code, const ShaderType& shaderType);
            GLShader(const std::string& code, const ShaderType& shaderType);

            GLuint get_shader() const;
            void destroy();
    };

    class GLShaderProgram {
        private:
            GLuint id;

        public:
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);

            void set_uniform(const char* uniformName, const i32& value) const;
            void set_uniform(const char* uniformName, const u32& value) const;
            void set_uniform(const char* uniformName, const f32& value) const;
            void set_uniform(const char* uniformName, const Mat4f& value) const;

            void bind_buffer(const char* uniformBufferName, const i32& binding, const GLUniformBufferObject& buffer) const;

            void enable();
            void destroy();
    };
}

#endif
