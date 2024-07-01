#include "opengl_shader.h"

namespace bebone::gfx {
    GLShader::GLShader(const ShaderCode& code, const ShaderType& shader_type, const GLShaderProperties& properties)
            : properties(properties) {

        shader = glCreateShader(shader_type.to_opengl());

        const auto& source = code.get_byte_code();

        // **_ARB things can be used only with specific glad extensions, see all-extensions glad branch
        // This should always work, since we now check if device can use SPIRV shader binary code.
        // If no, then factory will try to use second constructor
        glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, source.data(), source.size() * sizeof(unsigned int));
        glSpecializeShaderARB(shader, "main", 0, nullptr, nullptr);
    }

    GLShader::~GLShader() {
        destroy();
    }

    GLShader::GLShader(const std::string& code, const ShaderType& shader_type, const GLShaderProperties& properties)
            : properties(properties) {

        shader = glCreateShader(shader_type.to_opengl());

        const auto str = code.c_str();

        glShaderSource(shader, 1, &str, nullptr);
        glCompileShader(shader);

        check_shader_compilation(shader);
    }

    void GLShader::check_shader_compilation(const GLuint& shader) {
        char info_log[512];
        i32 success;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(shader, 512, nullptr, info_log);

            // Todo resolve this
            std::cout << info_log << "\n";

            throw std::runtime_error("Failed to compile shader, with error: " + std::string(info_log));
        }
    }

    GLuint GLShader::get_shader() const {
        return shader;
    }

    const GLShaderProperties& GLShader::get_properties() const {
        return properties;
    }

    void GLShader::destroy() {
        glDeleteShader(shader);
    }
}
