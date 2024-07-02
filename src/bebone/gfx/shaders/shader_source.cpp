#include "shader_source.h"

namespace bebone::gfx {
    ShaderSource::ShaderSource(const std::string& shader_source, const ShaderType& shader_type)
        : shader_source(shader_source),
          shader_type(shader_type) {

    }

    const ShaderType& ShaderSource::get_type() const {
        return shader_type;
    }

    const std::string& ShaderSource::get_shader_source() const {
        return shader_source;
    }
}
