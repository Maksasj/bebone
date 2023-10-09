#include "opengl_shader_factory.h"

namespace bebone::gfx::opengl {
    std::string GLShaderFactory::read_file(const std::string& path) {
        std::ifstream file(path);
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    GLShader GLShaderFactory::create_shader(const std::string& path, const ShaderType& shaderType) {
        ShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(read_file(path), shaderType));
        const auto code = shaderCompiler.compile(shaderType);

        return GLShader(code, shaderType);
    }
}
