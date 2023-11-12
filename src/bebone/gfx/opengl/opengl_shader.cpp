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

            // Todo resolve this
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
}
