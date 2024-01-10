#ifndef _BEBONE_SHADERS_SHADER_COMPILER_H_
#define _BEBONE_SHADERS_SHADER_COMPILER_H_

#include <cstring>
#include <fstream>

#include "shader_code.h"
#include "shader_source.h"

namespace bebone::gfx {
    /// Class used for compiling shaders
    class ShaderCompiler {
        protected:
            std::string m_defaultEntryPoint;
            std::vector<ShaderSource> m_shaderSources;

        public:
            /// Default constructor
            ShaderCompiler();

            /*!
             * Function sets an entry point for target shader
             * @param p_entryPoint - desired entry point name
            */
            void set_entry_point(const std::string& p_entryPoint);

            /*!
             * Adds source file to shader compiler
             * @param p_shaderSource - shader source object
            */
            void add_shader_source(const ShaderSource& p_shaderSource);

            /// Cleans shader compiler, all shader sources
            void clear_shader_source();

            /// Abstract method that compiles all shader sources to shader byte code with desired shader type
            virtual ShaderCode compile(const ShaderType& p_shaderType) = 0;
        };
}

#endif
