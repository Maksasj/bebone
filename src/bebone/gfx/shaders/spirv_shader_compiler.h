#ifndef _BEBONE_GFX_SHADERS_SPIRV_SHADER_COMPILER_H_
#define _BEBONE_GFX_SHADERS_SPIRV_SHADER_COMPILER_H_

#include "shader_compiler.h"

namespace bebone::gfx {
    /// Class that implements shader compiler for spir-v shaders
    class SpirVShaderCompiler : public ShaderCompiler {
        private:

        public:

            /*!
             * Function that compiles shader source codes with desired shader type
             * @param p_shaderType - desired shader type
             * @return Shader code object
            */
            ShaderCode compile(const ShaderType& p_shaderType);
    };
}

#endif
