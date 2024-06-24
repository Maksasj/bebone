#include "shader_type.h"

namespace bebone::gfx {
    const ShaderType ShaderTypes::FRAGMENT_SHADER = ShaderType(0);
    const ShaderType ShaderTypes::VERTEX_SHADER = ShaderType(1);

    ShaderType::ShaderType(const u32 &value)
            : value(value) {

    }

    bool ShaderType::operator==(const ShaderType &another) const {
        return value == another.value;
    }

    bool ShaderType::operator!=(const ShaderType &another) const {
        return value != another.value;
    }

    std::string ShaderType::to_string() const {
        switch (value) {
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
        switch (value) {
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
        switch (value) {
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
