#include "opengl_shader_program.h"

namespace bebone::gfx {
    GLShaderProgram::GLShaderProgram(const GLShader& vertex, const GLShader& fragment) {
        create_shader_program(vertex, fragment);

        if(vertex.get_properties() != fragment.get_properties()) {
            // Todo, we need to have some sort of policy for compatibility of shader properties
            throw std::runtime_error("Provided opengl shaders have different properties, therefore they can not be use for shader program creation");
        }

        // Todo also look there
        properties = vertex.get_properties() | fragment.get_properties();
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
        char info_log[512];

        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, info_log);

            // Todo resolve this
            std::cout << info_log << "\n";

            throw std::runtime_error("Failed to link shader program, with error: " + std::string(info_log));
        }
    }

    GLint GLShaderProgram::get_uniform_location(const char* uniform_name) const {
        return glGetUniformLocation(id, uniform_name);
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const i32& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform1i(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const GLsizei& size, const i32* value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform1iv(uniform, size, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const u32& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform1ui(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const f32& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform1f(uniform, value);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const Vec2f& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform2f(uniform, value.x, value.y);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const Vec3f& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform3f(uniform, value.x, value.y, value.z);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const Vec4f& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniform4f(uniform, value.x, value.y, value.z, value.w);
        }
    }

    void GLShaderProgram::set_uniform(const char* uniform_name, const Mat4f& value) const {
        if(properties & EnableUniforms) {
            const auto uniform = get_uniform_location(uniform_name);
            glUniformMatrix4fv(uniform, 1, GL_FALSE, value.get_raw());
        }
    }

    void GLShaderProgram::bind_buffer(const char* uniform_buffer_name, const i32& binding, const GLUniformBufferObject& buffer) const {
        buffer.bind_buffer_base(binding);

        const auto ubo_index = glGetUniformBlockIndex(id, uniform_buffer_name);
        glUniformBlockBinding(id, ubo_index, binding);
    }

    void GLShaderProgram::enable() {
        glUseProgram(id);
    }

    void GLShaderProgram::destroy() {
        glDeleteProgram(id);
    }
}