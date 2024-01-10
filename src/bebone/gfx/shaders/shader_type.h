#ifndef _BEBONE_GFX_SHADERS_SHADER_TYPE_H_
#define _BEBONE_GFX_SHADERS_SHADER_TYPE_H_

#include "../gfx_backend.h"
#include "../../core/core.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct ShaderTypes;

    struct ShaderType {
        private:
            u32 m_value;

            ShaderType(const u32& p_value);
        
        public:
            friend struct ShaderTypes;

            bool operator==(const ShaderType& p_another) const;
            bool operator!=(const ShaderType& p_another) const;

            std::string to_string() const;
            EShLanguage to_glslang() const;
            GLuint to_opengl() const;
    };

    struct ShaderTypes {
        static const ShaderType FRAGMENT_SHADER;
        static const ShaderType VERTEX_SHADER;
    };
}

#endif
