#include "opengl_shader_program.h"

namespace bebone::gfx::opengl {
    GLShaderProgram::GLShaderProgram(const GLShader& vertex, const GLShader& fragment) {
        create_shader_program(vertex, fragment);

        if(vertex.get_properties() != fragment.get_properties()) {
            // Todo, we need to have some sort of policy for compatibility of shader properties
            throw std::runtime_error("Provided opengl shaders have different properties, therefore they can not be use for shader program creation");
        }

        // Todo also look there
        m_properties = vertex.get_properties() | fragment.get_properties();
    }

    GLShaderProgram::~GLShaderProgram() {
        destroy();
    }

    void GLShaderProgram::create_shader_program(const GLShader& vertex, const GLShader& fragment) {
        id = glCreateProgram();
        glAttachShader(id, vertex.get_shader());
        glAttachShader(id, fragment.get_shader());
        glLinkProgram(id);

        check_program_linking(id);
    }

    void GLShaderProgram::check_program_linking(const GLuint& program) {
        i32 success;
        char infoLog[512];

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);

            // Todo resolve this
            std::cout << infoLog << "\n";

            throw std::runtime_error("Failed to link shader program, with error: " + std::string(infoLog));
        }
    }

    GLint GLShaderProgram::get_uniform_location(const char* uniformName) const {
        return glGetUniformLocation(id, uniformName);
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const i32& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform1i(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const GLsizei& size, const i32* value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform1iv(uniform, size, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const u32& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform1ui(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const f32& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform1f(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const Vec2f& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform2f(uniform, value.x, value.y);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const Vec3f& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform3f(uniform, value.x, value.y, value.z);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const Vec4f& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniform4f(uniform, value.x, value.y, value.z, value.w);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniformName, const Mat4f& value) const {
        if(m_properties & ENABLE_UNIFORMS) {
            const auto uniform = get_uniform_location(uniformName);
            glUniformMatrix4fv(uniform, 1, GL_FALSE, value.e);
        }
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