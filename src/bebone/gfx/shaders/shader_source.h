#ifndef _BEBONE_GFX_SHADERS_SHADER_SOURCE_H_
#define _BEBONE_GFX_SHADERS_SHADER_SOURCE_H_

#include "../gfx_backend.h"
#include "shader_type.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Class used for storing shader source
    class ShaderSource {
        private:
            std::string shader_source;
            ShaderType shader_type;

        public:
            /*!
             * Default constructor
             * @param shader_source - shader source string
             * @param shader_type - shader type
             */
            ShaderSource(const std::string& shader_source, const ShaderType& shader_type);

            /// Function that returns shader type
            const ShaderType& get_type() const;

            /// Function that returns shader source code as string
            const std::string& get_shader_source() const;
    };
}

#endif
