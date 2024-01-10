#ifndef _BEBONE_GFX_SHADERS_SHADER_SOURCE_H_
#define _BEBONE_GFX_SHADERS_SHADER_SOURCE_H_

#include "../../core/core.h"
#include "../gfx_backend.h"
#include "shader_type.h"

namespace bebone::gfx {
    using namespace bebone::core;

    /// Class used for storing shader source
    class ShaderSource {
        private:
            std::string m_shaderSource;
            ShaderType m_shaderType;

        public:
            /*!
             * Default constructor
             * @param p_shaderSource - shader source string
             * @param p_shaderType - shader type
             */
            ShaderSource(const std::string& p_shaderSource, const ShaderType& p_shaderType);

            /// Function that returns shader type
            const ShaderType& get_type() const;

            /// Function that returns shader source code as string
            const std::string& get_shader_source() const;
    };
}

#endif
