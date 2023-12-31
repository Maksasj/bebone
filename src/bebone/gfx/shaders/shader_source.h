#ifndef _BEBONE_GFX_SHADER_SOURCE_H_
#define _BEBONE_GFX_SHADER_SOURCE_H_

#include "../../core/core.h"
#include "../gfx_backend.h"
#include "shader_type.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class ShaderSource {
        private:
            std::string m_shaderSource;
            ShaderType m_shaderType;

        public:
            ShaderSource(const std::string& p_shaderSource, const ShaderType& p_shaderType);

            const ShaderType& get_type() const;
            const std::string& get_shader_source() const;
    };
}

#endif
