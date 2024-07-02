#include "shader_compiler.h"

namespace bebone::gfx {
    ShaderCompiler::ShaderCompiler()
        : default_entry_point("main") {

    }

    void ShaderCompiler::set_entry_point(const std::string& entry_point) {
        default_entry_point = entry_point;
    }

    void ShaderCompiler::add_shader_source(const ShaderSource& shader_source) {
        shader_sources.push_back(shader_source);
    }

    void ShaderCompiler::clear_shader_source() {
        shader_sources.clear();
    }
}
