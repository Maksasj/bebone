#ifndef _BEBONE_GFX_SPIRV_SHADER_COMPILER_H_
#define _BEBONE_GFX_SPIRV_SHADER_COMPILER_H_

#include "shader_compiler.h"

namespace bebone::gfx {
    class SpirVShaderCompiler : public ShaderCompiler {
        private:

        public:
            ShaderCode compile(const ShaderType& p_shaderType);
    };
}

#endif
