#ifndef _BEBONE_GFX_SHADER_TYPE_H_
#define _BEBONE_GFX_SHADER_TYPE_H_

#include "../gfx_backend.h"
#include "../../core/core.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct ShaderTypes;

    struct ShaderType {
        private:
            u32 m_value;

            ShaderType(const u32& p_value) 
                : m_value(p_value) {

            }
        
        public:
            friend struct ShaderTypes;

            bool operator==(const ShaderType& p_another) const {
                return m_value == p_another.m_value;
            }

            bool operator!=(const ShaderType& p_another) const {
                return m_value != p_another.m_value;
            }

            std::string to_string() const {
                switch (m_value) {
                    case 0: return "FRAGMENT_SHADER";
                    case 1: return "VERTEX_SHADER";
                    default: throw std::runtime_error("undefined shader type");
                }

                // Just do not want to have any warnings
                return "";
            }

            EShLanguage to_glslang() const {
                switch (m_value) {
                    case 0: return EShLanguage::EShLangFragment;
                    case 1: return EShLanguage::EShLangVertex;
                    default: throw std::runtime_error("undefined shader type, cannot be converted to glslang enum");
                }

                // Just do not want to have any warnings
                return EShLanguage::EShLangVertex;
            }

            GLuint to_opengl() const {
                switch (m_value) {
                    case 0: return GL_FRAGMENT_SHADER;
                    case 1: return GL_VERTEX_SHADER;
                    default: throw std::runtime_error("undefined shader type, cannot be converted to opengl gluint");
                }

                return GL_VERTEX_SHADER;
            }
    };

    struct ShaderTypes {
        static const ShaderType FRAGMENT_SHADER;
        static const ShaderType VERTEX_SHADER;
    };
}

#endif
