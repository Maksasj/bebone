#include "shader_source.h"

namespace bebone::gfx {
    ShaderSource::ShaderSource(const std::string& p_shaderSource, const ShaderType& p_shaderType)
        : m_shaderSource(p_shaderSource),
          m_shaderType(p_shaderType) {

    }

    const ShaderType& ShaderSource::get_type() const {
        return m_shaderType;
    }

    const std::string& ShaderSource::get_shader_source() const {
        return m_shaderSource;
    }
}
