#include "opengl_shader.h"

namespace bebone::gfx::opengl {
    GLShader::GLShader(const ShaderCode& code, const ShaderType& shaderType, const GLShaderProperties& properties)
            : m_properties(properties) {

        m_shader = glCreateShader(shaderType.to_opengl());

        const auto& source = code.get_byte_code();

        // **_ARB things can be used only with specific glad extensions, see all-extensions glad branch
        // This should always work, since we now check if device can use SPIRV shader binary code.
        // If no, then factory will try to use second constructor
        glShaderBinary(1, &m_shader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, source.data(), source.size() * sizeof(unsigned int));
        glSpecializeShaderARB(m_shader, "main", 0, nullptr, nullptr);
    }

    GLShader::GLShader(const std::string& code, const ShaderType& shaderType, const GLShaderProperties& properties)
            : m_properties(properties) {

        m_shader = glCreateShader(shaderType.to_opengl());

        const auto str = code.c_str();

        glShaderSource(m_shader, 1, &str, nullptr);
        glCompileShader(m_shader);

        check_shader_compilation(m_shader);
    }

    void GLShader::check_shader_compilation(const GLuint& shader) {
        char infoLog[512];
        i32 success;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

            std::cout << infoLog << "\n";

            throw std::runtime_error("Failed to compile shader, with error: " + std::string(infoLog));
        }
    }

    GLuint GLShader::get_shader() const {
        return m_shader;
    }

    const GLShaderProperties& GLShader::get_properties() const {
        return m_properties;
    }

    void GLShader::destroy() {
        glDeleteShader(m_shader);
    }

    GLShaderProgram::GLShaderProgram(const GLShader& vertex, const GLShader& fragment) {
        create_shader_program(vertex, fragment);

        if(vertex.get_properties() != fragment.get_properties()) {
            // Todo, we need to have some sort of policy for compatibility of shader properties
            throw std::runtime_error("Provided opengl shaders have different properties, therefore they can not be use for shader program creation");
        }

        // Todo also look there
        m_properties = vertex.get_properties() | fragment.get_properties();
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
