#ifndef _BEBONE_SHADER_COMPILER_H_
#define _BEBONE_SHADER_COMPILER_H_

#include <cstring>
#include <fstream>

#include "shader_code.h"
#include "shader_source.h"

namespace bebone::gfx {
    class ShaderCompiler {
        protected:
            std::string m_defaultEntryPoint;
            std::vector<ShaderSource> m_shaderSources;

        public:
            ShaderCompiler()
                : m_defaultEntryPoint("main") {

            }

            void set_entry_point(const std::string& p_entryPoint) {
                m_defaultEntryPoint = p_entryPoint;
            }

            void add_shader_source(const ShaderSource& p_shaderSource) {
                m_shaderSources.push_back(p_shaderSource);
            }

            void clear_shader_source() {
                m_shaderSources.clear();
            }

            virtual ShaderCode compile(const ShaderType& p_shaderType) = 0;
        };
}

#endif