#ifndef _BEBONE_GFX_SHADERS_SHADER_TYPE_H_
#define _BEBONE_GFX_SHADERS_SHADER_TYPE_H_

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    enum ShaderType {
        FragmentShader,
        VertexShader
    };

    std::string to_string(const ShaderType& type);

    EShLanguage to_glslang(const ShaderType& type);
    GLuint to_opengl(const ShaderType& type);
}

#endif
