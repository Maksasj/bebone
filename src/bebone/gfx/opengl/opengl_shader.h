#ifndef _OPENGL_SHADER_H_
#define _OPENGL_SHADER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLShader : private core::NonCopyable {
        private:
            GLuint m_shader;
            GLShaderProperties m_properties;

        public:
            GLShader(const ShaderCode& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);
            GLShader(const std::string& code, const ShaderType& shaderType, const GLShaderProperties& properties = NONE);

            GLuint get_shader() const;
            const GLShaderProperties& get_properties() const;

            void destroy();
    };

    class GLShaderProgram : private core::NonCopyable {
        private:
            GLuint id;
            GLShaderProperties m_properties;

            void create_shader_program(const GLShader& vertex, const GLShader& fragment);
            GLint get_uniform_location(const char* uniformName) const;
        public:
            GLShaderProgram(const GLShader& vertex, const GLShader& fragment);

            void set_uniform(const char* uniformName, const i32& value) const;
            void set_uniform(const char* uniformName, const GLsizei& size, const i32* value) const;
            void set_uniform(const char* uniformName, const u32& value) const;
            void set_uniform(const char* uniformName, const f32& value) const;
            void set_uniform(const char* uniformName, const Mat4f& value) const;

            void bind_buffer(const char* uniformBufferName, const i32& binding, const GLUniformBufferObject& buffer) const;

            void enable();
            void destroy();
    };
}

#endif
