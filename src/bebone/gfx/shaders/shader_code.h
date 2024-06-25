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
            RawSpirVByteCode spirv_code;
            ShaderType shader_type;

        public:
            /*!
             * Default constructor
             * @param shader_type - shader type
            */
            ShaderCode(const ShaderType& shader_type);

            /*!
             * Standart constructor
             * @param spirv_byte_code - shader byte code vector
             * @param shader_type - shader type
            */
            ShaderCode(const RawSpirVByteCode& spirv_byte_code, const ShaderType& shader_type) ;

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
