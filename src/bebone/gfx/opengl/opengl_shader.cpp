#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    GLShader::GLShader(const ShaderCode& code, const ShaderType& shaderType) {
        shader = glCreateShader(shaderType.to_opengl());

        const std::string& contents = code.get_shader_source_code().get_shader_source();
        const char* source = contents.c_str();

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        // const auto& source = code.get_byte_code();

        // // **_ARB things can be used only with specific glad extensions, see all-extensions glad branch
        // glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, source.data(), source.size() * sizeof(unsigned int));
        // glSpecializeShaderARB(shader, "main", 0, nullptr, nullptr);
    }

    GLuint GLShader::get_shader() const {
        return shader;
    }

    void GLShader::destroy() {
        glDeleteShader(shader);
    }

    GLShaderProgram::GLShaderProgram(const GLShader& vertex, const GLShader& fragment) {
        id = glCreateProgram();
        glAttachShader(id, vertex.get_shader());
        glAttachShader(id, fragment.get_shader());
        glLinkProgram(id);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const i32& value) const {
        const auto uniform = glGetUniformLocation(id, uniformName);
        glUniform1i(uniform, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const u32& value) const {
        const auto uniform = glGetUniformLocation(id, uniformName);
        glUniform1ui(uniform, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const f32& value) const {
        const auto location = glGetUniformBlockIndex(id, uniformName);
        glUniform1f(location, value);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const Mat4f& value) const {
        const auto uniform = glGetUniformLocation(id, uniformName);
        glUniformMatrix4fv(uniform, 1, GL_FALSE, value.e);
    }

    void GLShaderProgram::bind_buffer(const char* uniformBufferName, const i32& binding, const GLUniformBufferObject& buffer) const {
        buffer.bind_buffer_base(binding);

        const auto uboIndex = glGetUniformBlockIndex(id, uniformBufferName);
        glUniformBlockBinding(id, uboIndex, binding);
    }

    void GLShaderProgram::enable() {
        glUseProgram(id);
    }

    void GLShaderProgram::destroy() {
        glDeleteProgram(id);
    }
}
