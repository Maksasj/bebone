#include "shader_type.h"

namespace bebone::gfx {
    std::string to_string(const ShaderType& type) {
        switch (type) {
            case FragmentShader:
                return "FragmentShader";
            case VertexShader:
                return "VertexShader";
            default:
                throw std::runtime_error("undefined shader type");
        }
    }

    EShLanguage to_glslang(const ShaderType& shader_type) {
        switch (shader_type) {
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

    GLuint to_opengl(const ShaderType& type) {
        switch (type) {
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
