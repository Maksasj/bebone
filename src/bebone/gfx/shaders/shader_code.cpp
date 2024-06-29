#include "shader_code.h"

namespace bebone::gfx {
    ShaderCode::ShaderCode(const ShaderType& shader_type)
        : shader_type(shader_type) {

    }

    ShaderCode::ShaderCode(const RawSpirVByteCode& spirv_byte_code, const ShaderType& shader_type)
        : spirv_code(spirv_byte_code),
          shader_type(shader_type) {

    }

    const ShaderType& ShaderCode::get_shader_type() const {
        return shader_type;
    }

    const RawSpirVByteCode& ShaderCode::get_byte_code() const {
        return spirv_code;
    }
}
