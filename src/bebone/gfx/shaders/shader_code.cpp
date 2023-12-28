#include "shader_code.h"

namespace bebone::gfx {
    ShaderCode::ShaderCode(const ShaderType& p_shaderType)
        : m_shaderType(p_shaderType) {

    }

    ShaderCode::ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType)
        : m_spirVCode(p_spirVByteCode),
          m_shaderType(p_shaderType) {

    }

    const ShaderType& ShaderCode::get_shader_type() const {
        return m_shaderType;
    }

    const RawSpirVByteCode& ShaderCode::get_byte_code() const {
        return m_spirVCode;
    }
}
