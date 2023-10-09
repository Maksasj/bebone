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
            ShaderSource m_shaderSourceCode;

        public:
            ShaderCode(const ShaderType& p_shaderType) 
                : m_shaderType(p_shaderType) {

            }

            ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType) 
                : m_spirVCode(p_spirVByteCode), 
                  m_shaderType(p_shaderType) {

            }

            ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType, const ShaderSource& p_shaderSource) 
                : m_spirVCode(p_spirVByteCode), 
                  m_shaderType(p_shaderType), m_shaderSourceCode(p_shaderSource) {

            }

            const RawSpirVByteCode& get_byte_code() const {
                return m_spirVCode;
            }

            const ShaderSource& get_shader_source_code() const {
                return m_shaderSourceCode;
            }
    };
}

#endif
