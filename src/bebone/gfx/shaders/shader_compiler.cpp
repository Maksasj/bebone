#include "shader_compiler.h"

namespace bebone::gfx {
    ShaderCompiler::ShaderCompiler()
        : m_defaultEntryPoint("main") {

    }

    void ShaderCompiler::set_entry_point(const std::string& p_entryPoint) {
        m_defaultEntryPoint = p_entryPoint;
    }

    void ShaderCompiler::add_shader_source(const ShaderSource& p_shaderSource) {
        m_shaderSources.push_back(p_shaderSource);
    }

    void ShaderCompiler::clear_shader_source() {
        m_shaderSources.clear();
    }
}
