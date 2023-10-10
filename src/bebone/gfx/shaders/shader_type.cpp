#include "shader_type.h"

namespace bebone::gfx {
    const ShaderType ShaderTypes::FRAGMENT_SHADER = ShaderType(0);
    const ShaderType ShaderTypes::VERTEX_SHADER = ShaderType(1);

    ShaderType::ShaderType(const u32 &p_value)
            : m_value(p_value) {

    }

    bool ShaderType::operator==(const ShaderType &p_another) const {
        return m_value == p_another.m_value;
    }

    bool ShaderType::operator!=(const ShaderType &p_another) const {
        return m_value != p_another.m_value;
    }

    std::string ShaderType::to_string() const {
        switch (m_value) {
            case 0:
                return "FRAGMENT_SHADER";
            case 1:
                return "VERTEX_SHADER";
            default:
                throw std::runtime_error("undefined shader type");
        }

        // Just do not want to have any warnings
        return "";
    }

    EShLanguage ShaderType::to_glslang() const {
        switch (m_value) {
            case 0:
                return EShLanguage::EShLangFragment;
            case 1:
                return EShLanguage::EShLangVertex;
            default:
                throw std::runtime_error("undefined shader type, cannot be converted to glslang enum");
        }

        // Just do not want to have any warnings
        return EShLanguage::EShLangVertex;
    }

    GLuint ShaderType::to_opengl() const {
        switch (m_value) {
            case 0:
                return GL_FRAGMENT_SHADER;
            case 1:
                return GL_VERTEX_SHADER;
            default:
                throw std::runtime_error("undefined shader type, cannot be converted to opengl gluint");
        }

        return GL_VERTEX_SHADER;
    }
}
