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
            std::string default_entry_point;
            std::vector<ShaderSource> shader_sources;

        public:
            /// Default constructor
            ShaderCompiler();

            /*!
             * Function sets an entry point for target shader
             * @param entry_point - desired entry point name
            */
            void set_entry_point(const std::string& entry_point);

            /*!
             * Adds source file to shader compiler
             * @param shader_source - shader source object
            */
            void add_shader_source(const ShaderSource& shader_source);

            /// Cleans shader compiler, all shader sources
            void clear_shader_source();

            /// Abstract method that compiles all shader sources to shader byte code with desired shader type
            virtual ShaderCode compile(const ShaderType& shader_type) = 0;
        };
}

#endif
