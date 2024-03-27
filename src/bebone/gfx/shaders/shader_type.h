#ifndef _BEBONE_GFX_SHADERS_SHADER_TYPE_H_
#define _BEBONE_GFX_SHADERS_SHADER_TYPE_H_

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct ShaderTypes;

    // Class used for specifying a shader type
    struct ShaderType {
        private:
            u32 m_value;

            ShaderType(const u32& p_value);
        
        public:
            friend struct ShaderTypes;

            /// Overloaded shader type comparison operator
            bool operator==(const ShaderType& p_another) const;

            /// Overloaded shader type comparison operator
            bool operator!=(const ShaderType& p_another) const;

            /// Function that return string representation of shader type
            std::string to_string() const;

            /// Function that return glslang representation of shader type
            EShLanguage to_glslang() const;

            /// Function that return opengl representation of shader type
            GLuint to_opengl() const;
    };

    /// Class that is used for enumerating different shader types
    struct ShaderTypes {
        static const ShaderType FRAGMENT_SHADER;
        static const ShaderType VERTEX_SHADER;
    };
}

#endif
