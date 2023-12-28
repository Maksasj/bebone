#ifndef _BEBONE_GFX_SHADER_CODE_H_
#define _BEBONE_GFX_SHADER_CODE_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "shader_type.h"
#include "shader_source.h"

namespace bebone::gfx {
    using namespace bebone::core;

    using RawSpirVByteCode = std::vector<u32>;

    class ShaderCode {
        private:
            RawSpirVByteCode m_spirVCode;
            ShaderType m_shaderType;

        public:
            ShaderCode(const ShaderType& p_shaderType);
            ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType) ;

            const ShaderType& get_shader_type() const;

            const RawSpirVByteCode& get_byte_code() const;
    };
}

#endif
