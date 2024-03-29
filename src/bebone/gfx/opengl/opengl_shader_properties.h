#ifndef _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROPERTIES_H_
#define _BEBONE_GFX_OPENGL_OPENGL_SHADER_PROPERTIES_H_

namespace bebone::gfx::opengl {
    enum GLShaderProperties {
        NONE = (1 << 0),
        ENABLE_UNIFORMS = (1 << 1),
    };

    inline GLShaderProperties operator|(GLShaderProperties first, GLShaderProperties second) {
        return static_cast<GLShaderProperties>(static_cast<int>(first) | static_cast<int>(second));
    }
}

#endif
