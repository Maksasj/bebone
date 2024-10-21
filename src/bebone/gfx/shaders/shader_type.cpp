#include "shader_type.h"

namespace bebone::gfx {
    std::string to_string(const ShaderType& type) {
        switch (type) {
            case ShaderType::FragmentShader:
                return "FragmentShader";
            case ShaderType::VertexShader:
                return "VertexShader";
        }
    }

    EShLanguage to_glslang(const ShaderType& shader_type) {
        switch (shader_type) {
            case ShaderType::FragmentShader:
                return EShLanguage::EShLangFragment;
            case ShaderType::VertexShader:
                return EShLanguage::EShLangVertex;
        }
    }

    GLuint to_opengl(const ShaderType& type) {
        switch (type) {
            case ShaderType::FragmentShader:
                return GL_FRAGMENT_SHADER;
            case ShaderType::VertexShader:
                return GL_VERTEX_SHADER;
        }
    }
}
