#ifndef _BEBONE_GFX_SHADERS_SHADER_CODE_H_
#define _BEBONE_GFX_SHADERS_SHADER_CODE_H_

#include <vector>

#include "../gfx_backend.h"

#include "shader_type.h"
#include "shader_source.h"

namespace bebone::gfx {
    using namespace bebone::core;

    using RawSpirVByteCode = std::vector<u32>;

    /// Class used for storing shader code
    class ShaderCode {
        private:
            RawSpirVByteCode m_spirVCode;
            ShaderType m_shaderType;

        public:
            /*!
             * Default constructor
             * @param p_shaderType - shader type
            */
            ShaderCode(const ShaderType& p_shaderType);

            /*!
             * Standart constructor
             * @param p_spirVByteCode - shader byte code vector
             * @param p_shaderType - shader type
            */
            ShaderCode(const RawSpirVByteCode& p_spirVByteCode, const ShaderType& p_shaderType) ;

            /*!
             * Returns shader type
             * @return shader type
            */
            const ShaderType& get_shader_type() const;

            /*!
             * Function that returns const reference to shader byte code vector
             * @return reference to byte code vector
            */
            const RawSpirVByteCode& get_byte_code() const;
    };
}

#endif
